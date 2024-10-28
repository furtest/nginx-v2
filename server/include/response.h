#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>

#include "http.h"

struct http_response *create_response(struct http_request *request);
char *read_file(char *path);
FILE *open_file(char *path);
char *format_response(struct http_response *response);

#endif
