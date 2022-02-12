#include <stdio.h>
#include <stdint.h>

typedef union abc {
    uint64_t all;
    uint8_t buf[4];
}abc_t;

abc_t mem;

int main(void)
{
    mem.all = 0xABCD12345678CD01;
    
    printf("0x");
    for(int i = 0; i < 8; ++i)
    {
        printf("%02X", mem.buf[i]);
    }
    printf("\n");
    return 0;
}
