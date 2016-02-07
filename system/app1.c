#include <xinu.h>
#include <stdio.h>
extern syscall stackdepth(void);

int app1() {
    uint32 sd = stackdepth();
    kprintf("app1: my stack depth is %d.\n",sd);
    return 0;
}
