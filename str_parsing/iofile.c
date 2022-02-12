#include <stdio.h>
#include "iofile.h"
#include "sys.h"

#define DEBUG 1

void infile1()
{
    FILE* fp = fopen("./ipcount.csv", "w");

    for(int i= 0; i< ip_cnt; ++i)
    {   
        char buffer[MAX_BUFFER_LEN] = { 0 };
#ifdef DEBUG
    printf("%s ,%s\n", ip_storage[i].ip, str_tostring(ip_storage[i].cnt));
#endif
        sprintf(buffer, "%s ,%s\n", ip_storage[i].ip, str_tostring(ip_storage[i].cnt));
        fwrite(buffer, str_strlen(buffer), 1, fp);
    }
    close(fp);
}

void infile2()
{
    FILE* fp = fopen("./failcount.csv", "w");

    for(int i= 0; i< fail_cnt; ++i)
    {   
        char buffer[MAX_BUFFER_LEN] = { 0 };
        
#ifdef DEBUG
        printf("%s %s %s\n", fail_storage[i].mon, fail_storage[i].day, str_tostring(fail_storage[i].cnt));
#endif
        
        sprintf(buffer, "%s%s ,%s\n",  fail_storage[i].mon, fail_storage[i].day, str_tostring(fail_storage[i].cnt));
        fwrite(buffer, str_strlen(buffer), 1, fp);
    }
    close(fp);
}

void infile3()
{
    FILE* fp = fopen("./optcount.csv", "w");
    for(int i = 0; i< 4; ++i){
        char buffer[MAX_BUFFER_LEN] = { 0 };
        
#ifdef DEBUG
        printf("%s %s\n", logs[i].log_opt, str_tostring(logs[i].cnt));
#endif

        sprintf(buffer, "%s ,%s\n", logs[i].log_opt, str_tostring(logs[i].cnt));
        fwrite(buffer, str_strlen(buffer), 1, fp);
    }
    close(fp);
}