#ifndef INPUT_H_
#include "header.h"

#define MAX_STRING_LEN  256

typedef struct data{
    char key[MAX_STRING_LEN];
    char value[MAX_STRING_LEN];
}Data;

Data container[20];
int cnt;

void io_init();
void io_add(Data echo);
void input_stream(Data data[]);
void output_stream();

int isvalid(char* command);
Data* parsing(char* command);
void searching(char* target);

#endif /*INPUT_H_*/
