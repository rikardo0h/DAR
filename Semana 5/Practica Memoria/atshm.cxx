
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 4096 //tamaño del segmente

int main(int argc, char *argv[])
    {
        int shmid; //ID del segmento
        char *shmbuf; //Dirección del proceso
        
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
        //Dota esta adjunto
        printf("Segmmento adjunto en %p \n", shmbuf);
        
        //Realmente estamos adjuntos
        system("ipcs -m");
        
        //Lo quita
        if ((shmdt(shmbuf))<0) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
        puts("segmento quitado");
        //si, lo hemos hecho
        system("ipcs -m");
        exit(EXIT_SUCCESS);
    }
