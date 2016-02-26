#include<xinu.h>
#define LOOP1 5
#define LOOP2 90000
void cpubound(int n) {
    char str[2][40], *msg = "----- CS503 Xinu Lab3 -----\n";
    strncpy(str[0],msg,strnlen(msg,100));
    int i,j,x=1,y=0; 
    pid32 my_pid = getpid();
    pri16 my_prio = proctab[my_pid].prprio;
    for (i=0; i<LOOP1; i++) {
      for (j=0; j<LOOP2; j++) {
        strncpy(str[x],str[y],strnlen(msg,100));
        x = (x+1)%2; y = (y+1)%2;
      }
      // Using kprintf print the pid followed the outer loop count i,
      // the process's priority and remaining time slice (preempt).
      kprintf("[Pid %d] i: %d. Priority: %d. Remaining quantum: %d\n"
            , my_pid, (i+1)
            , my_prio
            , QUANTUM - (clktimemsec - proctab[my_pid].prctxswintime));
    }
    // Print the CPU time consumed by the process that is recorded in the
    // prcpumsec field of the current process's process table entry.

    uint32 run_time = proctab[my_pid].prcpumsec;
    uint32 sw_times = proctab[my_pid].prctxswcount;
    sleepms(100*n);
    kprintf("[Pid %d] FINISHED. swapped out %d times. Total CPU time is %dms\n",
            my_pid, sw_times, run_time);
}

void lab2q4t1() {
    int i;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q4T1: 6 cpu-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
	    resume(create(cpubound, 2048, 1, "cpubound", 1, i));
    }
    /* Sleeping for concurrency to end */
    sleep(7);
    kprintf("LAB2Q4T1: Ending\n");
    return;
}
