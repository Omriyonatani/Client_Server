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
#include  <stdlib.h>

#define PORT_S 2222
#define PORT_R 1111

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
    puts(pname);
    printf("%s ip= %s, port= %d\n", msg, inet_ntoa(sin->sin_addr), sin->sin_port);
}

  int main(int argc, char *argv[])
{
    // init variables
	  char name[1024];
	  int socket_fd;
	  unsigned int fsize;
  	struct sockaddr_in  serv_add,dest,destR;

    // build a socket
  	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
    // make all bytes ZERO
	  bzero((char *) &serv_add,sizeof(serv_add));
	  bzero((char *) &dest,sizeof(dest));
	  bzero((char *) &destR,sizeof(destR));

	  serv_add.sin_family=(short)AF_INET;
	  serv_add.sin_addr.s_addr=htonl(INADDR_ANY); // host to network long
	  serv_add.sin_port=PORT_S;

	  dest.sin_family=(short)AF_INET;
	  dest.sin_addr.s_addr=(INADDR_ANY);
	  dest.sin_port=PORT_R;

	  destR.sin_family=(short)AF_INET;
    	destR.sin_addr.s_addr=htonl(INADDR_ANY); // host to network long
    	destR.sin_port=PORT_R;

	  bind(socket_fd,(struct sockaddr*) & serv_add,sizeof(serv_add));

	  printsin( &serv_add, "UDP-SERVER ", "Local socket is:");
	  fflush(stdout);
	  char name2[1024]="Got your message";

    	//infinite loop
	  while(1)
	    {
	
	    fsize=sizeof(dest);
	    bzero(name,1024);
	    recvfrom(socket_fd,name,1024,0,(struct sockaddr *)&dest,&fsize); 
	    puts(name);
	    sendto(socket_fd,name2,1024,0,(struct sockaddr *)&destR,sizeof(destR));
	    bzero(name,1024);
	    fgets(name,1024,stdin);

	    if(strcmp(name,"exit\n")==0)
		    {
			  strcpy(name,"Server closed ");
			  sendto(socket_fd,name,1024,0,(struct sockaddr *)&dest,sizeof(dest));
			  fflush(stdout);
		    }
	    }
	    return 0;
}