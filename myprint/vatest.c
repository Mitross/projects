#include <stdarg.h>
#include <stdio.h>

int test(int n, ...){
    va_list list;
    va_start(list, n);

    for(int i = 0;i<n; i++){
        printf(" %d\n",va_arg(list, int));
    }
    va_end(list);

    va_list llist;
    va_start(llist,n);
    for(int i = 0;i<n; i++){
        printf(" %d\n",va_arg(llist, int));
    }
    va_end(llist);
}

int main(){
    test(3,1,2,3);
    return 0;
}