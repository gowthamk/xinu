#include<xinu.h>
#define LOOP1 5
#define LOOP2 9000
extern int printflag;
extern void cpubound(int, int, int, uint32 (*prio_fn)(pid32));
extern void iobound(int, int, int, int, uint32 (*prio_fn)(pid32));
uint32 prio_fn(pid32 pid) {
    return proctab[pid].tsprio;
}
void lab3q3t3() {
    int i;
    printflag = 0;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB3Q3T3: 3/3 cpu/io-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    intmask mask = disable();
    kprintf("LAB3Q3T3(%d): STARTING!\n",currpid);
    cpubound(1,LOOP1, 10*LOOP2, &prio_fn);
    restore(mask);
    for(i=0; i<3;i++) {
	    resume(create(cpubound, 1024, 1, "cpubound", 4
                        , 2*i, LOOP1, LOOP2, &prio_fn));
	    resume(create(iobound, 1024, 1, "iobound", 5
                        , 2*i+1, LOOP1, LOOP2/1000, 3, &prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(7);
    kprintf("LAB3Q3T3: Ending\n");
    printflag = 1;
    return;
}
