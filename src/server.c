// A very simple TCP server implementation written in the C programming language.
// Written to get a better grasp of sockets, and socket programming in C.
// Written by LH May '26.

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Variable used to handle SIGINT gracefully
volatile sig_atomic_t ctrl_c_interrupt = 0;

void handle_sigint(int sig) {

  (void)sig; // To avoid an unused variable warning

  ctrl_c_interrupt = 1;

}

int main(void) {
  
  // Will hold both the server's, and an incoming client's file descriptors
  int socket_fd, csocket_fd;

  const uint16_t socket_port = 8080;

  struct sockaddr_in socket_info;
  socklen_t socket_info_len = sizeof(socket_info);

  memset(&socket_info, 0, socket_info_len); // Ensures padding is set to 0

  // Defines the message to be sent and its length
  const char* msg = "Hello from the server!";
  const size_t msg_len = strlen(msg);

  // Signal handler for SIGINT
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = handle_sigint;
  sigaction(SIGINT, &act, NULL);

  // First, a socket is created, and the file descriptor is returned
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);

  if(socket_fd == -1) {

    perror("Failed to create the socket, please try again.");

    return 1;

  }

  // Allows for reuse of local addresses, prevents the "Address already in use" error if the server is restarted very quickly 
  int opt = 1;
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // Next, bind an address and port to the newly created socket
  socket_info.sin_family = AF_INET; // IPv4
  socket_info.sin_port = htons(socket_port); // Port: 8080
  socket_info.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Address: 127.0.0.1 (localhost)
  
  if(bind(socket_fd, (struct sockaddr *)&socket_info, socket_info_len) == -1) {

    perror("Failed to bind the address and port to the socket!");
    
    close(socket_fd);

    return 1;

  }

  // Have the socket start listening on the bound address and port 
  if(listen(socket_fd, 1) == -1) {

    perror("Failed to start listening!");

    close(socket_fd);

    return 1;

  }

  printf("Now listening on port %u... (Press Ctrl + C to quit)\n", socket_port); 

  // Loop to handle incoming connections
  while(!ctrl_c_interrupt) {
    
    // Accept an incoming connection
    csocket_fd = accept(socket_fd, (struct sockaddr *)&socket_info, &socket_info_len);

    if(csocket_fd == -1) {
      
      if (ctrl_c_interrupt) break;

      perror("Failed to accept a new connection!");

      continue;

    } 

    puts("Accepting a new connection...");

    puts("Connection established! Sending the message...");

    // Send the message to the client
    int bytes_sent = send(csocket_fd, msg, msg_len + 1, 0); // msg_len + 1 to include \0 
    
    if(bytes_sent == -1) {

      perror("Failed to send over the connection!");

      close(csocket_fd);

      continue;

    }

    puts("Message sent! Closing the connection...");

    // Close the connection
    close(csocket_fd);

  }

  // Closes the server socket cleanly after Ctrl + C is pressed
  if(socket_fd != -1) close(socket_fd);

  return 0;

}

