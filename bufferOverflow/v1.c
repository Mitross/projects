#include <stdio.h>
#include <string.h>

typedef char* string;

void foo(char *input){
    char buffer[4];
    strcpy(buffer,input);//bigger than four gets you stack smashing detected
                                            //-> core dumped

    printf("i entered %s\n", buffer);
}

void safe_foo(string input){
    char* buffer[64];
    snprintf(buffer, sizeof(buffer), "%s", input);

    printf("i entered %s\n", buffer);
}

int main(int argc, char* argv[]){
    if(argc>1){
        safe_foo(argv[1]);
    }else{
        printf("provide argument\n");
    }
    return 0;

}