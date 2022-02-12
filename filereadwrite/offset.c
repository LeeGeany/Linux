#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd = open("./file_seek.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("ERROR [FILE : %s][LINE : %d] FILE OPEN FAILED\n", __FILE__, __LINE__);
        exit(1);
    }

    size_t rd = 0;
    char buf[27] = {0};

    lseek(fd, 0, SEEK_SET);
    memset(buf, 0, sizeof(buf));
    rd = read(fd, buf, 5);
    printf("Q1 : %s\n", buf);

    lseek(fd, -5, SEEK_END);
    memset(buf, 0, sizeof(buf));
    rd = read(fd, buf, 5);
    printf("Q2 : %s\n", buf);

    lseek(fd, 0, SEEK_SET);
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        rd = read(fd, buf, 3);
        if(!strcmp(buf, "GHI"))
        {
            lseek(fd, 5, SEEK_CUR);
            memset(buf, 0, sizeof(buf));
            rd = read(fd, buf, 3);
            printf("Q3 : %s\n", buf);
            break;
        }

        lseek(fd, 3, SEEK_CUR);
    }

    close(fd);
    return 0;
}
