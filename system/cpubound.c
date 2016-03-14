#include<xinu.h>
int printflag = 1;
void cpubound(int n, int loop1, int loop2, uint32 (*prio_fn)(pid32)) {
    char str[2][40], *msg = "----- CS503 Xinu Lab3 -----\n";
    strncpy(str[0],msg,strnlen(msg,100));
    int i,j,x=1,y=0; 
    struct procent* p = &proctab[currpid];
    for (i=0; i<loop1; i++) {
      for (j=0; j<loop2; j++) {
        strncpy(str[x],str[y],strnlen(msg,100));
        x = (x+1)%2; y = (y+1)%2;
      }
      if (printflag) {
          kprintf("[Pid %d (cpubound)] iter: %d. TS Priority: %d. TS Quantum: %d\n"
                , currpid, (i+1)
                , p->tsprio
                , p->tsquantum);
      } else {
          kprintf(".");  
      }
    }
    // Print the CPU time consumed by the process that is recorded in the
    // cpumsec field of the current process's process table entry.

    uint32 run_time = proctab[currpid].cpumsec;
    uint32 elapsed_time = clkmsec - proctab[currpid].begunat;
    sleepms(20*n);
    kprintf("\n[Pid %d (cpubound)] FINISHED. (CPU time/total time)"
            "= (%dms/%dms).\n", currpid, run_time, elapsed_time);
}


