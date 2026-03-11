import argparse
import os
import json
import shutil
import subprocess
import yaml

from abc import ABC, abstractmethod
from pathlib import Path


class AbstractFileHandler(ABC):

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


class ChapterMetadataFileHandler(AbstractFileHandler):

    def __init__(self) -> None:
        super().__init__()
        self._metadata = {}
        self._metadatafile: Path | None = None

    def setup(self, output_dir: Path) -> None:
        self._metadatafile = output_dir / "_data" / "metadata.json"

    def teardown(self) -> None:
        if self._metadatafile is None:
            return
        with open(self._metadatafile, "w") as output_file:
            output_file.write(json.dumps(self._metadata, ensure_ascii=False))

    def match(self, file_path: Path) -> bool:
        return file_path.match(".metadata.yml")

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path | None:
        with open(file_src_path, mode='r') as f:
            #  Todo: find a better way of doing this
            id = str(file_src_path.parent).removeprefix("../src/")
            self._metadata[id] = yaml.safe_load(f) or {}
        return None


class MarplePdfSlideShowFileHandler(AbstractFileHandler):

    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        return file_path.match("*.pdf-slideshow.md")

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        publish_file_path = file_dst_path.with_suffix(".pdf")
        subprocess.run(
            [
                "npx",
                "@marp-team/marp-cli@latest",
                "--allow-local-files",
                "--pdf",
                file_src_path,
                "--output",
                publish_file_path,
            ]
        )

        return publish_file_path


class CopyFileHandler(AbstractFileHandler):

    def setup(self, output_dir: Path) -> None:
        pass

    def teardown(self) -> None:
        pass

    def match(self, file_path: Path) -> bool:
        return True

    def handle(self, file_src_path: Path, file_dst_path: Path) -> Path:
        shutil.copyfile(file_src_path, file_dst_path)
        return file_dst_path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", required=True)

    args = parser.parse_args()

    args.output = Path(args.output)

    if not args.output.is_dir():
        raise RuntimeError("args.output need to be a directory.")

    tree = {}
    root_dir = Path("../src")

    attachments_dir = args.output / "attachments"
    if attachments_dir.exists():
        shutil.rmtree(attachments_dir)

    file_handlers: list[AbstractFileHandler] = [
        ChapterMetadataFileHandler(),
        MarplePdfSlideShowFileHandler(),
        CopyFileHandler(),  #  Keep it last
    ]

    for fh in file_handlers:
        fh.setup(args.output)

    def handle_file(final_src_path: Path, final_dst_path: Path):
        if Path.is_file(final_src_path):
            for fh in file_handlers:
                if fh.match(final_src_path):
                    p_file = fh.handle(final_src_path, final_dst_path)
                    if p_file:
                        tree[d][sd].append(p_file.name)
                    break

    for d in os.listdir(root_dir):
        tree[d] = {}
        for sd in os.listdir(root_dir / d):
            final_src_path = root_dir / d / sd
            final_dst_path = attachments_dir / d / sd
            if final_src_path.is_dir():
                os.makedirs(final_dst_path)
                tree[d][sd] = []
                for f in os.listdir(final_src_path):
                    handle_file(final_src_path / f, final_dst_path / f)
            else:
                handle_file(final_src_path, final_dst_path)

    for fh in file_handlers:
        fh.teardown()

    with open(args.output / "_data" / "attachments.json", "w") as output_file:
        output_file.write(json.dumps(tree, ensure_ascii=False))


if __name__ == "__main__":
    main()
