#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdlib.h>

#include "http.h"

struct http_request *parse_request(const char *data, size_t n);
char * parse_uri(void *raw_uri, size_t n);
int decode_uri(void *uri, size_t n);

#endif
