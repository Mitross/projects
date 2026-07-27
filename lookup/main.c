#include <stdio.h>

const char *message[] =  {
    "not a party you are alone",
    "one is the loneliest number",
    "not onely but not a party",
    "we getting there",
    "we getting there",
    "ahh yeah...",
    "ahh yeah...",
    "ahh yeah...",
    "whoa violated fire code"
}; 

const int NUM_MESSAGES = (sizeof(message) / sizeof(char *));

void print_party_size_info(size_t people){
    if ( people > NUM_MESSAGES - 1 ){
        printf("%s\n",message[NUM_MESSAGES - 1]);
    } else{
        printf("%s\n",message[people]);
    }
}

int main(void){          //look up tables to wirte fster code
    
    
    print_party_size_info(0);    
    print_party_size_info(1);   
    print_party_size_info(2);   
    print_party_size_info(4);   
    print_party_size_info(10);   
    print_party_size_info(3);   
    printf("\n\n\n\n*****END OF PROGRAM*****\n");
    return 0;
}