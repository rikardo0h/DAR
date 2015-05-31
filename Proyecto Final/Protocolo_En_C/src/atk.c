#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

struct atak
{
    int8_t type;
    int8_t count;
    int8_t ack;
    char msg[100];
};

void fillAtak(struct atak *);
void printAtakMsg(struct atak *);

int main(int argc, char * argv[])
{
	if (argc < 2) 
    {    	
        fprintf(stderr,"ERROR, no port provided\n");        
        exit(1);
    }

	int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[103];
    struct atak msgAtak;

    bzero((char *) &serv_addr, sizeof(serv_addr));
	/*------------------------------*/
	/*----------- Servidor ---------*/
	/*------------------------------*/
	while(true)
    {
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	    
	    if (sockfd < 0)
	    {
	        perror("ERROR opening socket");
	        exit(1);
	    }

	    portno = atoi(argv[1]);
	    serv_addr.sin_port = htons(portno);
	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_addr.s_addr = INADDR_ANY;    

	    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	    {
	        perror("ERROR on binding");
	        exit(1);
	    }

	    listen(sockfd,1);
		/*------------------------------*/
		/*----------- Servidor ---------*/
		/*------------------------------*/
    
	    /*------------------------------*/
		/*----------- Cliente ----------*/
		/*------------------------------*/    
	    clilen = sizeof(cli_addr);
	    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	    if (newsockfd < 0) 
	    {
	          perror("ERROR on accept");
	          exit(1);
	    }
		/*------------------------------*/
		/*----------- Cliente ----------*/
		/*------------------------------*/

	    bool cond = true;
		char * msj = NULL;
		char * pointer = NULL;


		while(cond)		
		{			
	    	/*------------------------------*/
			/*----------- Envío ------------*/
			/*------------------------------*/
			
/********* Recibiendo de la INTERFAZ ***************/
 /*       	int sockdvc, newsockdvc, portnodvc, ndvc;
		    socklen_t clilent;
		    struct sockaddr_in serv_addrdvc, cli_addrdvc;				    

		    bzero((char *) &serv_addrdvc, sizeof(serv_addrdvc));
			/*------------------------------*/
			/*----------- Servidor ---------*/
			/*------------------------------*/
	/*		sockdvc = socket(AF_INET, SOCK_STREAM, 0);
		    
		    if (sockdvc < 0)
		    {
		        perror("ERROR opening socket INTERFAZ");
		        exit(1);
		    }

		    portnodvc = 10000;
		    serv_addrdvc.sin_port = htons(portnodvc);
		    serv_addrdvc.sin_family = AF_INET;
		    serv_addrdvc.sin_addr.s_addr = INADDR_ANY;    

		     if (bind(sockdvc, (struct sockaddr *) &serv_addrdvc, sizeof(serv_addrdvc)) < 0) 
		    {
		        perror("ERROR on binding INTERFAZ");
		        exit(1);
		    }

		    listen(sockdvc,1);
			/*------------------------------*/
			/*----------- Servidor ---------*/
			/*------------------------------*/

		    /*------------------------------*/
			/*----------- Cliente ----------*/
			/*------------------------------*/    
/*		    clilent = sizeof(cli_addrdvc);
		    newsockdvc = accept(sockdvc, (struct sockaddr *) &cli_addrdvc, &clilent);
		    if (newsockdvc < 0) 
		    {
		          perror("ERROR on accept INTERFAZ");
		          exit(1);
		    }
			printf("%s\n", "Cliente conectado");
			
		    /*Recibiendo Solicitud desde INTERFAZ*/

	/*		printf("%s\n", "Recibiendo ACK...");				
			n = read(newsockdvc,buffer,103);
	        if (n < 0)
	        { 
				perror("ERROR reading from socket");
				exit(1);
	        }	        
	        bzero(&msgAtak, sizeof(msgAtak));
	        memcpy(&msgAtak, buffer, (int) sizeof(msgAtak));

	        close(sockdvc);	
	    	close(newsockdvc);
			/*Recibiendo Solicitud desde INTERFAZ*/

/********* Recibiendo de la INTERFAZ ***************/
	        
			int op ;//= msgAtak.type;			
			printf("Read Option: \n");
			scanf("%d",&op);
			bzero(&msgAtak, sizeof(msgAtak));	
			printf("OP is: %i\n", op);
	    	switch(op)
			{
				case 1:				
					/*Enviando solicitud*/
					printf("%s\n", "Enviando solicitud...");
					msgAtak.type = 1;
					msgAtak.count = 1;
					msgAtak.ack = 0;
					strncpy(msgAtak.msg, "Solicitando", 12);
					printf("Tamaño: %i\n", (int)sizeof(msgAtak));
					printf("%s\n", "GET");				
					memcpy(buffer, &msgAtak, sizeof(msgAtak));
					n = write(newsockfd,buffer,strlen(buffer));							
			        if (n < 0)
			        { 
			            perror("ERROR writing to socket");
			            exit(1);
					}				
					/*Enviando solicitud*/


					/*Recibiendo ACK de solicitud recibida*/
					printf("%s\n", "Recibiendo ACK...");				
					n = read(newsockfd,buffer,103);
			        if (n < 0)
			        { 
			             perror("ERROR reading from socket");
			             exit(1);
			        }
			        bzero(&msgAtak, sizeof(msgAtak));
			        memcpy(&msgAtak, buffer, (int) sizeof(msgAtak));
			        /*Recibiendo ACK de solicitud recibida*/

					/**RESPUESTA A INTERFAZ*/
					/*n = write(newsockdvc, buffer, sizeof(buffer));							
			        if (n < 0)
			        { 
			            perror("ERROR writing to socket INTERFAZ");
			            exit(1);
					}*/	
										    							
					/**RESPUESTA A INTERFAZ*/

			        printAtakMsg(&msgAtak);		
			        /*Comprobando el ACK y preparandose para recibir*/
			        if(msgAtak.ack == 1)
			        {
			        	int i, count = msgAtak.count;	

			        	/*Enviando ACK de Enterado*/
			        	printf("%s\n", "Enviando ACK de Enterado..");		        	
			        	msgAtak.type = 1;
						msgAtak.count = 1;
						msgAtak.ack = 1;
						strncpy(msgAtak.msg, "Enterado", 11);
						memcpy(buffer, &msgAtak, sizeof(msgAtak));
						printAtakMsg(&msgAtak);
						n = write(newsockfd,buffer,strlen(buffer));
				        if (n < 0)
				        { 
				            perror("ERROR writing to socket");
				            exit(1);
						}				
						/*Enviando ACK de Enterado*/
						

						/*Recibiendo paquetes segun el numero a recibir*/
						printf("%s\n", "Recibiendo mensajes...");
						msj = malloc((sizeof(msgAtak.msg)*count));
						

			        	for (i = 0; i < count; ++i)
			        	{			        		
			        		usleep(1);
			        		printf("Recibiendo mensaje %i de %i.\n", i+1, count);				
							n = read(newsockfd,buffer,103);													
					        if (n < 0)
					        { 
					             perror("ERROR reading from socket");
					             exit(1);
					        }					        

					        /**RESPUESTA A INTERFAZ*/
							/*n = write(newsockdvc, buffer, sizeof(buffer));							
					        if (n < 0)
					        { 
					            perror("ERROR writing to socket INTERFAZ");
					            exit(1);
							}*/																			
							/**RESPUESTA A INTERFAZ*/

							printf("WRITE RETURN: %i\n", n);

					        bzero(&msgAtak, sizeof(msgAtak));
					        memcpy(&msgAtak, buffer, (int) 103);
					        printAtakMsg(&msgAtak);		

					        printf("Copiando: %i\n", sizeof(msgAtak.msg)); 
					        strncpy(msj, msgAtak.msg, 100);				        				        
					        msj += sizeof(msgAtak.msg);
					        
					        usleep(1);
					        if(msgAtak.ack == 0)
			        		{
			        			/*Enviando de Enterado*/
					        	msgAtak.type = 1;
								msgAtak.count = 1;
								msgAtak.ack = 1;
								bzero(msgAtak.msg, sizeof(msgAtak.msg));
								strncpy(msgAtak.msg, "Recibido", 8);
								memcpy(buffer, &msgAtak, sizeof(msgAtak));
								n = write(newsockfd,buffer,strlen(buffer));
						        if (n < 0)
						        { 
						            perror("ERROR writing to socket");
						            exit(1);
								}
								/*Enviando de Enterado*/
			        		}
			        	}			        	
			        	/*Recibiendo paquetes segun el numero a recibir*/

			        	msj -= (count * 100);
			        	printf("Mensaje: %s\n", msj);

			        }		        			        			        
			        //printf("Mensaje recibido:\n\t%s\n", msgAtak.msg);		        
					break;
				case 2:
					/*Enviando solicitud*/
					printf("%s\n", "Enviando solicitud...");
					msgAtak.type = 2;
					msgAtak.count = 1;
					msgAtak.ack = 0;
					strncpy(msgAtak.msg, "Solicitando", 12);
					printf("Tamaño: %i\n", (int) sizeof(msgAtak));
					printf("%s\n", "SCAN IP'S");				
					memcpy(buffer, &msgAtak, sizeof(msgAtak));
					n = write(newsockfd,buffer,strlen(buffer));							
			        if (n < 0)
			        { 
			            perror("ERROR writing to socket");
			            exit(1);
					}				
					/*Enviando solicitud*/


					/*Recibiendo ACK de solicitud recibida*/
					printf("%s\n", "Recibiendo ACK...");				
					n = read(newsockfd,buffer,103);
			        if (n < 0)
			        { 
			             perror("ERROR reading from socket");
			             exit(1);
			        }
			        bzero(&msgAtak, sizeof(msgAtak));
			        memcpy(&msgAtak, buffer, (int) sizeof(msgAtak));
			        /*Recibiendo ACK de solicitud recibida*/

					/**RESPUESTA A INTERFAZ*/
					/*n = write(newsockdvc, buffer, sizeof(buffer));							
			        if (n < 0)
			        { 
			            perror("ERROR writing to socket INTERFAZ");
			            exit(1);
					}*/	
										    							
					/**RESPUESTA A INTERFAZ*/

			        printAtakMsg(&msgAtak);		
			        /*Comprobando el ACK y preparandose para recibir*/
			        if(msgAtak.ack == 1)
			        {
			        	int ib, countb = msgAtak.count;	

			        	/*Enviando ACK de Enterado*/
			        	printf("%s\n", "Enviando ACK de Enterado..");		        	
			        	msgAtak.type = 2;
						msgAtak.count = 1;
						msgAtak.ack = 1;
						strncpy(msgAtak.msg, "Enterado", 11);
						memcpy(buffer, &msgAtak, sizeof(msgAtak));
						printAtakMsg(&msgAtak);
						n = write(newsockfd,buffer,strlen(buffer));
				        if (n < 0)
				        { 
				            perror("ERROR writing to socket");
				            exit(1);
						}				
						/*Enviando ACK de Enterado*/
						

						/*Recibiendo paquetes segun el numero a recibir*/
						printf("%s  %i\n", "Recibiendo mensajes...",countb);
						msj = malloc((sizeof(msgAtak.msg)*countb));
						

			        	for (ib = 0; ib < countb; ++ib)
			        	{			        		
			        		usleep(1);
			        		printf("Recibiendo mensaje %i de %i.\n", ib+1, countb);				
							n = read(newsockfd,buffer,103);													
					        if (n < 0)
					        { 
					             perror("ERROR reading from socket");
					             exit(1);
					        }					        

					        /**RESPUESTA A INTERFAZ*/
							/*n = write(newsockdvc, buffer, sizeof(buffer));							
					        if (n < 0)
					        { 
					            perror("ERROR writing to socket INTERFAZ");
					            exit(1);
							}*/																			
							/**RESPUESTA A INTERFAZ*/

							printf("WRITE RETURN: %i\n", n);
					        bzero(&msgAtak, sizeof(msgAtak));
					        memcpy(&msgAtak, buffer, (int) 103);
					        printAtakMsg(&msgAtak);		

					        printf("Copiando: %i\n", sizeof(msgAtak.msg));
					        strncpy(msj, msgAtak.msg, 100);				        				        
					        msj += sizeof(msgAtak.msg);
					        usleep(1);
					        if(msgAtak.ack == 0)
			        		{
			        			/*Enviando de Enterado*/
					        	msgAtak.type = 2;
								msgAtak.count = 1;
								msgAtak.ack = 1;
								bzero(msgAtak.msg, sizeof(msgAtak.msg));
								strncpy(msgAtak.msg, "Recibido", 8);
								memcpy(buffer, &msgAtak, sizeof(msgAtak));
								n = write(newsockfd,buffer,strlen(buffer));
						        if (n < 0)
						        { 
						            perror("ERROR writing to socket");
						            exit(1);
								}
								/*Enviando de Enterado*/
			        		}
			        	}			        	
			        	/*Recibiendo paquetes segun el numero a recibir*/

			        	msj -= (countb * 100);
			        	printf("Mensaje: %s\n", msj);

			        }		        			        			        
			        //printf("Mensaje recibido:\n\t%s\n", msgAtak.msg);		        
					break;
				case 3:
					//cond = false;
					msgAtak.type = 3;
					printf("Tamaño: %i\n", (int) sizeof(msgAtak));
					printf("%s\n", "Bye");				
					memcpy(buffer, &msgAtak, sizeof(msgAtak));
					n = write(newsockfd,buffer,strlen(buffer));
			        if (n < 0)
			        { 
			            perror("ERROR writing to socket");
			            exit(1);
					}
					printf("%s\n", "Recibiendo...");
					n = read(newsockfd,buffer,101);
			        if (n < 0)
			        { 
			             perror("ERROR reading from socket");
			             exit(1);
			        }
			        memcpy(&msgAtak, buffer, (int) sizeof(msgAtak));
			        printf("Mensaje recibido:\n\t%s\n", msgAtak.msg);
					break;
				default:
					cond = false;
					break;			
			}   		     		
		    /*------------------------------*/
			/*----------- Envío ------------*/
			/*------------------------------*/			
		}	
		
		close(newsockfd);
		close(sockfd);
	}    
	return 0;
}

void printAtakMsg(struct atak * msg)
{
    printf("=========================\n");
	printf("Type:\t%i\n", msg->type);
	printf("Count:\t%i\n", msg->count);
	printf("ACK:\t%i\n", msg->ack);
	printf("Message:\t%s\n", msg->msg);
	printf("=========================\n");
}