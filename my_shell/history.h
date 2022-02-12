#ifndef HISTORY_H_
#include "header.h"

typedef struct node{
    int num;
    char cmd[100];
    struct node* next;
}Node;

Node* head;
Node* tail;

int history_cnt;

void history_init();
void history_insert(char* command);
void history_viewer();
void history_clear();
int history_system(char* command);

int isNumber(char* buffer);

#endif /*HISTORY_H_*/