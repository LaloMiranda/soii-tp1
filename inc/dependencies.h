#ifndef _DEPENDENCIES_
#define _DEPENDENCIES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Include de memoria compartido
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

//Include de sockets
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 64000
#define MAX_CLIENT 1000

typedef struct
{
	long int Unix;
	long int IPv4;
	long int IPv6;
	long int total;
} Datos;

void configSocketUnix(char *path, long *datos);

void configSocketIPv4(uint16_t puerto, long *datos);
int setUpIPv4(uint16_t puerto);

void configSocketIPv6(uint16_t puerto, long *datos);
int setUpIPv6(uint16_t puerto);
#endif