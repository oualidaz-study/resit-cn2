#include "asp.h"

/*
  *Creates a new socket
*/
int create_socket(){
  
  int sockfd;

  //create a new socket.
  if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){ 
    perror("Error");
    exit(EXIT_FAILURE);
  }

  return sockfd;
}

/*
  *Binds an address to a socket
*/
struct sockaddr_in6 bind_address_to_socket(int sockfd, int port){

  struct sockaddr_in6 addr;

  memset(&addr, '\0', sizeof(addr)); // zero structure out
  addr.sin6_family = AF_INET6; // match the socket() call
  inet_pton(AF_INET6, "::1", &addr.sin6_addr); // bind to any local address
  addr.sin6_port = htons(port); // specify port to listen on

  if((bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)){
    perror("Error");
    exit(EXIT_FAILURE);
  }
  
  //return struct
  return addr;

}

/*
 * get the size of the address
*/
socklen_t get_address_length(struct sockaddr_in6 addr){
  return sizeof(addr);
}

/*
 * Receive message from remote address
*/
struct sockaddr_in6 receive_acknowledgemnt(int sockfd){
  
  //Initialize buffer
  struct sockaddr_in6 sender_addr;
  socklen_t sender_struct_length = sizeof(sender_addr);

  //receive message from remote address
  char buffer[8000];
  if (recvfrom(sockfd, buffer, 8000, 0, (struct sockaddr*)&sender_addr, &sender_struct_length) < 0){
    printf("Couldn't receive\n");
    exit(EXIT_FAILURE);
  }
  
  //print the IP and Port of the sender
  char str1[INET_ADDRSTRLEN];
  printf("<%s:%i>: '%s' \n", inet_ntop(AF_INET, &sender_addr.sin6_addr, str1, INET_ADDRSTRLEN), ntohs(sender_addr.sin6_port), buffer);
  
  //return the remote address
  return sender_addr;
}

/*
 * Send message to remote address
*/
void send_message(int sockfd, struct sockaddr_in6 receiver_addr, char* msg){
  int receiver_struct_length = sizeof(receiver_addr);
  if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&receiver_addr, receiver_struct_length) < 0){
    perror("Error: ");
    exit(EXIT_FAILURE);
  }
}

/*
 * Connect to server with port  
*/
struct sockaddr_in6 connect_to_server_with_port(int sockfd, int port){
  //connect
  struct sockaddr_in6 remote_addr;
  inet_pton(AF_INET6, "::1", &remote_addr.sin6_addr);
  remote_addr.sin6_port = htons(port);
  remote_addr.sin6_family = AF_INET6;
  remote_addr.sin6_flowinfo = 26;
  remote_addr.sin6_scope_id = 2;

  if(connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0){
    perror("Error: ");
    exit(0);
  }

  // Get input from the user:
  char message[2000] = "ack\0";
  // Send the message to server:
  send_message(sockfd, remote_addr, message);

  return remote_addr;
}