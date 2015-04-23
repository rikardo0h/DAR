#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

using namespace std;

/*Compilar con la siguiente directiva:
    g++ -std=c++11 mapport.cxx mapport*/
//#define MAX_FOO  20

int portno = 3306;
string cadena,name;
int i=0;

ifstream ifile ("protlist.csv");
int isFile(){
    if(ifile.is_open()){
        return 1;
    }
    return 0;
}

int readPorts(char *argv[]){
    string sSokect, sAux;
    if(isFile()){
        char *hostname = argv[1];
        char ch[20];
        ///
        while(!ifile.eof())
        {
            ifile >> sAux;
            size_t stToken = sAux.find(",");
            sSokect += sAux.substr(0, stToken);
            name=sAux.substr(0, stToken);
            sSokect += sAux.substr(stToken);
            
            /*Inicio_estado del puerto*/
            string::size_type sz;
            stToken++;
            portno = stoi (sAux.substr(stToken),&sz);
           // cout << portno;
            //char hostnameb[16] = "192.168.1.150";
            char *hostname = argv[1];
            /*char *hostname = hostnameb;*/
            
            int sockfd;
            struct sockaddr_in serv_addr;
            struct hostent *server;
            
            /*Crea un socket no ligado a un dominio.Devuelve un descriptor.
             Parametros: domain (Especifica e dominio de comunicaciones en el cual el
             soket sera creado), type (Especifica el tipo de socket a crear),
             protocol (Especifica el protocolo a ser usado, en 0 el socket usa el
             protocolo adecuado para la situación). Usar SOCK_STREAM para TCP o
             SOCK_DGRAM para UDP.*/
            string sTipoSokect = argv[1];
            //cout << sTipoSokect;
            if(sTipoSokect.compare("TCP"))
            {
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
            }
            else
            {
                if(sTipoSokect.compare("UDP"))
                    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                else
                {
                    printf("%c\n", "Error en el paramtro del protocolo");
                    return 0;
                }
            }
            
            /*Devuelve un entero no negativo en caso de que la operacion de creacióm
             del socket se realice correctamente, de otra manera devuelve -1*/
            if (sockfd < 0)
            {
                perror("ERROR opening socket");
            }
            
            server = gethostbyname(hostname);
            
            if (server == NULL)
            {
                fprintf(stderr,"ERROR, no such host\n");
                exit(0);
            }
            //creacion del paquete
            
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr,
                  (char *)&serv_addr.sin_addr.s_addr,
                  server->h_length);
            
            serv_addr.sin_port = htons(portno);
            if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            {
                //printf("Port is closed");
                sSokect += "     ->    closed\n";
                cadena += name+":"+std::to_string(portno)+":0,\n";
            } else
            {
                //printf("Port is active");
                sSokect += "     ->    active\n";
                cadena +=  name+":"+std::to_string(portno)+":1,\n";
            }
            close(sockfd);
            /*Fin_estado del puerto*/
        }

        
        ////
    }else{
        printf("Error abriendo..\n");
        return 0;
    }
    ifile.close();
    cout << "Resultadoooooooooo \n "<<cadena<<"  "<<name;
}