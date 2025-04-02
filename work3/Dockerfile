FROM gcc:latest

WORKDIR /app

COPY . .

RUN gcc -Wall -o stuManager stuManager.c

ENTRYPOINT ["./stuManager", "stdinfo.db"]