#include <stdio.h>

#include "read_stack_memory.h"

int main(int argc, char const *argv[])
{
     char a = 2;
     char b = 3;
     short i = 0x1234;
     char x = -127;
     long sn1 = 32;
     long sn2 = 22;
     int y[] = {0x11223344, 0x44332211};

    printf("short size: %zu bytes\n", sizeof(short));
    printf("char size: %zu bytes\n", sizeof(char));
    printf("long size: %zu bytes\n", sizeof(long));
    printf("int size: %zu bytes\n", sizeof(int));

    dump_stack_memory((u8 *)&b + sizeof(short), (u8 *)&y);

    return 0;
}
