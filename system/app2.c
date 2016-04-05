#include <xinu.h>
#include <stdio.h>
extern int app3(void);

int app2() {
    int my_pid = getpid();
    kprintf("app2: my pid is %d.\n",my_pid);
    resume(create(app3, 65536, 20, "app3", 0));
    kprintf("app2: sleeping for 5ms.\n");
    sleepms(5000);
    kprintf("app2: wokeup. My pid is %d.\n",my_pid);
    return 0;
}

