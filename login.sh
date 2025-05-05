#!/bin/bash

# 配置参数
USER="root"           # SSH 用户名
HOST="192.168.1.100"  # Milkv-Duo 的 IP 地址
PORT="22"             # SSH 端口（默认 22）
PASS="milkv"  # SSH 密码（建议改用密钥认证）
COMMANDS=(
    "ls -l /etc"      # 要执行的命令列表
    "df -h"
    "date"
)

# 通过 SSH 执行命令
for cmd in "${COMMANDS[@]}"; do
    sshpass -p "$PASS" ssh -p "$PORT" -o StrictHostKeyChecking=no "$USER@$HOST" "$cmd"
done