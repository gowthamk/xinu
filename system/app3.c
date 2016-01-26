#include <xinu.h>
#include <stdio.h>

int app3() {
    int res = 101 * 555;
    int my_pid = getpid();
    int my_prio = getprio(my_pid);
    kprintf("app3: 101*555=%d.\n",res);
    kprintf("app3: my pid is %d and my priority is %d.\n",my_pid,my_prio);
    int parent_pid = getppid();
    kprintf("app3: my parent pid is %d.\n",parent_pid);
    return 0;
}
