#include <stdio.h>
#include "magic_function.h"
#include "read_stack_memory.h"

int main(int argc, char const *argv[])
{
    void *rsp;
#if defined(__x86_64__)
    __asm__ volatile("mov %%rsp, %0" : "=r"(rsp));
#else
    // On supporte uniquement l'architecture x86_64
    return 1;
#endif

    const size_t N = 512;

    u8 before[N];
    u8 after[N];

    void *rbp = magic_function(N, before);

    printf("rsp=%p rbp=%p\n", rsp, rbp);

    read_stack_bytes(N, after, rbp - N);

    diff_dump(rbp, N, before, after);
    return 0;
}
