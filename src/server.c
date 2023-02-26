#include "../inc/dependencies.h"

int main(int argc, char *argv[]) /* Input arguments are not used */
{
    int pid, pidIPv4, pidIPv6;
    int mem_comp;
    uint16_t puertoIPv4, puertoIPv6;
    Datos *datos;
    FILE *outFile;

    if (argc != 4){
        printf("Error, falta un número para de puerto: UNIX / IPv4 / IPv6\n");
        exit(1);
    }

    //Obtengo el puerto IPv4
    puertoIPv4 = (uint16_t)atoi(argv[2]);
    //Obtengo el puerto IPv6
    puertoIPv6 = (uint16_t)atoi(argv[3]);

    // Creo un referencia a un bloque de memoria compartida
    mem_comp = shmget(ftok(".", 'S'), sizeof(datos), (IPC_CREAT | 0660));
    if (mem_comp < 0){
        perror("Error al crear bloque de memoria compartida\n");
        exit(1);
    }

    //Asigno la referencia a la memoria comparida
    datos = shmat(mem_comp, 0, 0);
    if (datos == (void *)-1){
        perror("Error al asignar memoria compartida\n");
        exit(1);
    }

    datos->IPv4 = 0;
    datos->IPv6 = 0;
    datos->Unix = 0;
    datos->total = 0;

    //Creo un hijo para correr el socket de unix
    pid = fork();
    if (pid < 0){
        perror("Error al crear el hijo para unix\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        configSocketUnix(argv[1], &(datos->Unix));
        exit(1);
    }

    //Creo un hijo para correr el socket IPv4
    pidIPv4 = fork();
    if (pidIPv4 < 0){
        perror("Error al crear el hijo para IPv4\n");
        exit(EXIT_FAILURE);
    }
    else if(pidIPv4 == 0){
        configSocketIPv4(puertoIPv4, &(datos->IPv4));
        exit(1);
    }

    //Creo un hijo para correr el socket IPv4
    pidIPv6 = fork();
    if (pidIPv6 < 0){
        perror("Error al crear el hijo para IPv6\n");
        exit(EXIT_FAILURE);
    }
    else if(pidIPv6 == 0){
        configSocketIPv6(puertoIPv6, &(datos->IPv6));
        exit(1);
    }

    while (1){
        sleep(1);
        outFile = fopen("./logs/logs.txt", "a+");

        //Abriendo un archivio
        if (outFile == NULL){
            perror("Error al abrir el archivo\n");
            exit(1);
        }
        datos->total += datos->Unix + datos->IPv4;
        fprintf(outFile, "Unix socket: %ld B/s\n", datos->Unix);
        fprintf(outFile, "IPv4 socket: %ld B/s\n", datos->IPv4);
        fprintf(outFile, "Total data received: %ld B\n", datos->total);
        fclose(outFile);
        system("clear");
        printf("---\n");
        printf("Unix: %s\t IPv4: %i\t IPv6:%i\n", argv[1], puertoIPv4, puertoIPv6);
        printf("Unix socket: %ld B/s\n", datos->Unix);
        printf("IPv4 socket: %ld B/s\n", datos->IPv4);
        printf("Total data received: %ld B\n", datos->total);
        datos->Unix = 0;
        datos->IPv4 = 0;
    }
    return 0;
}