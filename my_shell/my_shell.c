#include "input.h"
#include "history.h"
#include "header.h"

void selection(char* command);

#define MAX_COMMAND_LEN  256

const char* prompt = "SSAFY > ";

int main(int argc, char** argv )
{
    io_init();
    history_init();

    while(1)
    {   
        printf("%s", prompt);

        char command[MAX_COMMAND_LEN];
        gets(command);

        //printf("%s\n", command);

        history_insert((char*)command);
        selection(command);
    }
    return 0;
}

void selection(char* command)
{
   
        /* ---------------------------------
         * DATE
         ---------------------------------*/       
        if(!strcmp(command, "date"))
        {   
            int sys = system("date");

            if(sys < 0)
            {
                printf("ERROR\n");
            }
        }
        /* ---------------------------------
         * UPTIME
         ---------------------------------*/ 
        else if(!strcmp(command, "uptime"))
        {   
            int sys = system("uptime");

            if(sys < 0)
            {
                printf("ERROR\n");
            }
        }
        /* ---------------------------------
         * LS
         * ---------------------------------*/ 
        else if(!strcmp(command, "ls"))
        {   
            char opt[MAX_COMMAND_LEN + 4];
            sprintf(opt, "%s %s", command, "-al");
            int sys = system(opt);

            if(sys < 0)
            {
                printf("ERROR\n");
            }
        }
        /* ---------------------------------
         * LOG
         * ---------------------------------*/ 
        else if(!strcmp(command, "log"))
        {
            int sys = system("dmesg");

            if(sys < 0)
            {
                printf("ERROR\n");
            }
        }

        /* ---------------------------------
         * HISTORY
         * void history_init();                 => HISTORY LINKED LIST INIT
         * void history_insert(char* command);  => COMMNAD INSERT INT LINKED LIST
         * void history_viewer();               => SHOW LINKED LIST
         * void history_clear();                => LINKED LIST FREE
         * int history_system(char* command);   => EXECUTE HISTOTY USING !
         * 
         * int isNumber(char* buffer);          => PARSING !N COMMAND
         * ---------------------------------*/ 
        else if(!strcmp(command, "history")){
            history_viewer();

        }
        else if(command[0] == '!' && isdigit(command[1]))
        {
            int ret = history_system(command);
            
            if(ret < 0)
            {   
                printf("ERROR\n");
            }
        }
        else if(!strcmp(command, "hclear")){
            history_clear();
        }

        /* ---------------------------------
         * MACRO
         * void io_init();                  => MACRO INIT
         * void io_add(Data echo);          => FILL CONTAINER ARRAY
         * void input_stream(Data data[]);  => WRITE IN FILE
         * void output_stream();            => READ IN FILE
         *
         * int isvalid(char* command)       => MACRO VALID CHECK FUNCTION
         * Data* parsing(char* command);    => TOKEN1 = TOKEN2 PARSING FUNCTION
         * void searching(char* target);    => SEARCHING CONINTER ARRAY TO FIND TARGET
         * ---------------------------------*/ 
        else if(isvalid(command))
        {
            Data* ret =  parsing(command);
            io_add( *ret );
            input_stream(container);
        }
        else if(!strncmp(command, "echo", 4))
        {
            char str[MAX_COMMAND_LEN];

            strncpy(str, command + 5, strlen(command) - 5 );
            str[strlen(command) - 5] = '\0';
            
            searching(str);
        }

        /* ---------------------------------
         * EXIT
         * SHUTDOWN PROGRAM
         * ---------------------------------*/ 
        else if(!strcmp(command, "exit"))
        {
            exit(1);
        }
        
        /* ---------------------------------
         * ERROR
         * ---------------------------------*/ 
        else{
            printf("ERROR\n");
        }
}
