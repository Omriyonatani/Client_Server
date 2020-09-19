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

void printsin(struct sockaddr_in *sin, char *pname, char *msg) {
  printf("UDP-SERVER:\n");
  printf("%s: ", msg);
  printf("ip= %s , port= %d \n", inet_ntoa(sin->sin_addr), sin->sin_port);
}

 
int main(int argc, char *argv[])
{
  // init variables
  char nameS[50] = "Yonatani";
  int socket_fd;
  unsigned int fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; unsigned long  body; char tail;} msg;
  // build a socket, values=0
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
  // address for the socket
  s_in.sin_family = (short)AF_INET; 
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ // host to network long
  s_in.sin_port = htons((unsigned short)0x3333); // host to network short 

  printsin(&s_in, "UDP-SERVER ", "Local socket is: "); 
  fflush(stdout);
  // connect the address and port with socket
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  char name[100];
  // infinite loop 
  while(1) {
    fsize = sizeof(from);
    // receive and print msg
    recvfrom(socket_fd,name,100,0,(struct sockaddr *)&from,&fsize);
    printsin(&from, "UDP-SERVER ", "Packet from: ");
    printf("Got data: %s\n",name);
    // clean the memory 
    fflush(stdout);
    // Send the message to the socket 
    sendto(socket_fd,nameS,50,0,(struct sockaddr *)&from, sizeof(from));
  }
  // print the massage
  printf("%lu",msg.body);
      
  return 0;
}
