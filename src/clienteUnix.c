#include "../inc/send.h"

int main(int argc, char *argv[])
{
    int res;
	int sockfd;
	ssize_t servlen;
	struct sockaddr_un serv_addr;
	size_t size;

	if (argc < 3){
		fprintf(stderr, "Faltan argumentos: %s <server> <tamaño>\n", argv[0]);
		exit(0);
	}

	size = (size_t)atoi(argv[2]);

	memset((char *)&serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1]);

	servlen = (long int)strlen(serv_addr.sun_path);
	servlen = servlen + (ssize_t)sizeof(serv_addr.sun_family);

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
		printf("Error al crear el socket");
		exit(1);
	}

	printf("Path al socket UNIX: %s\n", serv_addr.sun_path);
    res = connect(sockfd, (struct sockaddr *)&serv_addr, (socklen_t)servlen);
	if (res < 0){
		printf("Error al establecer la conexion\n");
		exit(1);
	}
	enviarPaquete(sockfd, size, 'b');
	return 0;
}
