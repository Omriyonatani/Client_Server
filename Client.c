#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define PORT_C 3333
#define PORT_R 1111

int main(int argc, char *argv[])
{
  // init variables
	char name[1024];
	int socket_fd;
	unsigned int length;
  struct sockaddr_in serv_ad,dest;
  // build a socket and make all bytes ZERO
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &serv_ad,sizeof(serv_ad));
  bzero((char *) &dest,sizeof(dest));
  	
	serv_ad.sin_family=(short)AF_INET;
	serv_ad.sin_addr.s_addr=(INADDR_ANY);
	serv_ad.sin_port=PORT_C;


	dest.sin_family=(short)AF_INET;
	dest.sin_addr.s_addr=(INADDR_ANY);
	dest.sin_port=PORT_R;

	bind(socket_fd,(struct sockaddr*) & serv_ad,sizeof(serv_ad));
	fflush(stdout);

	// infinite loop
	while(1)
		{
		bzero(name,1024);
		fgets(name,1024,stdin);

		if(strcmp(name,"exit\n")==0)

			{
				strcpy(name,"Connetion end \n");
				sendto(socket_fd,&name,1024,0,(struct sockaddr *)&dest,sizeof(dest));
				
				close(socket_fd);
				break;
			}

		sendto(socket_fd,name,1024,0,(struct sockaddr *)&dest,sizeof(dest));
		bzero(name,1024);
		length=sizeof(dest);
		recvfrom(socket_fd,name,1024,0,(struct sockaddr *)&dest,&length);
		printf("%s\n",name);
		fflush(stdout);
		}
		
		return(0);
}
