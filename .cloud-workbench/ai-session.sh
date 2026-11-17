#!/usr/bin/env bash
set -euo pipefail
exec tmux new-session -A -s cloud-ai -c "$HOME/workspace/xcpc-template" /home/clouddev/bin/ai
