FROM debian:bullseye-slim

# Install socat
RUN apt update && apt install -y socat && \
    useradd -m ctf && \
    mkdir /chal && \
    chown ctf:ctf /chal && \
    rm -rf /var/lib/apt/lists/*

COPY chal /chal/chal
COPY flag.txt /chal/flag.txt
RUN chmod +x /chal/chal

USER ctf
WORKDIR /chal

EXPOSE 31605

CMD socat TCP-LISTEN:31605,reuseaddr,fork EXEC:./chal,stderr
