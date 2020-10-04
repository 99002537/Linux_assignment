#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char* argv[]){

    //missing irrelevant part where argum is set

    int status,i;
    char cmd[512];
    pid_t process_id = 0;
    for (i=0; i<=5;i++)
    {
        process_id = fork();
        if (process_id < 0)
        {
            printf("fork failed - %d!\n",i);
            continue;
        }
        else if(process_id > 0) {
            printf("process_id of child process %d \n", process_id);
        }
        else
        {
           
            status = system(cmd);
            exit(0);
        }
    }
    return 0;
}
