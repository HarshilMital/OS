#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/home/harshil/OS/OS_Assignment_3/socket"
#define BUFFER_SIZE 20

int main(int argc, char *argv[]) {
  // Create the socket
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  

  // Set up the socket address
  struct sockaddr_un saddr;
  memset(&saddr, 0, sizeof(struct sockaddr_un));
  saddr.sun_family = AF_UNIX;
  strncpy(saddr.sun_path, SOCKET_PATH, sizeof(saddr.sun_path) - 1);

  // Connect to the server
  connect(sockfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_un));

  // Read and print the strings sent by the server
  for(int k = 0; k < 10; k++){
    char buffer[BUFFER_SIZE];
  
    int max_index = -1;
    for (int i = 0; i < 5; i++) {
          read(sockfd, buffer, BUFFER_SIZE);
          char * token = strtok(buffer, ",");
          printf("%s\n", token);
          token = strtok(NULL, ",");
          int index = atoi(token);
          printf("%d\n", index);
          if (index > max_index){
            max_index = index;
          }
    }
    
    sprintf(buffer, "%d", max_index);
    write(sockfd, buffer, BUFFER_SIZE);
  }
  

  

  // Close the socket
  close(sockfd);

  return 0;
}

