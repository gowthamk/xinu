#include<xinu.h>
extern void cpubound(int, int, int, uint32 (*prio_fn)(pid32));
void slow_add(int n, int loop1, int loop2) {
    pid32 my_pid = getpid();
    int i;
    for(i=0;i<loop1;i++);
    for(i=0;i<loop2;i++);
    uint32 run_time = proctab[my_pid].prcpumsec;
    uint32 sw_times = proctab[my_pid].prctxswcount;
    pri16 prio = proctab[my_pid].prprio;
    sleepms(100*n);
    kprintf("[Pid %d] Priority: %d. Swapped out %d times. Total CPU time is %dms\n",
            my_pid, prio, sw_times, run_time);
}
uint32 q3_prio_fn(pid32 pid) {
    return proctab[pid].prprio;
}
void lab2q3t1() {
    int i;
    kprintf("--------------------------------------------------\n");
    kprintf("LAB2Q3T1: 4 cpu-bound processes with same priority\n");
    kprintf("--------------------------------------------------\n");
    for(i=0; i<4;i++) {
	    //resume(create(slow_add, 2048, 20, "slow_add", 3, i, 9999999, 9999999));
	    resume(create(cpubound, 2048, 20, "cpubound", 4, i, 5, 90000, &q3_prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(4);
    kprintf("LAB2Q3T1: Ending\n");
    return;
}
void lab2q3t2() {
    int i;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q3T2: 4 cpu-bound processes with different priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<4;i++) {
	    //resume(create(slow_add, 2048, 20*(i+1), "slow_add", 3, i, 99999999, 9999999));
	    resume(create(cpubound, 2048, 20*(i+1), "cpubound", 4, i, 5, 99999, &q3_prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(7);
    kprintf("LAB2Q3T1: Ending\n");
    return;
}
