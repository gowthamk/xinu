/* registercb.c - register a callback function for receive */

#include<xinu.h>

syscall registercb(int (* cb)(void *)) {
    struct procent* p = &proctab[currpid];
    p->recvcb = cb;
    return OK;
}

