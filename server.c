// Written to get a better grasp of sockets, and socket programming in C.
// Written by LH May '26

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  
  // Will hold both the server's, and an incoming client's file descriptors
  int socket_fd, csocket_fd;

  const int socket_port = 8080;

  struct sockaddr_in socket_info; 

  // First, a socket is created, and the file descriptor is returned
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);

  if(socket_fd == -1) {

    perror("Failed to create the socket, please try again.");

    return 1;

  }

  // Next, bind an address and port to the newly created socket
  

  return 0;

}

