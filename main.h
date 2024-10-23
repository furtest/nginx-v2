#ifndef MAIN_H
#define MAIN_H

// Struct for a received request
struct request {
    unsigned char *data;
    // The client socket descriptor
    int client_sd;
};

// Struct for passing the response
struct response {
    unsigned char *data;
    // The client socket descriptor
    int client_sd;
};

#endif
