#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LEN 2048

void parsing(char* line);
int getTime(char* line);

int main(void)
{
    system("dmesg > log.txt");
    FILE* fp = fopen("log.txt", "r");

    while(1){
        char buffer[MAX_BUFFER_LEN];
        char* ret = fgets(buffer, MAX_BUFFER_LEN, fp);
        parsing(buffer);

        if(ret == NULL){break;}
    }

    return 0;
}

/*-----------------------------------
 * PARSING()
 *----------------------------------*/
void parsing(char* line)
{   
    if(strstr(line, "sd") > 0)
    {
        printf("%s", line);
        return;
    }

    if(strstr(line, "syste") > 0)
    {
        printf("%s", line);
        return;
    }

    int ret = getTime(line);
    if(ret > 0)
    {
        if(ret % 2 == 0){
            printf("%s", line);
        }
        return;
    }
}

/*-----------------------------------
 * GETTIME()
 *----------------------------------*/
int getTime(char* line)
{
    char ttime[MAX_BUFFER_LEN] = {0};

    char* p1 = index(line, '.');
    char* p2 = index(line, ']');

    if(p1 == NULL || p2 == NULL)
    {
        return -1 ;
    }

    strncpy(ttime, p1 + 1, p2 - p1 -1);
    int num = atoi(ttime);

    return num;
}