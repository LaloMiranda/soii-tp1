#include "../inc/dependencies.h"

int main(int argc, char *argv[]) /* Input arguments are not used */
{
    int pid;
    int mem_comp;
    Datos *datos;
    FILE *outFile;

    if (argc != 2){
        printf("Error, falta un numero para el puerto UNIX\n");
        exit(1);
    }

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

    //Creo un hijo para correr el socket de unix
    pid = fork();
    if (pid < 0){
        perror("Error al crear el hijo1\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        configSocketUnix(argv[1], &(datos->Unix));
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
        fprintf(outFile, " Unix socket: %ld B/s\n", datos->Unix);
        datos->Unix = 0;
        fclose(outFile);
    }
    return 0;
}