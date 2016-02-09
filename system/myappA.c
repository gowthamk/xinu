#include <xinu.h>
#include <stdio.h>
extern int stacktop(void);
extern syscall stackdepth(void);

char myfuncA(char* msg) {
    kprintf("myfuncA\n");
    //stackdepth();
    stacktop();
    return msg[0];
}

int myappA(char* msg) {
    int pid = getpid();
    int ppid = getppid();
	struct procent	*pproc = &proctab[ppid];
    kprintf("myappA - \n");
    kprintf("currpid: %d\n",pid);
    kprintf("main's pid: %d\n",ppid);
    kprintf("main's esp is 0x%08X\n", pproc->prstkptr);
    kprintf("myappaA - before calling myfuncA\n");
    //stackdepth();
    stacktop();
    char x = myfuncA(msg);
    kprintf("myappaA - after return of myfuncA\n");
    //stackdepth();
    stacktop();
    return (int) x+1;
}
