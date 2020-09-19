#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>


#define SIM_LENGTH 10
#define IP_ADDRESS "127.0.0.1"
#define PORT 1337

int main(int argc, char*argv[])
{
  // init variables
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value;
  // init variables - properties of the site
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;

  printf("Client is alive and establishing socket connection.\n");

  // the address data
  hostname = argv[1];
  getaddrinfo(hostname, NULL, NULL, &res);
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);
  printf(" The IP address is %s ",hostaddr);
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }

  bzero((char *)&cli_name,sizeof(cli_name)); 
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(hostaddr); // change from IP to hostaddr
  cli_name.sin_port = htons(PORT);

  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf(" \n Client has received %d from socket.\n", value);
  }

  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
  { perror ("Error establishing communications");
    close(sock);
    exit(1);
  }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

}