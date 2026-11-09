#!/usr/bin/env bash
set -euo pipefail
root=$(cd "$(dirname "$0")/.." && pwd)
tmp=$(mktemp -d)
trap 'rm -rf -- "$tmp"' EXIT
cd "$tmp"
git init -q exporter
git -C exporter fetch -q --depth=1 https://github.com/OI-wiki/OI-Wiki-export.git 960f4345100a1b8caaea8fb13f5b813ec46985d0
git -C exporter checkout -q FETCH_HEAD
for pkg in remark-snippet remark-typst oi-wiki-export-typst; do
  npm ci --prefix "exporter/$pkg" --no-audit --no-fund
done
mkdir source
cp -R "$root/docs" "$root/mkdocs.yml" source/
cp "$root"/print/*.typ .
timeout 3m node exporter/oi-wiki-export-typst/index.js source
mkdir -p "$root/dist"
typst compile oi-wiki-export.typ "$tmp/result.pdf"
mv result.pdf "$root/dist/wiki-template.pdf"
