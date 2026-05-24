// Written to get a better grasp of sockets, and socket programming in C.
// Written by LH May '26

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  
  // Will hold both the server's, and an incoming client's file descriptors
  int socket_fd, csocket_fd;

  const int socket_port = 8080;

  struct sockaddr_in socket_info;
  memset(&socket_info, 0, sizeof(socket_info)); // For compatibility

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
  

  return 0;

}

