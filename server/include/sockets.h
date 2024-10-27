#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdlib.h>
#include <netinet/in.h>

#define BLOCK_SIZE 1024
#define MAX_REQ_SIZE 65536

// Struct to hold what is received and what needs to be sent
struct tcp_info {
    int client_sd;
    struct sockaddr_in client_addr;
    size_t data_len;
    unsigned char *data;
};

int init_socket(char *ip, int port);
struct tcp_info *wait_for_request(int server_sd);
ssize_t get_request(int sd, void **data);
ssize_t send_response(struct tcp_info *response);

#endif
