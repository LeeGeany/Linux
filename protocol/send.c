#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef union packet{
    uint32_t all;
    struct {
        uint8_t key;
        uint8_t num;
        uint8_t data;
        uint8_t parity;
    };
}packet_t;

packet_t make_packet(uint8_t key, uint8_t num, uint8_t data, uint8_t parity);
void read_packet(packet_t recv_packet);
const uint8_t dest = 24;

int main(void)
{

    while(1)
    {   
        char buffer[256];
        gets(buffer);

        uint8_t cnt = 0;
        for(char* idx = buffer; *idx != '\0'; idx++){
            packet_t pack = make_packet(dest, cnt++, (uint8_t)*idx, (uint8_t)*idx % 2);
            read_packet(pack);
        }
    }
    return 0;
}

packet_t make_packet(uint8_t key, uint8_t num, uint8_t data, uint8_t parity)
{
    packet_t new_packet;
    new_packet.key = key;
    new_packet.num = num;
    new_packet.data = data;
    new_packet.parity = parity;
    return new_packet;
}

void read_packet(packet_t rpack)
{
    printf("----------------------------\n");
    printf("dest : %d\n", rpack.key);
    printf("num : %d\n", rpack.num);
    printf("pack : %c\n", (char)rpack.data);
    printf("parity : %d\n", rpack.parity);
    fflush(stdout);
}