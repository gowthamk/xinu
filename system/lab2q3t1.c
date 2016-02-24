#include<xinu.h>
void slow_add() {
    pid32 my_pid = getpid();
    int i;
    for(i=0;i<99999999;i++);
    for(i=0;i<99999999;i++);
    for(i=0;i<9999999;i++);
    uint32 run_time = proctab[my_pid].prcpumsec;
    kprintf("[Pid %d] Total CPU time is %dms\n",
            my_pid, run_time);
}

void lab2q3t1() {
    int i;
    for(i=0; i<4;i++) {
	    resume(create(slow_add, 2048, 20, "slow_add", 0));
    }
    /* Sleeping for concurrency to end */
    sleep(2);
    return;
}
