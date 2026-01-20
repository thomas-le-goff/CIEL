import argparse
import os
import json
import shutil
import subprocess

from pathlib import Path


def extract_export_type_from_name(file_name):
    splitted = file_name.split(".")
    if len(splitted) < 3:
        return None
    return splitted[-2]


def publish_file(file_src_path, file_dst_path, export_type):
    publish_file_path = file_dst_path
    match export_type:
        case None:
            return None
        case "copy":
            shutil.copyfile(file_src_path, publish_file_path)
        case "pdf-slideshow":
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
        # Todo add pandoc case
        case _:
            raise RuntimeError(f"Unknown export type : {export_type}")
    return publish_file_path


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", required=True)

    args = parser.parse_args()

    args.output = Path(args.output)

    if not args.output.is_dir():
        raise RuntimeError("args.output need to be a directory.")

    tree = {}
    root_dir = Path("../src")
    file_formats = ".md"

    attachments_dir = args.output / "attachments"
    if attachments_dir.exists():
        shutil.rmtree(attachments_dir)

    for d in os.listdir(root_dir):
        tree[d] = {}
        for sd in os.listdir(root_dir / d):
            final_src_path = root_dir / d / sd
            final_dst_path = attachments_dir / d / sd
            os.makedirs(final_dst_path)
            tree[d][sd] = []
            for f in os.listdir(final_src_path):
                if Path.is_file(final_src_path / f) and f.endswith(file_formats):
                    p_file = publish_file(
                        final_src_path / f,
                        final_dst_path / f,
                        export_type=extract_export_type_from_name(f),
                    )
                    if p_file:
                        tree[d][sd].append(p_file.name)

    with open(args.output / "_data" / "attachments.json", "w") as output_file:
        output_file.write(json.dumps(tree, ensure_ascii=False))
