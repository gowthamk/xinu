#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpstate  -  Return the state of the currently executing process.
 *------------------------------------------------------------------------
 */

uint16 getpstate() {
    uint16 pstate;
    intmask mask;
    /* Disable interrupts */
    mask = disable();

    struct procent my_procent = proctab[currpid];
    pstate = my_procent.prstate;

    /* Re-enable interrupts */
    restore(mask);
    return pstate;
}
