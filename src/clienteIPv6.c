#include "../inc/send.h"
int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in6 serv_addr;
	uint16_t puerto;
	size_t size;

	if (argc != 4){
		perror("Error en los argumentos: <Binario> <server-ip> <puerto> <tamaño-mensaje>\n");
		exit(0);
	}

	size = (size_t)atoi(argv[3]);
	puerto = (uint16_t)atoi(argv[2]);
    
	sockfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1){
		perror("Error al crear el socket");
		exit(1);
	}
    
	memset((char *)&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	inet_pton(AF_INET6, argv[1], &serv_addr.sin6_addr);
	serv_addr.sin6_port = htons(puerto);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Client: connection error");
		exit(1);
	}
	enviarPaquete(sockfd, size, 'c');

	return 0;
}