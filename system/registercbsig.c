/* registercbsig.c - register a callback function as a signal handler */

#include<xinu.h>

syscall registercbsig(uint16 asig, int (* cb) (void *), uint32 optarg) {

    if (!isValidSig(asig)) {
        return SYSERR;
    }

	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();
    
    struct procent* p = &proctab[currpid];
    (p->sighandlers)[sigToIndex(asig)] = cb;

	restore(mask);		/* Restore interrupts */
    return OK;
}
