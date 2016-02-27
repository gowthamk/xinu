#include<xinu.h>
extern void cpubound(int, int, int, uint32 (*prio_fn)(pid32));
extern uint32 normalized_priority(uint32,uint32);

uint32 q5_prio_fn(pid32 pid) {
    uint32 begin_time = proctab[pid].prbegintime;
    uint32 cpu_time = proctab[pid].prcpumsec;
    return normalized_priority(begin_time,cpu_time);
}
void lab2q5t1() {
    int i;
    int sleep_times[6] = {100, 500, 50, 2000, 100, 0};
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q5T1: 6 cpu-bound processes beginning at different times\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
        kprintf("lab2q5t1 creating new process \n");
	    resume(create(cpubound, 2048, 1, "cpubound", 3
                        , i, 20, 90000, &q5_prio_fn));
        sleepms(sleep_times[i]);
        kprintf("lab2q5t1 wokeup \n");
    }
    /* Sleeping for concurrency to end */
    sleep(20);
    kprintf("LAB2Q5T1: Ending\n");
    return;
}
