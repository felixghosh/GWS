#ifndef HTTP_H
#define HHTP_H

#define MAX_HEADER 4096
#define MAX_BODY 16384


char* generate_response(int status_code, const char* reason_phrase, const char* content_type, const char* filepath);
char* load_html(const char* filepath);

#endif