#include <xinu.h>
#include <stdio.h>

int app1() {
    int my_pid = getpid();
    kprintf("app1: my pid is %d.\n",my_pid);
    return 0;
}
