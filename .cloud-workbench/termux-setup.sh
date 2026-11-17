#!/data/data/com.termux/files/usr/bin/bash
set -euo pipefail
pkg install -y openssh
umask 077
mkdir -p "$HOME/.ssh" "$HOME/bin"
if [ ! -f "$HOME/.ssh/cloud-workbench" ]; then
  ssh-keygen -q -t ed25519 -N '' -C android-cloud-workbench -f "$HOME/.ssh/cloud-workbench"
fi
if [ -f "$HOME/.ssh/config" ]; then
  cp -p "$HOME/.ssh/config" "$HOME/.ssh/config.before-cloud-$(date +%Y%m%dT%H%M%S)"
fi
cat > "$HOME/.ssh/config" <<'EOF'
Host cloud-workbench
 HostName 43.153.94.4
 User clouddev
 IdentityFile ~/.ssh/cloud-workbench
 IdentitiesOnly yes
 StrictHostKeyChecking yes
 UserKnownHostsFile ~/.ssh/known_hosts
 ConnectTimeout 15
 ServerAliveInterval 20
 ServerAliveCountMax 3
 IPQoS none
EOF
cat > "$HOME/bin/ai" <<'EOF'
#!/data/data/com.termux/files/usr/bin/bash
exec ssh -tt cloud-workbench /home/clouddev/bin/ai-session
EOF
cat > "$HOME/bin/cloud" <<'EOF'
#!/data/data/com.termux/files/usr/bin/bash
exec ssh -tt cloud-workbench /home/clouddev/bin/workbench
EOF
chmod 700 "$HOME/bin/ai" "$HOME/bin/cloud"
printf '%s\n' 'Send only this PUBLIC key to the server operator:'
cat "$HOME/.ssh/cloud-workbench.pub"
printf '%s\n' 'An operator must install the verified server host key in ~/.ssh/known_hosts and authorize the public key. Do not use an unverified ssh-keyscan result.'
