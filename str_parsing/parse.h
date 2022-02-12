#ifndef __PARSE_H_
#define __PARSE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int str_strcmp(char* oper1, char* oper2);
int str_strlen(char* str);
int str_indexof(const char* str, const char* target, int start);
char* str_trim(char* str);
char* str_insert(char* str, char* target, int index);
char* str_delete(char* str, int target_index, int num);
char* str_substring(char* str, int start, int cnt);
int str_split(char* str, char* tokens[], char target);
char *str_replace(char *s, const char *olds, const char *news);
char* str_tostring(int num);
int str_tointeger(char *s, char last);

#endif