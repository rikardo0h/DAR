#include <stdio.h>
#include "libPort.h" // Se incluye la lib


int main (int argc, char *argv[])
{
    char c[8] = "chicos";
    printf("Llamando a funcion imprimir(char cad)\n");
    readPorts(argv);
    return 0;
}