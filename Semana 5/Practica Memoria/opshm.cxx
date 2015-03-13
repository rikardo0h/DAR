
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFSZ 4096 //tamaño del segmente

int main(int argc, char *argv[])
    {
        int shmid; //ID del segmento
        char *shmbuf; //Dirección del proceso
        int fd; //descripción dedl archivo
        int i; //contador
        
        //Espera un id de segmento
        if (argc!= 2) {
            puts("Utilización: atshm <identifier>");
            exit(EXIT_FAILURE);
        }
        shmid = atoi(argv[1]);
        
        //se adjunta el segmento
        if((shmbuf= (char *) shmat(shmid,0,0))<(char *)0){
            perror("shmat");
            exit(EXIT_FAILURE);
        }
        
        if ((shmbuf = malloc(sizeof(char )* BUFSZ)) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        for(i=0;i<BUFSZ;++i){
            shmbuf[i]=rand();
        }
        //Se escribe el contenido en bruto del segmento en el archivo
        fd = open("opshm.out",O_CREAT|O_WRONLY,0600);
        
        write(fd,shmbuf,BUFSZ);
        free(shmbuf); //no quiere perdidas de memoria
        
       
        exit(EXIT_SUCCESS);
    }
