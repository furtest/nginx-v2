#include <stdlib.h>
#include <string.h>

#include "../include/request_parser.h"
#include "../include/http.h"

struct http_request *parse_request(const char *data, size_t n)
{
    struct http_request *req = malloc(sizeof(*req));
    req->method = parse_method(data);
    return req;
}


/*
 * Parses the http request to extract the method.
 *
 * Args:
 * const char *data: the request
 *
 * Returns:
 * enum HTTP_METHOD: the method used by the request or ERROR
 */
enum HTTP_METHOD parse_method(const char *data)
{
    enum HTTP_METHOD method = ERROR;
    switch(data[0]){
    case 'G':
	if(strncmp(data, "GET", 3) == 0){
	    method = GET;
	}
	break;
    case 'H':
	if(strncmp(data, "HEAD", 4) == 0){
	    method = HEAD;
	}
	break;
    case 'P':
	if(strncmp(data, "POST", 4) == 0){
	    method = POST;
	} else if(strncmp(data, "PUT", 3) == 0){
	    method = PUT;
	}
	break;
    case 'D':
	if(strncmp(data, "DELETE", 6) == 0){
	    method = DELETE;
	}
	break;
    case 'L':
	if(strncmp(data, "LINK", 4) == 0){
	    method = LINK;
	}
	break;
    case 'U':
	if(strncmp(data, "UNLINK", 6) == 0){
	    method = UNLINK;
	}
	break;
    default:
	break;
    }
    return method;
}



char * parse_uri(void *raw_uri, size_t n);
int decode_uri(void *uri, size_t n);
