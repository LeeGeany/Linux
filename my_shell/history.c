#include "header.h"
#include "history.h"

/*---------------------------------------------------------------
 * HISTORY_INIT()
 * INIT HISTORY LINKED LIST 
 *---------------------------------------------------------------*/
void history_init()
{
    head = NULL;
    tail = NULL;
    history_cnt =1;
}

/*---------------------------------------------------------------
 * HISTORY_INSERT()
 * INSERT IN HISTORY LINKED LIST 
 *---------------------------------------------------------------*/
void history_insert(char* command)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->cmd, command);
    newNode->num = history_cnt++;

    if(head == NULL && tail == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {    
        tail = tail->next = newNode;
    }
}

/*---------------------------------------------------------------
 * HISTORY_VIEWER()
 * SHOW HISTORY LINKED LIST 
 *---------------------------------------------------------------*/
void history_viewer()
{
    for(Node* now = head; now != NULL; now = now->next)
    {
        printf("%d %s\n", now->num, now->cmd);
    }
}

/*---------------------------------------------------------------
 * HISTORY_CLEAR()
 * CLEAR HISTORY LINKED LIST 
 *---------------------------------------------------------------*/
void history_clear()
{
    head = NULL;
    tail = NULL;
    history_cnt = 1;
}

/*---------------------------------------------------------------
 * HISTORY_SYSTEM()
 * EXECUTE !N COMMAND 
 *---------------------------------------------------------------*/
int history_system(char* command)
{
    int ret = isNumber(command);
    if(ret < 0){return -1;}

    for(Node* now = head; now != NULL; now = now->next)
    {
        if(now->num == ret){    
            selection(now->cmd);
            return 0;
        }
    }
    return -1;
}

/*---------------------------------------------------------------
 * ISNUMBER()
 * VALID CHECK FOR !N COMMAND
 *---------------------------------------------------------------*/
int isNumber(char* buffer)
{
    for(char* idx = buffer + 1; *idx != '\0'; idx++)
    {
        if(!isdigit(*idx))
        {
            return -1;
        }
    }

    int ret = atoi(buffer + 1);
    if(ret > history_cnt){return -1;}

    return ret;
}
