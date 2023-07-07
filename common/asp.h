#ifndef CN2_COMMON_ASP_H_
#define CN2_COMMON_ASP_H_

/* Skeleton code for Computer Networks 2022 @ LIACS */

/* TODO: Add function declarations for the public functions of your ASP implementation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <math.h>


/*
 * An asp socket descriptor for information about the sockets current state.
 * This is just an example, you can make anything you want out of it
 */
typedef struct{
  int sockfd;

  struct sockaddr_in6 local_addr;
  socklen_t local_addrlen;

  struct sockaddr_in6 remote_addr;
  socklen_t remote_addrlen;

  struct asp_socket_info *next;

  int current_quality_level;
  uint32_t sequence_count;

  size_t packets_received;
  size_t packets_missing;

  struct timeval last_packet_received;
  struct timeval last_problem;

  unsigned int is_connected : 1;
  unsigned int has_accepted : 1;
} asp_socket_info;


int create_socket();
struct sockaddr_in6 bind_address_to_socket(int sockfd, int port);
socklen_t get_address_length(struct sockaddr_in6 addr);

struct sockaddr_in6 receive_acknowledgemnt(int sockfd);
void send_message(int sockfd, struct sockaddr_in6 receiver_addr, char* msg);

struct sockaddr_in6 connect_to_server_with_port(int sockfd, int port);

#endif  // CN2_COMMON_ASP_H_