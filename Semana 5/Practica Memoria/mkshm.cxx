
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 4096 //tamaño del segmente

int main(void)
    {
        int shmid;
        if ((shmid=shmget(IPC_PRIVATE,BUFSZ,0666))<0) {
            perror("shmget");
            exit(EXIT_FAILURE);
        }
        printf("segmento creado %d\ n",shmid);
        system("ipcs -m");
        exit(EXIT_SUCCESS);
    }