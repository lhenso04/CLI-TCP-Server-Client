// A very simple TCP client implementation written in the C programming language.
// Written to get more familiar with the process of connecting to a server via sockets.
// Written by LH May '26

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {

  int client_fd;

  uint16_t port = 8080;

  char buf[512];

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));

  // Create the client's file socket
  client_fd = socket(PF_INET, SOCK_STREAM, 0);

  if(client_fd == -1) {

    perror("Failed to create the client socket!");

    return 1;

  }

  // Fill in the server's information
  server_addr.sin_family = AF_INET; // IPv4
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1
  server_addr.sin_port = htons(port); // 8080

  puts("Establishing a connection...");

  // Connect to the server 
  if(connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {

    perror("Connection failed!");

    return 1;

  }

  puts("Connection established! Receiving the message from the server...");

  // Receive the message from the server
  int bytes_received = recv(client_fd, &buf, sizeof(buf), 0);

  if(bytes_received == -1) {

    perror("Failed to receive the message!");

    return 1;

  }

  printf("Received the message: %s", buf);

  // Clean up, close the file descriptor for the socket
  close(client_fd);

  return 0;

}

