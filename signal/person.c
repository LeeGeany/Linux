#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

const char* prompt = "Shell >> ";

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        perror("FORMAT : ./[PROGRAM] [PROCESS ID]\n)");
        return -1;
    }

    int pid = atoi(argv[1]);

    while(1){
        printf("%s", prompt);
        int command; scanf("%d", &command);

        if(command == 1)
        {
            kill(pid, SIGUSR1);
            continue;
        }

        if(command == 2)
        {
            kill(pid, SIGUSR2);
            continue;
        }

        if(command == 3)
        {
            kill(pid, SIGTERM);
            break;
        }
    }

    return 0;
}
