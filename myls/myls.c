#define _XOPEN_SOURCE 500
#define _GNU_SOURCE 

#include <stdio.h>
#include <ftw.h>

int print_name(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
    if (ftwbuf->level > 1){
        return FTW_CONTINUE;
    }
    else{
        if ( typeflag == FTW_D){
            printf("\033[1;34m%s\n",fpath);
        }
        else if(typeflag == FTW_F)
        {
            printf("\033[1;37m%s\n",fpath);
        }
        else{
            printf("\033[1;32m%s\n",fpath);
        }
        return 0;
    }


}


void print_dir_contents(char* dir){
    nftw(dir, print_name, 1, 0);
}


int main(int argc, char *argv[]){

    if(argc == 2){
        //list contents of the given dir
        print_dir_contents(argv[1]);

    }
    else if(argc == 1){
        //liust contents of curr dir

        char* curr_dir = ".";
        print_dir_contents(curr_dir);
    }
    else{
        printf("Too many arguments given: Usage %s <dir>\n",argv[0]);
        return 0;
    }

    return 0;
}