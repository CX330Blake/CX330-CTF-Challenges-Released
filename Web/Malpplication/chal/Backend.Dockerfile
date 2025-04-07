# 使用 PHP 7.4 CLI 作為後端基礎環境
FROM php:8-cli

WORKDIR /var/www/html

# 建立 CTF 用戶
RUN groupadd -r ctf && useradd -r -g ctf ctf

# 複製 Backend 代碼
COPY Backend/ /var/www/html/

# 設置 flag.txt
RUN echo "SITCON{Ez_W3b5he11_Up10ad_r1gh7?}" > /flag.txt

# 設定權限
RUN chown -R ctf:ctf /var/www/html

# 開放端口
EXPOSE 1337

# 切換用戶
USER ctf

# 啟動 PHP 內建伺服器
CMD ["php", "-S", "0.0.0.0:1337", "-t", "/var/www/html"]
