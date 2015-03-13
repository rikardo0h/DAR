#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <usb.h>

int main(void)
{
	int dispositivos[10];
	int aux=0;
	int fd; /* Descriptor del FIFO*/
	int len; /* Bytes escritos en el FIFO*/
	char buf[PIPE_BUF]; /* Se asegurs de escrituras atomicas*/
	time_t tp;

	/* Nos identificaremos*/
	printf("I am %d\n", getpid());

	/* Abre el FIFO de sólo escritura*/
	if ((fd = open("fifo1", O_WRONLY)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	/* Genera algunos datos para escribir*/

    struct usb_bus *bus;
    struct usb_device *dev;
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next)
        for (dev = bus->devices; dev; dev = dev->next){
	    dispositivos[aux]=dev->descriptor.idVendor;
	    dispositivos[aux+1]=dev->descriptor.idProduct;
            //printf("\tID_VENDOR = %04x\n", dev->descriptor.idVendor);
            //printf("\tID_PRODUCT = %04x\n", dev->descriptor.idProduct);
	    aux=aux+2;
           // printf("\tID_PRODUCT = %04x\n", dev->descriptor.idUUID);
        }

	//Almacenar
	int x=0;
	printf("\tID = %d\n",aux/2);
	while(x<aux){
		//printf("\tID_VENDOR = %04x\n", dispositivos[x]);
		//printf("\tID_PRODUC = %04x\n", dispositivos[x+1]);
		x=x+2;
	}


	while(1)
	{
	
		time(&tp);
		 for (bus = usb_busses; bus; bus = bus->next)
			for (dev = bus->devices; dev; dev = dev->next){
			    printf("\tID_VENDOR = %04x\n", dev->descriptor.idVendor);
			    printf("\tID_PRODUCT = %04x\n", dev->descriptor.idProduct);

			    len=sprintf(buf, "%04x%04x", dev->descriptor.idVendor, dev->descriptor.idProduct);
			    if((write(fd, buf, len+1)) < 0)
				{
					perror("write");
					exit(EXIT_FAILURE);
				}
			}
	}
		sleep(10);
		exit(EXIT_SUCCESS);
}
