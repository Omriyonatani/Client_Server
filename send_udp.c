#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  // initialize variables 
  int socket_fd;
  unsigned int fsize;
  struct sockaddr_in  dest,from;
  struct hostent *hostptr;
  char nameR[100]="Omri";

  // build a socket
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */
  // recieve the ip
  hostptr = gethostbyname(argv[1]);
  dest.sin_family = (short) AF_INET;
  // copy the ip from sin to h_addr
  memcpy(hostptr->h_addr_list, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((unsigned short)0x3333);
  // send the information
  sendto(socket_fd,nameR,100,0,(struct sockaddr *)&dest, sizeof(dest));
  // make all the bytes to 0
  fsize=sizeof(from);	
	bzero(nameR,100);
  // get the data and information
	recvfrom(socket_fd,nameR,100,0,(struct sockaddr *)&from,&fsize);
  // Prints the message
  printf("Got data: %s\n",nameR); 
  //cleans the memory
  fflush(stdout);


  return 0;
}

