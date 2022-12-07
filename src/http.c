#include "http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* generate_response(int status_code, const char* reason_phrase, const char* content_type, const char* filepath){
    char* resp = calloc(MAX_HEADER + MAX_BODY, sizeof(char));

    //HTTP version
    strncat(resp, "HTTP/1.0 ", 10);

    //Status Code
    char status_code_str[4] = {0};
    snprintf(status_code_str, 4, "%d", status_code);
    strncat(resp, status_code_str, 3);
    strncat(resp, " ", 2);

    //Reason phrase
    strncat(resp, reason_phrase, 10);
    strncat(resp, "\r\n", 3);

    if(content_type != NULL){
        strncat(resp, "Content-Type: ", 15);
        strncat(resp, content_type, 20);
        strncat(resp, "\r\n", 3);
    }

    //End of response header
    strncat(resp, "\r\n", 3);

    //Message body
    char* body = load_html(filepath);
    strncat(resp, body, MAX_BODY);
    free(body);

    return resp;
}

char* load_html(const char* filepath){
    char* body = calloc(MAX_BODY, sizeof(char));
    long length;
    FILE* f = fopen(filepath, "rb");

    if(f == NULL){
        fprintf(stderr, "Error when reading html file!\n");
    }

    if(f){
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        fread(body, 1, length, f);
        fclose(f);
    }


    return body;
}