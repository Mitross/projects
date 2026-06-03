#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int main(){

    time_t rawtime = 0; //time_t holds bigger than long epoch sincde jan 1 1970(epoch)
    struct tm *ptime = NULL;
    bool isrunning = true;



    printf("DIGITAL CLOCK\n");

    while(isrunning){
        time(&rawtime);        

        ptime = localtime(&rawtime);

        printf("%02d : %02d : %02d\r",ptime->tm_hour, ptime->tm_min , ptime->tm_sec);

        fflush(stdout);
        sleep(1);
        
    }



    return 0;
}