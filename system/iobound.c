#include<xinu.h>
extern int printflag;
void iobound(int n, int loop1, int loop2, int t, uint32 (*prio_fn)(pid32)) {
    int i,j; 
    struct procent* p = &proctab[currpid];
    for (i=0; i<loop1; i++) {
      for (j=0; j<loop2; j++) {
        sleepms(t);
      }
      if (printflag) {
          kprintf("[Pid %d (iobound)] iter: %d. TS Priority: %d. TS Quantum: %d\n"
                , currpid, (i+1)
                , p->tsprio
                , p->tsquantum);
      } else {
          kprintf(".");
      }
    }
}
