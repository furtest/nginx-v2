#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdlib.h>

#include "http.h"

struct http_request *parse_request(const uint8_t *request, size_t len);
enum HTTP_METHOD parse_method(const char *request);
char *extract_uri(const char *request);
ssize_t parse_uri(const char *uri, uint8_t *parsed_uri);

#endif
