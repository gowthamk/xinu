#include<xinu.h>
extern int printflag;
void iobound(int n, int loop1, int loop2, int t, uint32 (*prio_fn)(pid32)) {
    int i,j; 
    pid32 my_pid = getpid();
    for (i=0; i<loop1; i++) {
      for (j=0; j<loop2; j++) {
        sleepms(t);
      }
    }
}
