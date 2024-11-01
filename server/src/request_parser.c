#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "../include/request_parser.h"
#include "../include/http.h"

struct http_request *parse_request(const uint8_t *request, size_t len)
{
    struct http_request *req = malloc(sizeof(*req));
    if(req == NULL)
	return NULL;
    if(len < 16)
	goto bad_request;

    enum HTTP_METHOD method = parse_method((char *) request);
    if(method == BAD_REQUEST)
	goto bad_request;


    return req;

bad_request:
    req->method = BAD_REQUEST;
    req->len = 0;
    req->uri = NULL;
    req->headers = NULL;
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
enum HTTP_METHOD parse_method(const char *request)
{
    enum HTTP_METHOD method = BAD_REQUEST;
    size_t method_len = 0;
    switch(request[0]){
    case 'G':
	if(strncmp(request, "GET", 3) == 0){
	    method_len = 3;
	    method = GET;
	}
	break;
    case 'H':
	if(strncmp(request, "HEAD", 4) == 0){
	    method_len = 4;
	}
	break;
    case 'P':
	if(strncmp(request, "POST", 4) == 0){
	    method_len = 4;
	    method = POST;
	} else if(strncmp(request, "PUT", 3) == 0){
	    method_len = 3;
	    method = PUT;
	}
	break;
    case 'D':
	if(strncmp(request, "DELETE", 6) == 0){
	    method_len = 6;
	    method = DELETE;
	}
	break;
    case 'L':
	if(strncmp(request, "LINK", 4) == 0){
	    method_len = 4;
	    method = LINK;
	}
	break;
    case 'U':
	if(strncmp(request, "UNLINK", 6) == 0){
	    method_len = 6;
	    method = UNLINK;
	}
	break;
    default:
	break;
    }

    if(request[method_len + 1] != ' '){
	method = BAD_REQUEST;
    }
    return method;
}

/*
 * Extracts the URI from the request and returns it.
 */
char *extract_uri(const char *request)
{
    const char *cursor = request;
    while(*cursor != ' ' && *(cursor++) != '\0') {}
    if(*cursor == '\0')
	return NULL;
    const char *start = ++cursor;

    while(*cursor != ' ' && *(cursor++) != '\0') {}
    if(*cursor == '\0')
	return NULL;

    size_t uri_len = cursor - start;
    char *uri = calloc(uri_len + 1, 1);
    strncpy(uri, cursor, uri_len);
    return NULL;
}

int decode_uri(void *uri, size_t n);
