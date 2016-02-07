#include <xinu.h>
#include <stdio.h>
extern int stacktop(void);
extern syscall stackdepth(void);

char myfuncA(char* msg) {
    kprintf(" --- Inside myfuncA. ----\n");
    //stackdepth();
    stacktop();
    return msg[0];
}

int myappA(char* msg) {
    kprintf(" --- Inside myappaA. Before calling myfuncA. ----\n");
    //stackdepth();
    stacktop();
    char x = myfuncA(msg);
    kprintf(" --- Inside myappaA. After calling myfuncA. ----\n");
    //stackdepth();
    stacktop();
    int pid = getpid();
    int ppid = getppid();
	struct procent	*pproc = &proctab[ppid];
    kprintf("[Pid %d] Main process's ESP is 0x%08X\n", pid, pproc->prstkptr);
    return (int) x+1;
}
