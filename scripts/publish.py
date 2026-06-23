# Local Variables:
# compile-command: "python publish.py ../eleventy/"
# End:

import argparse
import json
import os
import shutil
import subprocess
import tempfile
from abc import ABC, abstractmethod
from pathlib import Path
from posix import access
from typing import Any

import yaml

# TODO better logging (each handler print its action)
# TODO add pandoc file handler


class FileIgnorer:
    def __init__(self, root: Path, ignore_filename: str = ".publishignore") -> None:
        self.patterns = []
        self.root = Path
        self.ignore_filename = ignore_filename

    @classmethod
    def _load_patterns(cls, file_or_list: Path | list[str]):
        Patterns = []
        if isinstance(file_or_list, Path):
            patterns = [file_or_list.name]
            if Path.exists(file_or_list):
                with open(file_or_list) as file:
                    for l in file.readlines():
                        l = l.strip()
                        if l != "" and not l.startswith("#"):
                            patterns.append(l.strip())
        else:
            patterns = file_or_list

        return patterns

    def _load_tree(self, leaf: Path) -> list[str]:
        # TODO: handle multiple ignore files from file tree
        if (local_ignore := Path(leaf.parent / self.ignore_filename)).exists():
            return FileIgnorer._load_patterns(local_ignore)

        return []

    def is_file_ignored(self, file: Path) -> bool:
        local_patterns = self._load_tree(file)
        return any(file.match(p) for p in local_patterns)


class AbstractNodeHandler(ABC):
    @abstractmethod
    def setup(self, output_dir: Path) -> None:
        pass

    @abstractmethod
    def teardown(self) -> None:
        pass

    @abstractmethod
    def match(self, file_path: Path) -> bool:
        pass

    @abstractmethod
    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path | None:
        pass


class ChapterMetadataNodeHandler(AbstractNodeHandler):
    def __init__(self, metadatafile: Path) -> None:
        super().__init__()
        self._metadata: dict[str, Any] = {}
        self._metadatafile = metadatafile

    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        with open(self._metadatafile, "w") as output_file:
            output_file.write(json.dumps(self._metadata, ensure_ascii=False))

    def match(self, file_path: Path) -> bool:
        return not file_path.is_dir() and file_path.match(".metadata.yml")

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path | None:
        with open(file_src_path, mode="r") as f:
            #  Todo: find a better way of doing this
            id = str(file_src_path.parent).removeprefix("../src/")
            self._metadata[id] = yaml.safe_load(f) or {}
        return None


class MarplePdfSlideShowNodeHandler(AbstractNodeHandler):
    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        return not file_path.is_dir() and file_path.match("*.pdf-slideshow.md")

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        publish_file_path = file_dst_path.with_suffix(".pdf")
        destination_dir: Path = file_dst_path.parent.resolve()
        workdir = file_src_path.parent.resolve()

        _ = subprocess.run(
            [
                "podman",
                "run",
                "--userns=keep-id",
                "--rm",
                "--init",
                "-v",
                f"{workdir}:/home/marp/app:Z",
                "-v",
                f"{destination_dir}:/home/marp/out:Z",
                "-e",
                f"LANG={os.environ.get('LANG', 'C.UTF-8')}",
                "-e",
                f"MARP_USER={os.getuid()}:{os.getgid()}",
                "ghcr.io/marp-team/marp-cli",
                file_src_path.name,
                "--pdf",
                "--allow-local-files",
                "--output",
                f"/home/marp/out/{publish_file_path.name}",
            ]
        )

        return publish_file_path


class PandocNodeHandler(AbstractNodeHandler):
    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        compatible_extensions = ["md", "tex"]
        return not file_path.is_dir() and any(
            e for e in compatible_extensions if file_path.match("*.pandoc." + e)
        )

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        publish_file_path = file_dst_path.with_suffix(".pdf")
        destination_dir: Path = file_dst_path.parent.resolve()
        workdir: Path = file_src_path.parent.resolve()

        _ = subprocess.run(
            [
                "podman",
                "run",
                "--userns=keep-id",
                "--rm",
                "-v",
                f"{workdir}:/data:Z",
                "-v",
                f"{destination_dir}:/out:Z",
                "--user",
                f"{os.getuid()}:{os.getgid()}",
                "localhost/pandoc-extra-font:latest",
                file_src_path.name,
                "-o",
                f"/out/{publish_file_path.name}",
                "--pdf-engine=xelatex",
                "--template",
                "eisvogel",
                "-f",
                "markdown+implicit_figures",
            ]
        )

        return publish_file_path


class CopyNodeHandler(AbstractNodeHandler):
    def __init__(self) -> None:
        super().__init__()

    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        return not file_path.is_dir()

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        shutil.copyfile(file_src_path, file_dst_path)
        return file_dst_path


class ArchiveFolderNodeHandler(AbstractNodeHandler):
    def __init__(
        self,
        folder_names: list[str] = [],
        file_handlers: list[AbstractNodeHandler] = [],
        format: str = "zip",
    ) -> None:
        super().__init__()
        self.folder_names = folder_names
        self.publisher = Publisher(file_handlers, allow_multiple_handlers=True)
        self.format = format

    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        return file_path.is_dir() and any(
            fd for fd in self.folder_names if file_path.parent.match(fd)
        )

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        if not file_src_path.is_dir():
            raise RuntimeError(f"{file_src_path} must be a directory.")

        with tempfile.TemporaryDirectory() as tmpdirname:
            publish_dir_path = Path(tmpdirname)
            self.publisher.publish(file_src_path, publish_dir_path)

            archive_filename = Path(
                shutil.make_archive(
                    base_name=file_dst_path.stem,
                    format=self.format,
                    root_dir=publish_dir_path,
                )
            )

            shutil.move(archive_filename, file_dst_path.parent / archive_filename.name)

        return file_dst_path.with_suffix("." + self.format)


class Publisher:
    def __init__(
        self,
        node_handlers: list[AbstractNodeHandler],
        allow_multiple_handlers: bool = False,
    ) -> None:
        self.node_handlers = node_handlers
        self.allow_multiple_handlers = allow_multiple_handlers

    def _get_node_handlers(self, src_path: Path) -> list[AbstractNodeHandler]:
        handlers: list[AbstractNodeHandler] = []
        for fh in self.node_handlers:
            if fh.match(src_path):
                handlers.append(fh)
                if not self.allow_multiple_handlers:
                    return handlers
        return handlers

    def _handle_node(
        self, src_path: str | Path, dst_path: Path
    ) -> dict[str, Any | list[str]] | list[str]:
        tree: dict[str, Any] = {}
        if isinstance(src_path, str):
            src_path = Path(src_path)

        file_ignorers = [FileIgnorer(src_path), FileIgnorer(src_path, ".gitignore")]
        files: list[str] = []
        for n in os.listdir(src_path):
            n_src_path = src_path / n
            n_dst_path = dst_path / n
            if any(fi for fi in file_ignorers if fi.is_file_ignored(n_src_path)):
                continue
            handlers = self._get_node_handlers(n_src_path)
            if len(handlers) != 0:
                for fh in handlers:
                    p_file = fh.handle(n_src_path, n_dst_path)
                    if p_file:
                        files.append(p_file.name)
            elif n_src_path.is_dir():
                os.makedirs(n_dst_path)
                tree[n] = self._handle_node(n_src_path, n_dst_path)

        if len(files) != 0:
            for k in tree:
                files += tree[k]
            return files

        return tree

    def publish(
        self, src_path: str | Path, dst_path: Path
    ) -> dict[str, Any | list[str]] | list[str]:
        if dst_path.exists():
            shutil.rmtree(dst_path)

        os.mkdir(dst_path)

        # Maybe context manager is suitable here?
        for fh in self.node_handlers:
            fh.setup(dst_path)

        tree = self._handle_node(src_path, dst_path)

        for fh in self.node_handlers:
            fh.teardown()

        return tree


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", required=True)

    args = parser.parse_args()

    args.output = Path(args.output)

    if not args.output.is_dir():
        raise RuntimeError("args.output need to be a directory.")

    root_dir = Path("../src")

    publisher = Publisher(
        [
            ChapterMetadataNodeHandler(args.output / "_data" / "metadata.json"),
            PandocNodeHandler(),
            MarplePdfSlideShowNodeHandler(),
            ArchiveFolderNodeHandler(
                ["TP", "TD", "Assessments"],
                [
                    PandocNodeHandler(),
                    MarplePdfSlideShowNodeHandler(),
                    CopyNodeHandler(),
                ],
            ),
            CopyNodeHandler(),  #  Keep it last
        ]
    )

    tree = publisher.publish(root_dir, args.output / "attachments")

    with open(args.output / "_data" / "attachments.json", "w") as output_file:
        output_file.write(json.dumps(tree, ensure_ascii=False, check_circular=True))


if __name__ == "__main__":
    main()
