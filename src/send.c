#include "../inc/send.h"

void enviarPaquete(int socket, size_t cant, char letter){
    //Creo el buffer con el tamaño que le pase y lo lleno de ceros
    char buff[cant];
    memset(buff, letter, cant);

    ssize_t res;
    while (1){
        //Mando el mensaje y espero un segundo
        res = write(socket, buff, cant);
        if (res < 0){
            printf("Error al mandar mensaje\n");
            exit(1);
        }
        sleep(1);
    }
}