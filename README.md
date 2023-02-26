Sistemas Operativos II - Laboratorio I IPC
###  Ingeniería en Compitación - FCEFyN - UNC
# Interprocess Communication

## Introducción
Los mecanismos de IPC permiten a los procesos intercambiar información. Hemos visto que se pueden clasificar en dos grandes grupos, los de transferencia de datos (pipe, FIFO, message queue, sockets, etc.) y los de memoria compartida (shared memory, memory mapping, etc.). Todo este conjunto de mecanismos son sumamente útiles en todo proyecto y es lo que motiva el presente trabajo.

## Objetivo
El objetivo del presente trabajo práctico es que el estudiante sea capaz de diseñar e implementar un software que haga uso de los mecanismos de IPC que provee el Sistema Operativo, implementando lo visto en el teórico, práctico y haciendo uso todos los conocimientos adquiridos en Ingeniería de Software y Sistemas Operativos I.

## Desarrollo
Se pide que diseñe, implemente y testee un conjunto de aplicaciones (desarrollado en lenguaje C) de una arquitectura cliente servidor con al menos 3 protocolos de la familia descriptas en  <sys/socket.h>.  

![Diagrama de Componentes](/img/block_diagram.jpg)
*Figura 1: Diagrama de Componentes del sistema*

### Servidor
El servidor recibe los bytes de cada cliente filtrando por protocolo par analizar la cantidad recibida en por medio de cada uno de ellos. Esta información es entregada en la consola del servidor, junto a los puertos para cada una de las conexiones, y en un archivo de texto dentro de la carpeta **logs**.
Ambas fuentes de información se actualizan y vez por segundo.

Para correr el servidor:

```shell
./bin/server.out [Unix Port] [IPv4 Port] [IPv6 Port]
```

### Cliente Unix
Cliente utilizado para conexiones Unix que manda su paquete una vez por segundo, para correr este cliente:

```shell
./bin/clienteIPv4.out [IP del servidor] [Puerto] [Tamaño del paquete]
```

### Cliente IPv4
Cliente utilizado para conexiones IPv4 que manda su paquete una vez por segundo, para correr este cliente:

```shell
./bin/clienteIPv4.out [IP del servidor] [Puerto] [Tamaño del paquete]
```

### Cliente IPv6
Cliente utilizado para conexiones IPv6 que manda su paquete una vez por segundo, para correr este cliente:

```shell
./bin/clienteIPv6.out [IP del servidor] [Puerto] [Tamaño del paquete]
```

## Dependencias
Las dependencias son:
- make
- binutils
- build-essential

Se pueden instalar corriendo el archivo **installDependencias.sh**

## Links / Referencias
- [Git Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows)

[workflow]: https://www.atlassian.com/git/tutorials/comparing-workflows "Git Workflow"

