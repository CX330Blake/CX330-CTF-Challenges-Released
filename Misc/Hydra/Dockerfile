# 基於 Ubuntu 最新版本
FROM ubuntu:latest

# 更新包並安裝 OpenSSH Server
RUN apt-get update && apt-get install -y openssh-server sudo

# 創建 SSH 目錄
RUN mkdir /var/run/sshd

# 創建一個新用戶 BEEF
RUN useradd -m -d /home/BEEF -s /bin/bash BEEF

# 設置新用戶 BEEF 的密碼
RUN echo 'BEEF:thinkpink' | chpasswd

# 允許通過 SSH 登錄
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

# 設定 SSH 守護進程以允許 Docker 的後台運行
RUN echo 'export VISIBLE=now' >> /etc/profile

# 開放 22 端口
EXPOSE 22

# 啟動 SSH 服務
CMD ["/usr/sbin/sshd", "-D"]
