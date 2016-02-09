#include<xinu.h>
#include<stdio.h>

extern int victimglobal;

void victim_sleeper() {
    int x = 1;
    int y = 2;
    int z = x*x*x + y*y;
    kprintf("[Victim %d] about to sleep\n",currpid);
    sleepms(3000);
    kprintf("[Victim %d] woke up from sleep\n",currpid);
}

void myvictim() {
    kprintf("[Victim %d] began execution\n", currpid);
    int x = 1;
    int y = 2;
    int z = x*x + y*y*y;
    victim_sleeper();
    kprintf("[Victim %d] victim_sleeper returned\n", currpid);
    kprintf("[Victim %d] exiting\n", currpid);
    return;
}
