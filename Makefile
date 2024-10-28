CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: server client

server: server.o client_handler.o email_utils.o
	$(CC) -o server server.o client_handler.o email_utils.o

client: client.o email_utils.o
	$(CC) -o client client.o email_utils.o

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o server client
