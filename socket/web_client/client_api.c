#include "client_api.h"

void error(char* msg)
{
    perror(msg);
    exit(1);
}

void terminate()
{
    fprintf(stderr, "\nDISCONNECT\n");
    isconnect = 0;
    close(fd);
    exit(1);
}

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

int init(char* ip, int port)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        error("ERROR SOCKET OPEN FAILED\n");
        return -1;
    }
    
    struct sockaddr_in addr = { 0 };
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(port);
    addr.sin_addr.s_addr    = inet_addr("52.79.44.234");
    //addr.sin_addr.s_addr    = inet_addr(ip);

    int ret = connect(fd, (struct sock_addr *)&addr, sizeof(addr));
    if(ret < 0)
    {
        error("ERROR CONNECT FAILED\n");
        return -1;
    }

    isconnect = 1;
    return ret;
}

void* recv_data()
{
    while (1)
    {
        char buffer[MAX_BUFFER_LEN] = { 0 };
        int ret = read(fd, buffer, MAX_BUFFER_LEN);
        printf("Recv: %s\n", buffer);
        
        if(ret == 0) 
        {
            terminate();
        }
    }
}