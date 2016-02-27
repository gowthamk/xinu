#include<xinu.h>
extern int printflag;
void iobound(int n, int loop1, int loop2, int t, uint32 (*prio_fn)(pid32)) {
    int i,j; 
    pid32 my_pid = getpid();
    for (i=0; i<loop1; i++) {
      for (j=0; j<loop2; j++) {
        sleepms(t);
      }
      // Using kprintf print the pid followed the outer loop count i,
      // the process's priority and remaining time slice (preempt).
      if (printflag) {
          kprintf("[Pid %d (iobound)] iter: %d. Priority: %d. Remaining quantum: %d\n"
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
    sleepms(30*n);
    kprintf("\n[Pid %d (iobound)] FINISHED. swapped out %d times. (CPU time/total time)"
            "= (%dms/%dms).\n", my_pid, sw_times, run_time, elapsed_time);
}
