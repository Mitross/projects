/*
To bypass modern safety futures we are going to use ROP(Return Oriented Programing)
in assembly code of a program there are ROP gadgets like "pop rdi; ret"
(they have to end in ret to be gadget)
I OVER FLOW WITH SEQUENCE OF GADGET ADDRESSSES !!!!!ROP CHAI!!!!!

to go round ASLR  we need informtion leak vulnerability so we can now addresses
*/

#include <stdio.h>
#include <string.h>

void vulnerable_function(){
    char buffer[64];
    //until new line 0 BIUNDS CHECKING
    gets(buffer);
}

int main(){
    printf("ROP lab.\n");
    vulnerable_function();
    printf("Exiting notmally.\n");
    return 0;
}
//gcc -fno-stack-protector -z execstack -no-pie -o v3 v3.c
/*

-z execstack kkeps stuck non executable
-no-pie fixes adresses so no moving around(ASLR)


ROPgadget --binary ./v3 --only "pop|ret"
we look for pop rbp ; ret


*/