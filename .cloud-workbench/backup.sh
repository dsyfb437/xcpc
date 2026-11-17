#!/usr/bin/env bash
set -euo pipefail
umask 077
project=${1:-$HOME/workspace/xcpc-template}
backup_dir=${CLOUD_BACKUPS:-$HOME/backups}
mkdir -p "$backup_dir"
exec 9>"$backup_dir/.backup.lock"
flock 9
stamp=$(date -u +%Y%m%dT%H%M%S%NZ)
name="xcpc-template-$stamp.tar.gz"
tar --exclude='xcpc-template/output' --exclude='xcpc-template/build' -czf "$backup_dir/.$name.tmp" -C "$(dirname "$project")" "$(basename "$project")"
mv "$backup_dir/.$name.tmp" "$backup_dir/$name"
(cd "$backup_dir" && sha256sum "$name" > "$name.sha256")
printf '%s\n' "$backup_dir/$name"
