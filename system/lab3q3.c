#include<xinu.h>
#define LOOP1 5
#define LOOP2 90000
extern int printflag;
extern void cpubound(int, int, int, uint32 (*prio_fn)(pid32));
extern void iobound(int, int, int, int, uint32 (*prio_fn)(pid32));
uint32 prio_fn(pid32 pid) {
    return proctab[pid].tsprio;
}
void lab3q3t1() {
    int i;
    printflag = 1;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB3Q3T1: 6 cpu-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
	    resume(create(cpubound, 1024, 1, "cpubound", 4
                        , i, LOOP1, LOOP2, &prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(7);
    kprintf("LAB3Q3T1: Ending\n");
    return;
}
void lab3q3t2() {
    int i;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB3Q3T2: 6 io-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
	    resume(create(iobound, 2048, 1, "iobound", 5
                        , i, LOOP1, LOOP2/1000, 3, &prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(5);
    kprintf("LAB3Q3T2: Ending\n");
    return;
}
void lab3q3t3() {
    int i;
    printflag = 0;
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB3Q3T3: 3/3 cpu/io-bound processes with same initial priorities\n");
    kprintf("---------------------------------------------------------\n");
    //intmask mask = disable();
    //kprintf("LAB3Q3T3(%d): STARTING!\n",currpid);
    //restore(mask);
    for(i=0; i<3;i++) {
	    resume(create(cpubound, 1024, 1, "cpubound", 4
                        , 2*i, LOOP1, LOOP2, &prio_fn));
	    resume(create(iobound, 1024, 1, "iobound", 5
                        , 2*i+1, LOOP1, LOOP2/1000, 3, &prio_fn));
    }
    /* Sleeping for concurrency to end */
    sleep(6);
    kprintf("LAB3Q3T3: Ending\n");
    printflag = 1;
    return;
}
void lab3q3t4() {
    int i;
    int sleep_times[6] = {100, 500, 50, 2000, 100, 0};
    kprintf("---------------------------------------------------------\n");
    kprintf("LAB3Q3T4: 6 cpu-bound processes beginning at different times\n");
    kprintf("---------------------------------------------------------\n");
    for(i=0; i<6;i++) {
        kprintf("lab3q3t1 creating new process \n");
	    resume(create(cpubound, 2048, 1, "cpubound", 4
                        , i, 20, 90000, &prio_fn));
        sleepms(sleep_times[i]);
        kprintf("lab3q3t1 wokeup \n");
    }
    /* Sleeping for concurrency to end */
    sleep(20);
    kprintf("LAB3Q3T4: Ending\n");
    return;
}
