# -*- mode: bash-ts-mode; compile-command: "bash build.sh" -*-
#!/usr/bin/env bash

set -o pipefail

container_cmd() {
    if command -v podman &>/dev/null; then
        echo "podman"
    else
        echo "docker is currently not supported."
        exit 1
    fi
}

"$(container_cmd)" build . --tag pandoc-extra-font
