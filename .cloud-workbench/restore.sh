#!/usr/bin/env bash
set -euo pipefail
archive=$(realpath "${1:?usage: restore.sh ARCHIVE EMPTY_DIRECTORY}")
dest=${2:?usage: restore.sh ARCHIVE EMPTY_DIRECTORY}
(cd "$(dirname "$archive")" && sha256sum -c "$(basename "$archive").sha256")
mkdir -p "$dest"
if [ -n "$(ls -A "$dest")" ]; then echo 'Restore destination must be empty' >&2; exit 1; fi
tar -xzf "$archive" -C "$dest"
cd "$dest/xcpc-template"
if [ "${CLOUD_FULL_CHECK:-0}" = "1" ]; then python3 print.py --check; fi
python3 print.py
