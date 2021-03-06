#include<xinu.h>
extern int printflag;
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
      if (printflag) {
          kprintf("[Pid %d (cpubound)] iter: %d. Priority: %d. Remaining quantum: %d\n"
                , my_pid, (i+1)
                , prio_fn(my_pid)
                , QUANTUM - (clktimemsec - proctab[my_pid].prctxswintime));
      } else {
          kprintf(".");  
      }
    }
    // Print the CPU time consumed by the process that is recorded in the
    // prcpumsec field of the current process's process table entry.

    uint32 run_time = proctab[my_pid].prcpumsec;
    uint32 elapsed_time = clktimemsec - proctab[my_pid].prbegintime;
    uint32 sw_times = proctab[my_pid].prctxswcount;
    sleepms(20*n);
    kprintf("\n[Pid %d (cpubound)] FINISHED. swapped out %d times. (CPU time/total time)"
            "= (%dms/%dms).\n", my_pid, sw_times, run_time, elapsed_time);
}


