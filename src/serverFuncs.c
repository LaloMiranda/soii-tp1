#include "../inc/dependencies.h"

void configSocketUnix(char *path, long *datos){
    int res;
	int sockfd, newsockfd, servlen;
	struct sockaddr_un cli_addr, serv_addr;
	char buffer[BUF_SIZE];
	socklen_t client_len;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Error al crear el socket\n");
		exit(1);
	}

	unlink(path);

    // Configuro el tipo de server address
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, path);

	servlen = (int)strlen(serv_addr.sun_path) + (int)sizeof(serv_addr.sun_family);

	// Asigno el socket
    res = bind(sockfd, (struct sockaddr *)&serv_addr, (socklen_t)servlen);
	if (res < 0){
		perror("Error al hacer el attach del socket\n");
		exit(1);
	}

	// Configuro el socket como listener
    res = listen(sockfd, MAX_CLIENT);
	if (res < 0){
		perror("Error al configurar el socket\n");
		exit(1);
	}

	while (1){
        //Espero un mensaje en el socket
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &client_len);

		if (newsockfd == -1){
			fprintf(stdout, "Fallo a aceptar el cliente\n");
			exit(1);
		}

		res = fork();
		if (res < 0){
			fprintf(stdout, "Fallo al hacer el fork\n");
			exit(1);
		}

		if (res == 0){
			close(sockfd);
			while (1){
                //Limpio el buffer
				memset(buffer, '\0', BUF_SIZE);

				long rec = read(newsockfd, buffer, (BUF_SIZE - 1));
				if (rec < 0){
					fprintf(stdout, "Error al recibir el mensaje\n");
					exit(1);
				}
				if (rec == 0){
					fprintf(stdout, "Cliente Unix desconectado\n");
					exit(1);
				}
				*datos = *datos + rec;
			}
		}
		else{
			fprintf(stdout, "Nuevo cliente en Unix socket\n");
			close(newsockfd);
		}
	}
}


void configSocketIPv4(uint16_t puerto, long *datos){
	int serverSocket;
	char buffer[BUF_SIZE];
	struct sockaddr_in clientAddress;
	socklen_t client_len;
	int cliente_socket_fd;

	serverSocket = setUpIPv4(puerto);
	client_len = sizeof(clientAddress);

	while (1){
		cliente_socket_fd = accept(serverSocket, (struct sockaddr *)&clientAddress, &client_len);
		if (cliente_socket_fd == -1){
			fprintf(stdout, "Fallo al aceptar el cliente IPv4\n");
			exit(1);
		}

		//Creo un hijo para atender el cliente
		int ch_pid = fork();
		if (ch_pid == -1){
			fprintf(stdout, "Fallo al hacer el fork IPv4\n");
			exit(1);
		}

		if (ch_pid == 0){
			close(serverSocket);
			while (1){
				memset(buffer, 0, BUF_SIZE);
				ssize_t rec = read(cliente_socket_fd, buffer, (BUF_SIZE - 1));
				if (rec == -1){
					fprintf(stdout, "Fallo al recibir el mensaje IPv4\n");
					exit(1);
				}
				if (rec == 0){
					fprintf(stdout, "Cliente IPv4 se desconectado\n");
					exit(1);
				}
				*datos = *datos + rec;
			}
		}
		else{
			fprintf(stdout, "Nuevo cliente IPv4\n");
			close(cliente_socket_fd);
		}
	}
}

int setUpIPv4(uint16_t puerto){
	int serverSocket;
	struct sockaddr_in servAddr;

	//Creo el socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0){
		perror("ERROR: Problemas con la creacion del socket IPv4\n");
		exit(0);
	}

	memset(&servAddr, 0, sizeof(servAddr));	//Vacio la estructura
	servAddr.sin_family = AF_INET;			//IPv4
	servAddr.sin_addr.s_addr = INADDR_ANY;	//IPs de la pc
	servAddr.sin_port = htons(puerto);		//Puerto del socket

	//Asigno el socket
	if (bind(serverSocket, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
		perror("ERROR: No fue posible asignar el socket IPv4\n");
		close(serverSocket);
		exit(0);
	}

	//Configuro el socket como listener
	if (listen(serverSocket, MAX_CLIENT) < 0){
		perror("Error al poner el socket IPv4 del server como listener\n");
		exit(EXIT_FAILURE);
	}
	return serverSocket;
}