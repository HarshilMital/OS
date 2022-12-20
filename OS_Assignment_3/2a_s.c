#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>




#define SOCKET_PATH "/home/harshil/OS/OS_Assignment_3/socket"
#define BUFFER_SIZE 20


int main(int argc, char *argv[]) {
  // Create the socket
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  

  // Set up the socket address
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

  // Bind the socket to the address
  bind(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));

  // Listen for incoming connections
  listen(sockfd, 20);

  // Accept a connection
  int clientfd = accept(sockfd, NULL, NULL);
  

  // Generate and send 50 random strings of size 5
  
    char buffer[BUFFER_SIZE];
    char string_list[50][BUFFER_SIZE];
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 5; j++) {
        buffer[j] = 'A' + rand() % 26;
      }
      strcpy(string_list[i], buffer);
      // string_list[i][BUFFER_SIZE] = '\0';
      // string_list[i] = buffer;
    }
    // int k = rand() % 45;
    for (int k = 0; k < 50; k += 5){
      for (int i = 0; i < 5; i++){
        char buffer[BUFFER_SIZE];
        sprintf(buffer, "%s,%d",string_list[k + i],k + i);
        write(clientfd, buffer, BUFFER_SIZE);
      }
      
      read(clientfd, buffer, BUFFER_SIZE);
      printf("max index = %d\n", atoi(buffer));
  }
  

  // Close the socket
  close(clientfd);
  close(sockfd);

  return 0;
}

