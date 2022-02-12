
#include "sys.h"
#include <ctype.h>

extern int ip_cnt = 0;
extern int fail_cnt = 0;

extern Logs logs[4] = {
    {"ftpd", 0},
    {"su", 0},
    {"named", 0},
    {"sshd", 0}
};

int isipvalid(char* str)
{
    if(!isdigit(*str))
    {
        return 0;
    }
    return 1;
}

void insert_ip_count(char* ip)
{
    if(!isipvalid(ip))
    {
        return;
    }

    for(int i = 0; i< ip_cnt; ++i)
    {
        if(!str_strcmp(ip_storage[i].ip, ip))
        {
            ip_storage[i].cnt++;
            return;
        }
    }
    
    ip_storage[ip_cnt].ip = ip;
    ip_storage[ip_cnt++].cnt = 1;
}

void insert_fail_count(char* mon, char* day)
{
    for(int i = 0; i< fail_cnt; ++i)
    {
        if(!str_strcmp(fail_storage[i].mon, mon) && ! str_strcmp(fail_storage[i].day, day))
        {
            fail_storage[i].cnt++;
            return;
        }
    }
    fail_storage[fail_cnt].mon = mon;
    fail_storage[fail_cnt].day = day;
    fail_storage[fail_cnt++].cnt = 1;
}

void insert_opt_count(char* option)
{
    if( str_indexof(option, "ftpd", 0) == 0)
    {
        logs[0].cnt++;
    }
        if( str_indexof(option, "su", 0) == 0)
    {
        logs[1].cnt++;
    }
        if( str_indexof(option, "named", 0) == 0)
    {
        logs[2].cnt++;
    }
        if( str_indexof(option, "sshd", 0) == 0)
    {
        logs[3].cnt++;
    }
}
