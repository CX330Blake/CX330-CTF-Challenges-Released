FROM alpine:latest

WORKDIR /app

RUN apk add --no-cache build-base make socat

COPY chal.c Makefile flag.txt ./

RUN make chal

EXPOSE 10001

CMD ["socat", "-T", "60", "TCP-LISTEN:10001,reuseaddr,fork", "EXEC:./chal,pty,stderr,setsid,sane"]
