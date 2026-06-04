#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(){

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd<0){
        perror("Socket error");
        exit(-1);
    }

    struct sockaddr hint, *res;
    hint.ai_family 
    
    getaddrinfo(NULL, "8080", &hint, &res); 
    int bind_result = bind(socketfd, &addr,sizeof(struct sockaddr));
    printf("Bind result is %d\n",bind_result);

    while(1){
        ///some ind of request be recieved
        printf("Waiting for request...\n");
        sleep(1);
    }


    return 0;
}