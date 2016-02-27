#include<xinu.h>
#define LOOP1 5
#define LOOP2 90000
void cpubound(int n, int loop1, int loop2, uint32 (*prio_fn)(pid32)) {
    char str[2][40], *msg = "----- CS503 Xinu Lab3 -----\n";
    strncpy(str[0],msg,strnlen(msg,100));
    int i,j,x=1,y=0; 
    pid32 my_pid = getpid();
    for (i=0; i<loop1; i++) {
      for (j=0; j<loop2; j++) {
        strncpy(str[x],str[y],strnlen(msg,100));
        x = (x+1)%2; y = (y+1)%2;
      }
      // Using kprintf print the pid followed the outer loop count i,
      // the process's priority and remaining time slice (preempt).
      kprintf("[Pid %d] iter: %d. Priority: %d. Remaining quantum: %d\n"
            , my_pid, (i+1)
            , prio_fn(my_pid)
            , QUANTUM - (clktimemsec - proctab[my_pid].prctxswintime));
    }
    // Print the CPU time consumed by the process that is recorded in the
    // prcpumsec field of the current process's process table entry.

    uint32 run_time = proctab[my_pid].prcpumsec;
    uint32 elapsed_time = clktimemsec - proctab[my_pid].prbegintime;
    uint32 sw_times = proctab[my_pid].prctxswcount;
    sleepms(100*n);
    kprintf("[Pid %d] FINISHED. swapped out %d times. (CPU time/total time)"
            "= (%dms/%dms).\n", my_pid, sw_times, run_time, elapsed_time);
}

uint32 q4_prio_fn(pid32 pid) {
    uint32 prcpumsec = proctab[pid].prcpumsec;
    uint32 prio = prcpumsec_to_priority(prcpumsec);
    //kprintf("[Pid %d] prcpumsec: %d. priority: %d\n",pid,prcpumsec,prio);
    return prio;
}

void lab2q4t1() {
    int i;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q4T1: 6 cpu-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
	    resume(create(cpubound, 2048, 1, "cpubound", 4
                        , i, LOOP1, LOOP2, &q4_prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(7);
    kprintf("LAB2Q4T1: Ending\n");
    return;
}
