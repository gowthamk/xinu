/* registercb.c - register a callback function for receive */

#include<xinu.h>

syscall registercb(int (* cb)(void *)) {
	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();

    struct procent* p = &proctab[currpid];
    p->recvcb = cb;

	restore(mask);		/* Restore interrupts */
    return OK;
}

