CC=gcc
CFLAGS= -g -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

all: clean obj/send.o obj/serverFuncs.o bin/server bin/clienteUnix bin/clienteIPv4 bin/clienteIPv6 cleanObj

bin/server:
	$(CC) $(CFLAGS) ./src/server.c obj/serverFuncs.o -o ./bin/server.out -lrt

obj/serverFuncs.o:
	$(CC) $(CFLAGS) -c ./src/serverFuncs.c -o obj/serverFuncs.o

obj/send.o:
	$(CC) $(CFLAGS) -c ./src/send.c -o obj/send.o

bin/clienteUnix:
	$(CC) $(CFLAGS) ./src/clienteUnix.c obj/send.o -o ./bin/clienteUnix.out -lrt

bin/clienteIPv4:
	$(CC) $(CFLAGS) ./src/clienteIPv4.c obj/send.o -o ./bin/clienteIPv4.out -lrt

bin/clienteIPv6:
	$(CC) $(CFLAGS) ./src/clienteIPv6.c obj/send.o -o ./bin/clienteIPv6.out -lrt

cleanObj:
	rm -f ./obj/*

clean:
	rm -f ./bin/*
	rm -f ./obj/*
	rm -f ./logs/*.txt
	