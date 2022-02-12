#include "client_api.h"
//#define DEBUG

const char* prompt = "ssafy >> ";

int main(int argc, char* argv[])
{  
    int token_size = 0;
    char buffer[MAX_BUFFER_LEN] ={ 0 };
    char* token[MAX_TOKEN_LEN] = {NULL,};
    while(1)
    {   
        usleep(100000);
        signal(SIGINT, terminate);

        memset(buffer, 0, sizeof(buffer));
        memset(token, 0, sizeof(token));
        
        printf("%s", prompt);
        gets(buffer);

        if(isconnect == 1)
        {
            write(fd, buffer, MAX_BUFFER_LEN);
            continue;
        }

        token_size = parsing(buffer, token, " ");

#ifdef DEBUG
    printf("DEBUG: %s\n", buffer);
    printf("DEBUG: TOKEN[0] : %s, TOKEN[1] : %s\n", token[0], token[1]);
#endif

        if(token_size == 2 && !strcmp(token[0], "connect"))
        {
            int ret = init(token[1], 12345 );
            if(ret < 0)
            {
                error("ERROR INIT FAILED\n");
                exit(-1);
            }
            
            pthread_create(&recv_tid, NULL, recv_data, NULL);
            continue;
        }

        printf("NOT CONNECT TO SERVER\n");
    }
}

