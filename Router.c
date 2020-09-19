#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT_C 3333
#define PORT_S 2222
#define PORT_R 1111

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
    puts(pname);
    printf("%s ip= %s, port= %d\n", msg, inet_ntoa(sin->sin_addr), sin->sin_port);
}

// Random (double)
double Random()
{
	return(double)rand()/(double)RAND_MAX;
}

int main(int args,char *argv[])
{
	double random,y;
	printf("Enter your choice \n");
	scanf("%lf", &y);
	printf("%f\n",y);

	char name[1024];
	int socket_fd;
	unsigned int fsize;
	struct sockaddr_in serv_ad,from, destA, destC;
	
    // build a socket, and make all the bytes ZERO
	socket_fd=socket(AF_INET,SOCK_DGRAM,0);
	bzero((char *) &serv_ad,sizeof(serv_ad));
	bzero((char *) &from,sizeof(from));
	bzero((char *) &destA,sizeof(destA));
	bzero((char *) &destC,sizeof(destC));

	serv_ad.sin_family=(short)AF_INET;
    serv_ad.sin_addr.s_addr=htonl(INADDR_ANY); // host to network long
    serv_ad.sin_port=PORT_R;

	destA.sin_family=(short)AF_INET;
    destA.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    destA.sin_port=PORT_C;

	destC.sin_family=(short)AF_INET;
    destC.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    destC.sin_port=PORT_S;
	
    // connect between port and server, return 0 in success. 
	bind(socket_fd,(struct sockaddr *) &serv_ad,sizeof(serv_ad));

    // infinite loop
	while(1)
	{
	fsize=sizeof(from);
	bzero(name,1024);
	recvfrom(socket_fd,name,1024,0,(struct sockaddr *)&from,&fsize);
	printsin(&from, "UDP-SERVER ", " Packet from:");
	puts(name);
	fflush(stdout);
	if(from.sin_port==PORT_C)
		{
			random=Random();

			if(random>y)
			{
			sendto(socket_fd,name,1024,0,(struct sockaddr *)&destC,sizeof(destC));
			}
			else {
			strcpy(name,"The messege is lost \n");
			sendto(socket_fd,name,1024,0,(struct sockaddr *)&destA,sizeof(destA));
			}
		}
		else
		sendto(socket_fd,name,1024,0,(struct sockaddr *)&destA,sizeof(destA));
	}
return 0;
}
