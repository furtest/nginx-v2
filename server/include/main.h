#ifndef MAIN_H
#define MAIN_H

#include <netinet/in.h>

// Struct for a received request
struct request {
    int client_sd;
    struct sockaddr_in client_addr;
    size_t data_len;
    unsigned char *data;
};

// Struct for passing the response
struct response {
    int client_sd;
    unsigned char *data;
};

#endif
