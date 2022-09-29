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

#define BUF_SIZE 64000 /* Buffer rx, tx max size  */
#define MAX_CLIENT 1000

typedef struct
{
	long int Unix;
} Datos;

void configSocketUnix(char *path, long *datos);

#endif