FROM python:3.10

RUN apt-get update && apt-get install socat -y

WORKDIR /app
COPY chal.py .

RUN useradd -ms /bin/bash chal
USER chal
EXPOSE <DOCKER PORT>
ENTRYPOINT ["socat", "TCP-LISTEN:<DOCKER PORT>, fork,reuseaddr", "EXEC:'python chal.py', stderr"]