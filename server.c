// Written to get a better grasp of sockets, and socket programming in C.
// Written by LH May '26

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  
  // Will hold both the server's, and an incoming client's file descriptors
  int socket_fd, csocket_fd;

  const unsigned int socket_port = 8080;

  struct sockaddr_in socket_info, csocket_info;
  memset(&socket_info, 0, sizeof(socket_info)); // Ensures padding is set to 0
  memset(&csocket_info, 0, sizeof(csocket_info)); // Same here

  socklen_t csocket_info_len = sizeof(csocket_info); // For later use in the accept loop

  // First, a socket is created, and the file descriptor is returned
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);

  if(socket_fd == -1) {

    perror("Failed to create the socket, please try again.");

    return 1;

  }

  // Next, bind an address and port to the newly created socket
  socket_info.sin_family = AF_INET; // IPv4
  socket_info.sin_port = htons(socket_port); // Port: 8080
  socket_info.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Address: 127.0.0.1 (localhost)
  
  if(bind(socket_fd, (struct sockaddr *)&socket_info, sizeof(socket_info)) == -1) {

    perror("Failed to bind the address and port to the socket!");

    return 1;

  }

  // Have the socket start listening on the bound address and port 
  if(listen(socket_fd, 1) == -1) {

    perror("Failed to start listening!");

    return 1;

  }

  printf("Now listening on port %d...", socket_port); 

  // Loop to handle incoming connections
  while(1) {

    csocket_fd = accept(socket_fd, (struct sockaddr *)&csocket_info, &csocket_info_len);

    if(csocket_fd == -1) {

      perror("Failed to accept a new connection!");

      return 1;

    } 

    

  }

  return 0;

}

