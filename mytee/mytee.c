#include <stdio.h>

int main(int argc, char *argv[]){
	
	if(argc != 2){
		printf("usage: %s <filename>\n",argv[0]);
		return 0;
	}
	
	FILE *fp = fopen(argv[1],"w");
	if(fp == NULL){
		perror("opening file to write went wrong");
		return 0;
	}	
	
	

	char c;
	//read characters for stdin
	while( (c = getchar()) != EOF ){
		//print to console
		putchar(c);//stdout is predefined
			
		//store in a file
			
		putc(c, fp); 
	}

}

