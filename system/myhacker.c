#include<xinu.h>
#include<stdio.h>

extern int victimglobal;
extern unsigned long* plzhackme;

void myhackermalware(int x) {
    victimglobal = 1;
    kprintf("victimglobal is %d\n",victimglobal);
    return;
}

void myhacker(int victim_pid) {
	//*plzhackme = (unsigned long) myhackermalware;
    return;
}
