#ifndef _LIBSCAN_H_
#define _LIBSCAN_H_

/*Las lineas anteriores siempre van y se nombran segun el nombre que se le
 haya dado al archivo pero en mayúsculas*/
extern int scanIPS(int n);

extern void ProcessPacket(unsigned char* , int);
extern void print_ip_header(unsigned char* , int);
extern void print_tcp_packet(unsigned char * , int );
extern void print_udp_packet(unsigned char * , int );
extern void print_icmp_packet(unsigned char* , int );
extern void PrintData (unsigned char* , int);

#endif