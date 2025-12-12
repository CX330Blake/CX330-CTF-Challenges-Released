FROM alpine:latest

WORKDIR /app

RUN apk add --no-cache build-base make socat

# 把檔案確實複製到 /app
COPY chal.c Makefile flag.txt ./

# 指定要 build 的 target，並檢查目錄內容方便 debug
RUN make chal && ls -al

EXPOSE 10001

CMD ["socat", "-T", "60", "TCP-LISTEN:10001,reuseaddr,fork", "EXEC:./chal,pty,stderr,setsid,sane"]
