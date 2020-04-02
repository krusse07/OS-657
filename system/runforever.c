#include <xinu.h>
#include <stdio.h>
#include <string.h>

void runforever(int32 priority)
{
    kprintf("priority: %d\n", priority);
    kprintf("getpid: %d\n", getpid());

       while (1) {

    }
}
