#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_LEN  1025
#define MAX_TOKEN_LEN   5

typedef struct info{
    struct sockaddr* new_addr;
    int* len_ptr;
    int* client_fd;
}info_t;

typedef struct node{
    char key[MAX_BUFFER_LEN];
    char value[MAX_BUFFER_LEN];
    struct node* next;
}node_t;

int fd;

node_t* head = NULL;
node_t* tail = NULL;

int sock_init();
void error(char* msg);
void terminate();
void* sock_accept();
void* conn_node();
void insert(char* key, char* value);
void show();
int parsing(char* str, char* token[], char* ch);
node_t* searching(char* nkey);
void clearing();

void get_file();
void put_file();

int main(void)
{
    signal(SIGINT, terminate);
    get_file();

    int ret = sock_init();
    if(fd < 0)
    {
        error("ERROR INIT FAILED\n");
        return -1;
    }    
    printf("SERVER INITIATE COMPLETE [STATE : LISTEN]\n");
    
    while(1)
    {
        struct sockaddr* new_addr = (struct sockaddr*)malloc(sizeof(struct sockaddr));
        int* len_ptr = (int*)malloc(sizeof(int));
        int* client_fd = (int*)malloc(sizeof(int));

        memset(new_addr, 0, sizeof(struct sockaddr));
        *client_fd = accept(fd, new_addr, len_ptr);            // Accept first client connection request on the queue;
        if(*client_fd < 0)
        {
            error("ERROR ACCEPTED FAILE\n");
            free(new_addr);
            free(len_ptr);
            free(client_fd);
            exit(1);
        }

        // connect response
        write(*client_fd, "Response", 9);

        // Make pthread data argument
        info_t* new_info = (info_t*)malloc(sizeof(info_t));
        new_info->new_addr = new_addr;
        new_info->len_ptr = len_ptr;
        new_info->client_fd = client_fd;

        // pthread section
        pthread_t* recv_tid = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(recv_tid, NULL, conn_node, new_info);
        pthread_join(*recv_tid, NULL);
        listen(fd, 10);
    }

    close(fd);
    return 0;
}

void error(char* msg)
{
    perror(msg);
    exit(1);
}

void terminate()
{
    fprintf(stderr, "\nDISCONNECT\n");
    put_file();
    close(fd);
    exit(1);
}

int sock_init()
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        error("ERROR SOCKET OPEN FAILED\n");
        return -1;
    }

    struct sockaddr_in addr = { 0 };
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(12345);
    addr.sin_addr.s_addr    = 0;

    int ret = bind(fd, (struct sockaddr*) &addr, sizeof(struct sockaddr));
    if(ret < 0)
    {
        error("ERROR BIND FAILED\n");
        return -1;
    }

    ret = listen(fd, 10);
    if(ret < 0)
    {
        error("ERROR LISTEN FAILED\n");
        return -1;
    }
    return ret;
}

void* conn_node(void* new_info)
{
    info_t* ninfo = (info_t*) new_info;
    int token_size = 0;
    char buffer[MAX_BUFFER_LEN] ={ 0 };
    char* token[MAX_TOKEN_LEN] = {NULL,};

    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(token, 0, sizeof(token));
        read( *(ninfo->client_fd), buffer, MAX_BUFFER_LEN);
        token_size = parsing(buffer, token, " ");

#ifdef DEBUG
    printf("DEBUG: %s\n", buffer);
    printf("DEBUG: [%s] [%s]\n", token[0], token[1]);
#endif

        if(token_size == 2 && !strcmp(token[0],"save"))
        {
            char* kv[2] = {NULL,};
            int cnt = parsing(token[1], kv, ":");
            if(cnt != 2)
            {
                write(*(ninfo->client_fd), "NOT PROPER FORMAT", 18);
                continue;
            }

            insert(kv[0], kv[1]);
            write(*(ninfo->client_fd), "SAVE OK", 9);
            continue;
        }

        if(token_size == 2 && !strcmp(token[0], "read"))
        {
            node_t* ret = searching(token[1]);
            if(ret != NULL)
            {
                write(*(ninfo->client_fd), ret->value, strlen(ret->value));
            }
            else
            {
                write(*(ninfo->client_fd), "NO DATA EXIST", 14);
            }
            continue;
        }

        if(token_size == 1 && !strcmp(token[0], "clear"))
        {
            clearing();
            write(*(ninfo->client_fd), "CLEAR OK", 9);
            continue;
        }
#ifdef DEBUG
        if(token_size == 1 && !strcmp(token[0], "show"))
        {
            show();
            continue;
        }
#endif
        if(token_size == 1 && !strcmp(token[0], "exit"))
        {
            terminate();
        }

        write(*(ninfo->client_fd), "INVALID COMMAND", 20);
    }
}

//-----------------

int parsing(char* str, char* token[], char* ch)
{
    int idx = 0;
    char* ptr = strtok(str, ch);

    while(ptr != NULL)
    {
        token[idx++] = ptr;
        ptr = strtok(NULL, ch);
    }
    return idx;
}

void get_file()
{
    FILE* fd = fopen("server.dat", "r");
    while(1)
    {
        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        int rd = fread(newNode, sizeof(node_t), 1, fd);
        if(!rd){ break; }

        newNode->next = NULL;
        if(head == NULL)
        {
            head = newNode;
            tail = newNode; 
        }
        else
        {
            tail = tail->next = newNode;
        }
    }
    fclose(fd);
}

void put_file()
{
    FILE* fd = fopen("server.dat", "w");
    for(node_t* now = head; now != NULL; now = now->next)
    {
        fwrite(now, sizeof(node_t), 1, fd);
        free(now);
    }
    fclose(fd);
}

node_t* searching(char* nkey)
{
    for(node_t* now = head; now != NULL; now = now->next)
    {
        if(!strcmp(now->key, nkey))
        {
            return now;
        }
    }
    return NULL;
}

void clearing()
{
    for(node_t* now = head; now != NULL; )
    {
        now = now->next;
        free(now);
    }
    head = NULL;
}

void insert(char* nkey, char* nvalue)
{
    node_t* isExist = searching(nkey);

    if(isExist != NULL)
    {
        strcpy(isExist->value, nvalue);
        return;
    }

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    strcpy(newNode->key,nkey);
    strcpy(newNode->value, nvalue);

    if(head == NULL)
    {
        head = newNode;
        tail = newNode; 
    }
    else
    {
        tail = tail->next = newNode;
    }
}

void show()
{
    for(node_t* now = head; now != NULL; now = now->next)
    {
        printf("key : %s, value : %s\n", now->key, now->value);
    }
}