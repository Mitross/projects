#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
int main(){

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd<0){
        perror("Socket error");
        exit(-1);
    }

    int yes = 1;
    //lose the "address alreay in use" message
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    struct addrinfo hint, *res;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;   
    
    getaddrinfo(NULL, "8080", &hint, &res); 

 

    int bind_result = bind(socketfd, res->ai_addr, res->ai_addrlen);
  //  printf("Bind result is %d\n",bind_result);

    if(bind_result<0){
        perror("bind error");
        exit(-1);
    }


    //listen for incoming connections 
    int listen_result = listen(socketfd, 20);
    
    if(listen_result<0){
        perror("Listen error");
        exit(-1);
    }

    struct sockaddr_storage their_addr;
    socklen_t addrsize; 
    int new_fd = accept(socketfd, (struct sockaddr *)&their_addr, &addrsize);
   
    int max_len = 1000;
    char recieved_request[max_len];
    memset(recieved_request, 0, max_len); //this sets all values to 0

    int num_bytes = recv(new_fd, recieved_request, max_len, 0);

    if (strncmp(recieved_request, "GET", 3) == 0){
        printf("recieved http get request\n");

        //response to http get request
        char *status_line = "HTTP/1.1 200 OK \r\n";
        int sent_bytes = send(new_fd, status_line, strlen(status_line), 0);
        printf("sent_bytes = %d\n",sent_bytes);

        char *headers = "Content-Type: text/html\r\n\r\n";
        sent_bytes = send(new_fd, headers, strlen(headers), 0);
        printf("sent_bytes = %d\n",sent_bytes);

        FILE *index_file = fopen("index.html", "r");
        char c;
        while( (c = getc(index_file)) != EOF){
            sent_bytes = send(new_fd, &c, 1, 0);
        }
    }
    else {
        printf("recieved non get request ignoring...\n");
        close(socketfd);
        close(new_fd);
        exit(-1);
    }



    close(socketfd);
    close(new_fd);
    return 0;
}