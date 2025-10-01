#ifndef READ_STACK_MEMORY_H
#define READ_STACK_MEMORY_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

typedef unsigned char u8;

static void dump_stack_memory(const u8 *from, const u8 *to)
{
    const u8 *lo = from;
    const u8 *hi = to;

    printf("From %p to %p ", hi, lo);

    printf(GREEN "Adresse \t Valeur (dec) \t Valeur (hex)\n");
    printf("---------------------------------------------\n");

    for (const u8 *i = lo; i != hi; i++)
    {
        printf("%p \t %i \t\t 0x%02X\n", i, *i, *i);
    }

    printf("---------------------------------------------\n");
}

static void read_stack_bytes(size_t buffer_size, u8 buffer[], const u8 *start)
{
    u8 *ptr = (u8 *)start;
    for (size_t i = 0; i < buffer_size; i++)
    {
        buffer[i] = *ptr;
        ptr++;
    }
}

static void diff_dump(const u8 *start, size_t buffer_size, const u8 buffer_before[], const u8 buffer_after[])
{
    printf(GREEN "Addr\t\tDec\tHex (changed bytes only)\n");
    printf("------------------------------------------------\n");

    // 2.2 Complétez ce programme pour afficher les différences entre buffer_before et buffer_after

    // Ligne pour afficher une diff
    // printf("%p\t%3u\t0x%02X  (was %3u / 0x%02X)\n", &start[i], buffer_after[i], buffer_after[i], buffer_before[i], buffer_before[i]);

    printf("------------------------------------------------\n");
}

#endif