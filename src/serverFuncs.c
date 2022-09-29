#include "../inc/dependencies.h"

void configSocketUnix(char *path, long *datos){
    int res;
	int sockfd, newsockfd, servlen;
	struct sockaddr_un cli_addr, serv_addr;
	char buffer[BUF_SIZE];
	socklen_t client_len;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error al crear el socket\n");
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
		printf("Error al hacer el attach del socket\n");
		exit(1);
	}

	// Configuro el socket como listener
    res = listen(sockfd, MAX_CLIENT);
	if (res < 0){
		printf("Error al configurar el socket\n");
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
