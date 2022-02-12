#include "header.h"
#include "input.h"
/*---------------------------------------------------------------
 * IO_INIT()
 * GET ECHO DATA FOR INPUT.TXT FILE
 *---------------------------------------------------------------*/
void io_init()
{   
    output_stream();
    for(int i = 0; i< 20; ++i){
        if(!strcmp(container[i].key,"")){
            cnt = i;
            //printf("now ; %d\n", cnt);
            return;
        }
    }
}

/*---------------------------------------------------------------
 * IO_ADD()
 * ADD ECHO DATA IN CONTAINER STRUCT ARRAY
 *---------------------------------------------------------------*/
void io_add(Data echo)
{
    cnt++;
    if(cnt > 19)
    {
        perror("queue overflow\n");
        return;
    }
    container[cnt - 1] = echo;
}

/*---------------------------------------------------------------
 * INPUT_STREAM()
 * CONTAINER STRUCT ARRAY TO INPUT.TXT FILE
 *---------------------------------------------------------------*/
void input_stream(Data data[]){
    FILE* fp = fopen("./input.txt", "w");

    if(fp == NULL){
        perror("file open failed\n");
        return;
    }

    int ret = fwrite(data, sizeof(Data), 20, fp);

    if(ret < 0){
        perror("file write failed\n");
        return;
    }
    fclose(fp);
}

/*---------------------------------------------------------------
 * OUTPUT_STREAM()
 * INPUT.TXT FILE TO CONTAINER STRUCT ARRAY
 *---------------------------------------------------------------*/
void output_stream()
{
    FILE* fp = fopen("./input.txt", "r");

    if(fp == NULL){
        perror("file open failed\n");
        return;
    }

    int ret = fread(container, sizeof(Data), 20, fp);

    if(ret < 0){
        perror("file read failed\n");
        return;
    }
    fclose(fp);
}

/*---------------------------------------------------------------
 * ISVALID()
 * CHECK VALID FOR MACRO
 *---------------------------------------------------------------*/
int isvalid(char* command)
{ 
    int len = sizeof(command);
    int cnt = 0;
    for(int i = 0; i< len; ++i)
    {
        if(command[i] == '=')
        {   
            cnt++;
        }
    }

    return cnt == 1 ? 1 : 0;
}

/*---------------------------------------------------------------
 * PARSING()
 * PARSING MACRO COMMAND
 *---------------------------------------------------------------*/
Data* parsing(char* command)
{   
    Data* newData = (Data*)malloc(sizeof(Data));
    int len = strlen(command);
    //printf("%s, %d\n", command, len);
    
    for(int i = 0; i< len; ++i)
    {
        if(command[i] == '=' && command[i-1] == ' ')
        {
            strncpy(newData->key, command, i -1);
            newData->key[i-1] = '\0';
            break;
        }    
        else if(command[i] == '=' && command[i-1] != ' ')
        {
            strncpy(newData->key, command, i);
            newData->key[i] = '\0';
            break;
        }
    }
    
    for(int i = 0; i< len; ++i)
    {
        if(command[i] == '='&& command[i+1] == ' ')
        {
            strncpy(newData->value, command + i + 2, len - i);
            newData->value[len - i -1] = '\0';
            break;
        }
        else if(command[i] == '='&& command[i+1] != ' ')
        {
            strncpy(newData->value, command + i + 1, len - i);
            newData->value[len - i] = '\0';
            break;
        }
    }        
    //printf("%s,%send\n", newData->key, newData->value);
    return newData;
}

/*---------------------------------------------------------------
 * SEARCHING()
 * SEARCHING FOR ECHO DATA
 *---------------------------------------------------------------*/
void searching(char* target)
{   
    for(int i = 0; i< cnt; ++i )
    {
        if(!strcmp(target, container[i].key))
        {
            printf("%s\n" ,container[i].value);
            return;
        }
    }
    printf("ERROR\n");
}