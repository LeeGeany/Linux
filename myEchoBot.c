#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char* prompt = "SSAFY_ECHOBOT >> ";

int isNumber(char* buffer);

int main(void)
{
    while(1)
    {
        char buffer[100];
        printf("%s", prompt);
	scanf("%s", buffer);

        if(!strcmp(buffer, "exit") || !strcmp(buffer, "bye"))
        {
            break;
        }

        int ret = isNumber( (char*)buffer );
        if( ret > -1 ) 
        {
            for(int i = 1; i <= ret; ++i)
            {
                printf("%d", i);
            }
            printf("\n");
            continue;
        }

        printf("%s\n", buffer);
    }

    return 0;
}

/*
 * isNumber 함수는 입력받은 문자열이 모두 정수일때
 * 문자열을 정수로 변환시켜 리턴한다.
 * 단 정수가 아닐경우, 1 부터 100까지 범위를 벗어난 경우 -1을 반환한다. 
 */

int isNumber(char* buffer)
{
    for(char* idx = buffer; *idx != '\0'; idx++)
    {
        if(!isdigit(*idx))
        {
            return -1;
        }
    }

    int ret = atoi(buffer);
    return ret > 100 || ret < 1 ? -1 : ret;
}
