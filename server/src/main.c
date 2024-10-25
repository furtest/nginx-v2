#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/sockets.h"

int main(int argc, char **argv){

    if(argc != 2){
	fputs("You need to provide a port number\n", stderr);
	exit(EXIT_FAILURE);
    }
    
    int sd = init_socket("127.0.0.1", atoi(argv[1]));
    if(sd < 0){
	exit(EXIT_FAILURE);
    }

    struct request *req = wait_for_request(sd);
    
    fwrite(req->data, req->data_len, 1, stdout);

    free(req);
    close(sd);

    return EXIT_SUCCESS;
}
