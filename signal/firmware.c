#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_sigterm_handler(int signo)
{
    if(signo == SIGTERM)
    {
        printf("Bye\n");
        exit(1);
    }
}

void signal_sigusr1_handler(int signo)
{
    printf("[Button Clicked]\n");
}

void signal_sigusr2_handler(int signo)
{
    system("clear");
    printf("RESET\n");
}

int main(void)
{
    setbuf(stdout, NULL);
    int i = 0;

    signal(SIGTERM, signal_sigterm_handler);
    signal(SIGUSR1, signal_sigusr1_handler);
    signal(SIGUSR2, signal_sigusr2_handler);

    while(1)
    {
        for(i = 0; i < 26; ++i){
            printf("%c", (char)('A' + i));
            usleep(100000);
        }
        for(i = 25; i >= 0; --i){
            printf("%c", (char)('A' + i));
            usleep(100000);
        }
    }
    return 0;
}
