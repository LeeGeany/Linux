#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid = fork();
    if( pid > 0){
        printf("Parents process run\n");
        wait(pid);
    }
    else if(pid == 0)
    {
        execlp("./run", NULL);
        sleep(2);
    }

    pid = fork();
    if( pid > 0){
        printf("Parents process run\n");
        wait(pid);
    }
    else if(pid == 0)
    {
        execl("/bin/ls", "ls",  NULL);
        sleep(2);
    }    

    pid = fork();
    if( pid > 0){
        printf("Parents process run\n");
        sleep(2);
        wait(pid);
    }
    else if(pid == 0)
    {
        execlp("htop", NULL);
    }        
    return 0;
}