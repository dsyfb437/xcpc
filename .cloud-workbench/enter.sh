#!/usr/bin/env bash
set -euo pipefail
cd "$HOME/workspace/xcpc-template"
exec tmux new-session -A -s cloud-workbench -c "$PWD"
