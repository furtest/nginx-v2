#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "request_parser.h"
#include "http.h"

struct http_request *parse_request(const uint8_t *request, size_t len)
{
    struct http_request *req = malloc(sizeof(*req));
    if(req == NULL)
	return NULL;
    if(len < 16){
	req->method = BAD_REQUEST;
	goto parse_request_fail;
    }

    // TODO check the size of the request and the uri (set a max size for both)

    enum HTTP_METHOD method = parse_method((char *) request);
    if(method == BAD_REQUEST){
	req->method = BAD_REQUEST;
	goto parse_request_fail;
    }


    req->uri = extract_uri((char *) request);
    if(req->uri == NULL){
	switch (errno) {
	case EINVAL:
	    req->method = BAD_REQUEST;
	    break;

	case ENOMEM:
	default:
	    req->method = INTERNAL_SERVER_ERROR;
	    break;
	}
	goto parse_request_fail;
    }

    return req;

parse_request_fail:
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
 * This function assumes that the request has a valid HTTP method.
 * Returns NULL in case of error sets errno to 
 * - EINVAl : bad request
 * - ENOMEM : failed memory allocation
 */
char *extract_uri(const char *request)
{
    const char *start = strchr(request, ' ');
    if(start == NULL){
	errno = EINVAL;
	return NULL;
    }

    start++;

    const char *end = strchr(start, ' ');
    if(end == NULL){
	errno = EINVAL;
	return NULL;
    }

    size_t uri_len = end - start;
    char *uri = calloc(uri_len + 1, 1);
    if(uri == NULL){
	errno = ENOMEM;
	return NULL;
    }

    memcpy(uri, start, uri_len);
    uri[uri_len] = '\0';
    return uri;
}

/*
 * Parse an extracted uri, handles the % HEX HEX parts.
 * parsed_uri should be at least the same size as uri-1
 * Returns the size of the parsed uri.
 * On error returns -1 and sets errno to :
 * - EINVAL : INTERNAL_SERVER_ERROR
 * - EBADMSG : BAD_REQUEST
 */
ssize_t parse_uri(const char *uri, uint8_t *parsed_uri)
{
    if(uri == NULL || parsed_uri == NULL){
	errno = EINVAL;
	return -1;
    }

    size_t uri_len = strlen(uri);
    size_t parsed_len = uri_len;
    const char *cursor = uri;
    const char *next = NULL;
    while ((next = strchr(cursor, '%')) != NULL) {
	parsed_len -= 2;
	if(next >= uri + uri_len + 2){
	    errno = EBADMSG;
	    return -1;
	}

	for(size_t i = 0; cursor != next; ++cursor, ++i){
	    parsed_uri[cursor - uri + i] = *cursor;
	}
	// Increase cursor so we do not find the same % on the next loop
	++cursor;

	char val[3];
	val[0] = cursor[1];
	val[1] = cursor[2];
	val[2] = '\0';
	char *endptr = NULL;
	uint8_t value = (uint8_t) strtol(val, &endptr, 16);

	if(*endptr != '\0'){
	    errno = EBADMSG;
	    return -1;
	}
	parsed_uri[next - uri] = value;
    }

    return parsed_len;
}
