CC = gcc
CFLAGS = -pthread

all: server client

server: server.c user_handler.c email_handler.c socket_utils.c
    $(CC) $(CFLAGS) -o server server.c user_handler.c email_handler.c socket_utils.c -lssl -lcrypto

client: client.c socket_utils.c
    $(CC) -o client client.c socket_utils.c
