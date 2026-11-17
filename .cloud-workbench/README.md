# 云端开发试点

运行环境：Ubuntu 24.04、Python 3.12、g++ 13、Typst 0.15.1、Codex CLI 0.169.0、tmux 3.4、Noto CJK。
项目目录 `/home/clouddev/workspace/xcpc-template`；账户 clouddev 不含 sudo 权限。

## 电脑或手机 SSH

以 SSH 密钥登录 `clouddev@43.153.94.4`，运行 `~/bin/workbench`，即可进入共享 tmux 工作区。
在该工作区运行 `~/bin/ai`，或者 `~/bin/ai resume --last` 找回会话。
按 Ctrl-B，再按 D 可分离 tmux。关闭客户端不会终止 tmux 内任务；服务器重启会终止普通终端进程，Codex 会话历史仍保留，可 resume。
手机需在 SSH 客户端使用自己的密钥，将公钥加到 `~/.ssh/authorized_keys`，不要通过聊天传私钥。

Codex 官方 CLI 的远程控制为实验功能。`codex remote-control start` 启动后，运行 `codex remote-control pair` 生成短时配对码。
若手机 ChatGPT 提供手动配对入口，可用它直接控制服务器。手机实测是验收条件，不以服务端已启动代替。

## 构建和恢复

```bash
python3 print.py --check
python3 print.py
# 生成 output/pdf/template.pdf
~/bin/workbench-backup
# 校验备份后恢复到空目录；包括 Git 历史及未提交修改
bash .cloud-workbench/restore.sh ~/backups/xcpc-template-TIMESTAMP.tar.gz /tmp/xcpc-restore
```

依赖重建：在 Ubuntu 24.04 的管理员账户执行 `bash .cloud-workbench/bootstrap-ubuntu.sh`。Ubuntu 24.04 安装 `git python3 g++ tmux fonts-noto-cjk fonts-noto-mono`；Typst 0.15.1 使用官方 musl 发布包，SHA256 `a6d077d0a95eed5a2eba715b2dae06be954f624ccbf85758a03f389ded33118c`。
Codex 0.169.0 使用官方完整包 `codex-package-x86_64-unknown-linux-musl.tar.zst`，SHA256 `6d02baff052818e8c2ace3e22c1bd9ec3723524686e586fc1342e4caa04689a7`，保留包目录结构，将 bin/codex 链接到 PATH。
安装 Codex 后单独登录，认证文件不进入备份或 Git。源码恢复不需要 Codex 登录。
Typst 使用 codly 1.3.0 包；首次构建需要联网下载包。

每日 timer 备份项目（含 .git 和未提交文件，排除可重建 build/output），备份在 `~/backups`，每个文件附 SHA256。无自动删除策略，需监控磁盘。
同机备份不能应对整机丢失，还须将副本下载到其他设备；GitHub 仅保存已提交和推送内容。
不要自动提交算法改动；查看 diff 后按实际工作提交。

## 每次收工

1. 检查 git status 和 diff，把已确认的修改提交、推送。
2. 运行备份，并将至少一份副本保存到服务器之外。
3. 记录下一步；需要持续的交互任务放在 tmux 内。

## 当前下一步

验证安卓手机接入、下达真实 AI 任务并断开重连；再决定是否增加网页版编辑器和私人网络。
