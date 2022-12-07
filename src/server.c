#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "GCL.h"
#include "http.h"

#define MAX_LINE 4096
#define MAX_CON 10
#define SERVER_PORT 80

int main(int argc, char** argv){

    bool running = true;

    //Set up route map
    tree_map_t* route_map = new_tree_map((void*)"/", (void*)"html/index.html", &compstring);
    insert_tree_map(route_map, (void*)"/style.css", (void*)"html/style.css");
    printf("Routes:\n");
    print_tree_map(route_map, "{%s: %s}");
    printf("\n");

    //Set up content type map
    tree_map_t* content_type_map = new_tree_map((void*)"/", (void*)"text/html", &compstring);
    insert_tree_map(content_type_map, (void*)"/style.css", (void*)"textcss");
    printf("Content types:\n");
    print_tree_map(content_type_map, "{%s: %s}");
    printf("\n");

    
    //Set up file descriptors, socket adress, and buffers
    int listen_fd, connection_fd, n;
    struct sockaddr_in server_address;
    uint8_t send_buff[MAX_LINE+1];
    uint8_t receive_buff[MAX_LINE+1];

    //Create socket to listen for incomming connections
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "Socket error!\n");
        exit(1);
    }

    //Set address/port to be reusable
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0){
        printf("setsockopt(SO_REUSEADDR) failed\n");
        exit(1);
    }
        
    //Create server address and bind our port to it
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    //Bind listening socket
    if((bind(listen_fd, (struct sockaddr*)&server_address, sizeof server_address)) < 0){
        if(SERVER_PORT == 80)
            fprintf(stderr, "Error: Program needs to be run with elevated privileges to listen on port 80!\n");
        else
            fprintf(stderr, "Bind error!\n");
        exit(1);
    }

    //Start listening for incomming connections
    if((listen(listen_fd, MAX_CON)) < 0){
        fprintf(stderr, "Listen error!\n");
        exit(1);
    }

    while(running){
        struct sockaddr_in addr;
        socklen_t addr_len;

        //Accept new connection
        printf("Wating for a connection on port %d\n", SERVER_PORT);
        connection_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
        
        fprintf(stdout, "\nReceived request:\n");

        //Read data from connection
        memset(receive_buff, 0, MAX_LINE);
        while((n = read(connection_fd, receive_buff, MAX_LINE-1)) > 0){
            fprintf(stdout, "%s", receive_buff);

            //Bad way of finding end of data
            if(receive_buff[n-1] == '\n')
                break;

            memset(receive_buff, 0, MAX_LINE);
        }

        if(n < 0){
            fprintf(stderr, "Read error!\n");
            exit(1);
        }

        //Extract method and url
        char method[8] = {0};
        char url[256] = {0};
        int i = 0;
        int j = 0;
        char c;
        while((c = receive_buff[i++]) != (char)' ')
            method[j++] = c;
        j = 0;
        while((c = receive_buff[i++]) != (char)' ')
            url[j++] = c;

        
        //Create response based on url
        char* resp;
        if(contains_tree_map(route_map, url)){
            resp = generate_response(200, "OK", get_tree_map(content_type_map, url), get_tree_map(route_map, url));
        } else {
            //Default to index page for now
            resp = generate_response(200, "OK", "text/html", "html/index.html");
        }
            
        printf("Sending response:\n%s\n\n", resp);
        snprintf((char*)send_buff, sizeof send_buff, resp);
        free(resp);

        //Send response
        write(connection_fd, (char*)send_buff, strlen((char*)send_buff));

        //Close connection
        close(connection_fd);
    }

    return 0;
}