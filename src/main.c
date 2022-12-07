#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
//#include <sys/types.h>
//#include <signal.h>
//#include <unistd.h>
#include <arpa/inet.h>
//#include <stdarg.h>
//#include <errno.h>
//#include <fcntl.h>
//#include <sys/time.h>
//#include <sys/ioctl.h>
//#include <netdb.h>
#include "GCL.h"

#define MAX_LINE 4096
#define MAX_CON 10
#define SERVER_PORT 8888

int main(int argc, char** argv){

    bool running = true;

    int listen_fd, connection_fd;
    struct sockaddr_in server_address;
    uint8_t buff[MAX_LINE+1];
    uint8_t receive[MAX_LINE+1];

    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "Socket error!\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    if((bind(listen_fd, (struct sockaddr*)&server_address, sizeof(server_address))) < 0){
        fprintf(stderr, "Bind error!\n");
        exit(1);
    }

    if((listen(listen_fd, MAX_CON)) < 0){
        fprintf(stderr, "Listen error!\n");
        exit(1);
    }

    while(running){
        struct sockaddr_in addr;
        socklen_t addr_len;

        //Wait for an incoming connection
        printf("Wating for a connection on port %d\n", SERVER_PORT);
        connection_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
    }

    return 0;
}