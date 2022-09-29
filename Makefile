CC=gcc
CFLAGS= -g -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

all: clean obj/send.o obj/serverFuncs.o bin/server bin/clienteUnix

bin/server:
	$(CC) $(CFLAGS) ./src/server.c obj/serverFuncs.o -o ./bin/server.out -lrt

obj/serverFuncs.o:
	$(CC) $(CFLAGS) -c ./src/serverFuncs.c -o obj/serverFuncs.o

obj/send.o:
	$(CC) $(CFLAGS) -c ./src/send.c -o obj/send.o

bin/clienteUnix:
	$(CC) $(CFLAGS) ./src/clienteUnix.c obj/send.o -o ./bin/clienteUnix.out -lrt

clean:
	rm -f ./bin/*
	rm -f ./obj/*
	