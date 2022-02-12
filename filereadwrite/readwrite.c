#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct node{
    char* name;
    int age;
}node_t;

void read_operation()
{
    int fd = open("struct_rw.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("ERROR [FILE : %s][LINE : %d] FILE OPEN FAILED\n", __FILE__, __LINE__);
    }

    node_t buf;
    size_t rd = read(fd, &buf, sizeof(buf));

    printf("name : %s\n", buf.name);
    printf("age  : %d\n", buf.age);

    close(fd);
}

void write_operation()
{
    int fd = open("struct_rw.txt", O_WRONLY|O_TRUNC|O_CREAT, 0666);
    if(fd < 0)
    {
        printf("ERROR [FILE : %s][LINE : %d] FILE OPEN FAILED\n", __FILE__, __LINE__);
    }

    node_t buf = {"LeeJinHee", 27};
    size_t wr = write(fd, &buf, sizeof(buf));

    close(fd);
}

int main(int argc, char* argv[])
{
    write_operation();
    read_operation();

    return 0;
}
