#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand(time(NULL));
	char allowed_characters[] = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRTSUWXYZ123456789";
	char password[20];
	for(int i=0; i<sizeof(password); i++){
		int random_number = rand() % sizeof(allowed_characters);
		printf("%c",allowed_characters[random_number]);
	}
	printf("\n");
}
