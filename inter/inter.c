//simpel interpreter for super simple aritmatic expressions
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 1000

#define INT 0
#define OPERATOR 1
#define INT_STR "INT"
#define OPERATOR_STR "OPERATOR"
#define ERR -1

typedef struct{
    int type;
    char operator_value;
    int number_value;
} Token; // token is a unit of meaning 


size_t current_pos=0;
Token current_token;

bool is_digit(char c){
    return ( c >= '0' && c <= '9');
}
//represnts the token as string in given string s
void token_str(Token token, char *s){
    sprintf(s, "Token (type=%s, number_value=%d, operator_value=%c)",token.type == INT ? INT_STR : OPERATOR_STR, token.number_value, token.operator_value);
}
bool is_operator(char c){
    return c == '+' || c == '-';
}

bool is_whitespace(char c){
    return c == ' ';
}
void parse(int type){


    if(current_token.type != type){
        char s[100];
        token_str(current_token,s); 

        printf("Syntax error at pos %ld : expexted token of type %s , but recieved token  %s\n", current_pos, type == INT ? INT_STR : OPERATOR_STR, s);
        exit(-1);
    }
}

//sets the current token and advances the current pos pointer
void get_next_token(char *text){

    char c = text[current_pos];
   //skip whitespaces 
    while(is_whitespace(c)){
        current_pos += 1;
        c = text[current_pos];
    }


    if(is_digit(c)){
        int current_number = c - '0';
        current_pos +=1;
        while(is_digit(text[current_pos])){
            current_number *= 10;
            current_number += (text[current_pos] - '0');
            current_pos +=1; 
        }
        current_token.type = INT;
        current_token.number_value = current_number; //based on asci numeric representation
        current_token.operator_value = ' ';

    }
    else if(is_operator(c)){
        current_token.type = OPERATOR;
        current_token.number_value = 0;  
        current_token.operator_value = c;
    }
    else{
        printf("Invalid token recieved at pos %ld: %c\n", current_pos, c); 
        exit(-1);
    }
    current_pos += 1;

}

 

int interpret(char *text){
    int result = 0;

    //for each char from the input text create tokens -->  tokenier (reads from text to tokens)
    
    get_next_token(text);
    parse(INT);
    result +=  current_token.number_value;


    size_t len = strlen(text);
    while (current_pos < len - 2){
    get_next_token(text);
    parse(OPERATOR);
    char operator = current_token.operator_value;

    get_next_token(text);
    parse(INT);
    int operand = current_token.number_value;

    
    
    if(operator == '+') result += operand;
    else result -= operand;
    }
    return result;
}

int main(){
    
    char s[INPUT_LENGTH];
    memset(s, 0, INPUT_LENGTH);

    bool isrunning = true;

    printf("interpreter running...\n");
    
    int result;
    while(isrunning){
        current_pos = 0;
        printf(">>> ");
        fgets(s, INPUT_LENGTH, stdin);
        result = interpret(s);
        printf("%d\n",result);
        memset(s, 0, INPUT_LENGTH);
    }

}