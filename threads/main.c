#include <pthread.h>
#include <stdio.h>

void* foo(void* arg){
    pthread_t thisThread = pthread_self();
    printf("the id of this thread is: %lu\n",(unsigned long)thisThread);
    return NULL;
}

int main(){
    pthread_t thread;

    pthread_create(&thread,NULL, foo, NULL);
    pthread_join(thread, NULL);


    return 0;
}