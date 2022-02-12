#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_alarm_handler()
{
    printf("SYSTEM ERROR\n");
    exit(1);
}

int main(void)
{
    signal(SIGALRM, signal_alarm_handler);

    while(1){
        alarm(3);
        char command[1024]; gets(command);
        char com[1030];
        sprintf(com, "%s %s", "echo", command);
        system(com);
    }
    return 0;
}
