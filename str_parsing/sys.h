#ifndef __SYS_H_
#define __SYS_H_

#include "parse.h"

#define MAX_BUFFER_LEN 2048
#define MAX_DATA_LEN 2048

typedef struct ip_storge{
    char* ip;
    int cnt;
}ipst;

ipst ip_storage[MAX_DATA_LEN]; 
int ip_cnt;

typedef struct fail_data{
    char* mon;
    char* day;
    int cnt;
}Faildata;

Faildata fail_storage[MAX_DATA_LEN];
int fail_cnt;

typedef struct logs{
    char* log_opt;
    int cnt; 
}Logs;

Logs logs[4];

int isipvalid(char* str);
void insert_ip_count(char* ip);
void insert_fail_count(char* mon, char* day);
void insert_opt_count(char* option);

#endif 