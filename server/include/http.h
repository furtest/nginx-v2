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

struct http_request *parse_request(const char *data, size_t n);
char * parse_uri(void *raw_uri, size_t n);
int decode_uri(void *uri, size_t n);

struct http_response *create_response(struct http_request *request);
char *read_file(char *path);
FILE *open_file(char *path);
char *format_response(struct http_response *response);

#endif
