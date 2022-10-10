#include "../inc/send.h"

int main(int argc, char *argv[])
{
	int sockfd;
	uint16_t puerto;
	size_t size;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	if (argc != 4){
		perror("Error en los argumentos: <Binario> <server-ip> <puerto> <tamaño-mensaje>\n");
		exit(0);
	}

	size = (size_t)atoi(argv[3]);
	puerto = (uint16_t)atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		perror("Error al crear el socket");
		exit(1);
	}
	server = gethostbyname(argv[1]);

	memset((char *)&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		  (char *)&serv_addr.sin_addr.s_addr,
		  (size_t)server->h_length);
	serv_addr.sin_port = htons(puerto);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Client: connection error");
		exit(1);
	}
	enviarPaquete(sockfd, size, 'a');
	return 0;
}
