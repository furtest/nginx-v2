#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdlib.h>

#include "main.h"

#define BLOCK_SIZE 1024
#define MAX_REQ_SIZE 65536

int init_socket(char *ip, int port);
struct request *wait_for_request(int server_sd);
ssize_t get_request(int sd, void **data);
ssize_t send_response(struct response *response);

#endif
