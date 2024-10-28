#ifndef HTTP_H
#define HTTP_H

#include <stdlib.h>
#include <stdio.h>

enum HTTP_METHOD {GET, HEAD, POST};

struct http_request{
    enum HTTP_METHOD method;
    char * uri;
    // Won't use headers nor body at first, this is why headers is void*
    void *headers;
    size_t len;
    char *body;
};

struct http_response{
    enum HTTP_METHOD method;
    void *headers;
    size_t len;
    char *body;
};

#endif
