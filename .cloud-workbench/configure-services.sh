#!/usr/bin/env bash
set -euo pipefail
# Run as clouddev; an operator must enable linger and apply resource limits below.
base=$(cd -- "$(dirname -- "$0")" && pwd)
mkdir -p "$HOME/.config/systemd/user" "$HOME/bin" "$HOME/backups"
cp "$base"/systemd/* "$HOME/.config/systemd/user/"
ln -sfn "$base/backup.sh" "$HOME/bin/workbench-backup"
ln -sfn "$base/enter.sh" "$HOME/bin/workbench"
ln -sfn "$base/ai.sh" "$HOME/bin/ai"
systemctl --user daemon-reload
systemctl --user enable --now codex-cloud-remote.service workbench-backup.timer
