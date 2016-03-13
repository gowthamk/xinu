#include<xinu.h>
int printflag = 0;
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
    }
    // Print the CPU time consumed by the process that is recorded in the
    // prcpumsec field of the current process's process table entry.

    /*
    uint32 run_time = proctab[my_pid].prcpumsec;
    uint32 elapsed_time = clktimemsec - proctab[my_pid].prbegintime;
    uint32 sw_times = proctab[my_pid].prctxswcount;
    sleepms(20*n);
    kprintf("\n[Pid %d (cpubound)] FINISHED. swapped out %d times. (CPU time/total time)"
            "= (%dms/%dms).\n", my_pid, sw_times, run_time, elapsed_time);
    */
}


