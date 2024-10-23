#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sockets.h"

int main(int argc, char **argv){

    if(argc != 2){
	fputs("You need to provide a port number\n", stderr);
	exit(EXIT_FAILURE);
    }
    
    int sd = init_socket("127.0.0.1", atoi(argv[1]));
    close(sd);

    return EXIT_SUCCESS;
}
