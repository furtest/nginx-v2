#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <unistd.h>

#include "sockets.h"
#include "main.h"

// Initializing socket 
// Args :
// - char *ip : the ip to bind the socket to 
// - int port : the listening port
// Returns :
// int : the socket descriptor
int init_socket(char *ip, int port){
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0){
	perror("Failed to open socket");
	return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if( inet_pton(AF_INET, ip, &(addr.sin_addr.s_addr)) < 1){
	fputs("Failed to init socket : invalid ip address", stderr);
	close(sd);
	return 2;
    }

    if(bind(sd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) != 0){
	perror("Failed to bind socket");
	return 3;
    }
    
    // 2 is for the backlog queue not sure what it does nor what is a good value for it
    listen(sd, 2);

    return sd;   
}

struct request *wait_for_request(int server_socketd);
ssize_t send_response(struct response *response);
