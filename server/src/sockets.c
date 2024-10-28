#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <unistd.h>

#include "../include/sockets.h"

/*
* Initializing socket 
* Args :
* - char *ip : the ip to bind the socket to 
* - int port : the listening port
* Returns :
* int : the socket descriptor
*/
int init_socket(char *ip, int port){
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0){
	perror("Failed to open socket");
	return -1;
    }
    
// For dev only, IN_DEV is set (or not) at compile time
#ifdef IN_DEV
    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0){
	perror("Failed to set dev option");
    }
#endif
    
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if( inet_pton(AF_INET, ip, &(addr.sin_addr.s_addr)) < 1){
	fputs("Failed to init socket : invalid ip address", stderr);
	close(sd);
	return -2;
    }
    
    if(bind(sd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) != 0){
	perror("Failed to bind socket");
	return -3;
    }
    
    // 2 is for the backlog queue not sure what it does nor what is a good value for it
    listen(sd, 2);

    return sd;   
}

/*
* Wait for a request, accept it and read the request
* Returns : the received request including the address of the client and the request itself
*/
struct tcp_info *wait_for_request(int server_sd){
    struct tcp_info *req = malloc(sizeof(struct tcp_info));
    
    unsigned int client_size = sizeof(struct sockaddr_in);
    int client_sd = accept(server_sd, (struct sockaddr *) &(req->client_addr), &client_size);
    
    if(client_sd == -1){
	free(req);
	perror("Failed to accept client");
	return NULL;
    }
    req->client_sd = client_sd;
    req->data = NULL;

    if((req->data_len = get_tcp_request(client_sd, (void *) &(req->data))) < 0){
	free(req);
	return NULL;
    }

    
    return req;
}

/*
* Read the data (request) on the socket 
* Args :
* sd : The client's socket descriptor
* data : The address of a buffer to fill with data, should be NULL
*/
ssize_t get_tcp_request(int sd, uint8_t **data){
    if(*data != NULL) return -1;

    size_t size = 0;
    size_t len_received = 0;

    do{
	*data = realloc(*data, BLOCK_SIZE);
	if(*data == NULL){
	    return -2;
	}
	len_received = recv(sd, *data, BLOCK_SIZE, 0);
	size += len_received;
    }while(size < MAX_REQ_SIZE && len_received == 512);
    
    return size; 
}


ssize_t send_tcp_response(struct tcp_info *response){
    ssize_t return_value = send(response->client_sd, response->data, response->data_len, 0);

    if( return_value < 0) perror("Failed to send data");

    return return_value;
}
