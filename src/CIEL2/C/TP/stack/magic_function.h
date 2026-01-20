#ifndef MAGIC_FUNCTION_H
#define MAGIC_FUNCTION_H

#include "read_stack_memory.h"

__attribute__((noinline)) void *magic_function(size_t buffer_size, u8 stack_snapshot_buffer[buffer_size])
{
    void *rbp = __builtin_frame_address(0);

    volatile unsigned char a = 1;
    volatile unsigned char b = 2;
    volatile unsigned char c = 3;

    volatile unsigned char pad[255];
    for (unsigned char i = 0; i < 255; ++i)
    {
        pad[i] = 5;
    }

    printf("magic: rbp=%p pad[%d]=[%p .. %p)\n",
           rbp, 255, (void *)&pad[0], (void *)(&pad[0] + 256));

    read_stack_bytes(buffer_size, stack_snapshot_buffer, rbp - buffer_size);

    return rbp;
}

#endif