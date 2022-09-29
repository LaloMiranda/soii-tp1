#ifndef _SEND_
#define _SEND_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

void enviarPaquete(int socket, size_t cant, char letter);

#endif