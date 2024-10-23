#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdlib.h>

#include "main.h"

int init_socket(char *ip, int port);
struct request *wait_for_request(int server_socketd);
ssize_t send_response(struct response *response);

#endif
