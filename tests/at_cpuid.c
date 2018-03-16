#include "stdio.h"

static void cpuid(void)
{
    asm volatile ("push %%" "bx; cpuid; pop %%" "bx"
                  : : : "eax", "ecx", "edx");
}

int main(void)
{
    cpuid();
    return 0;
}
