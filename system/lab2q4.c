#include<xinu.h>
#define LOOP1 5
#define LOOP2 90000
extern int printflag;
extern void cpubound(int, int, int, uint32 (*prio_fn)(pid32));
extern void iobound(int, int, int, int, uint32 (*prio_fn)(pid32));
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

void lab2q4t2() {
    int i;
    printflag = 0;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q4T2: 6 io-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
	    resume(create(iobound, 2048, 1, "iobound", 5
                        , i, LOOP1, LOOP2/1000, 3, &q4_prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(5);
    kprintf("LAB2Q4T2: Ending\n");
    printflag = 1;
    return;
}

void lab2q4t3() {
    int i;
    printflag = 0;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB2Q4T3: 3/3 cpu/io-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<3;i++) {
	    resume(create(cpubound, 2048, 1, "cpubound", 4
                        , 2*i, LOOP1, LOOP2, &q4_prio_fn));
	    resume(create(iobound, 2048, 1, "iobound", 5
                        , 2*i+1, LOOP1, LOOP2/1000, 3, &q4_prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(8);
    kprintf("LAB2Q4T3: Ending\n");
    printflag = 1;
    return;
}
