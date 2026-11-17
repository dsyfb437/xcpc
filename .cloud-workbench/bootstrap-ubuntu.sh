#!/usr/bin/env bash
set -euo pipefail
# Run as a sudo-capable operator on Ubuntu 24.04 before restoring source.
sudo apt-get update -qq
sudo apt-get install -y git python3 g++ tmux fonts-noto-cjk fonts-noto-core fonts-noto-mono zstd bubblewrap apparmor-profiles apparmor-utils
if [ -f /usr/share/apparmor/extra-profiles/bwrap-userns-restrict ]; then
  if [ ! -f /etc/apparmor.d/bwrap-userns-restrict ]; then
    sudo install -m 0644 /usr/share/apparmor/extra-profiles/bwrap-userns-restrict /etc/apparmor.d/bwrap-userns-restrict
  fi
  sudo apparmor_parser -r /etc/apparmor.d/bwrap-userns-restrict
fi
stage=$(mktemp -d)
trap 'rm -rf "$stage"' EXIT
cd "$stage"
curl -fsSL --retry 2 -o typst.tar.xz https://github.com/typst/typst/releases/download/v0.15.1/typst-x86_64-unknown-linux-musl.tar.xz
printf '%s  %s\n' a6d077d0a95eed5a2eba715b2dae06be954f624ccbf85758a03f389ded33118c typst.tar.xz | sha256sum -c -
tar -xJf typst.tar.xz
sudo install -m 755 typst-x86_64-unknown-linux-musl/typst /usr/local/bin/typst
python3 --version
g++ --version | head -1
typst --version
