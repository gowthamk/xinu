#include <xinu.h>

/*------------------------------------------------------------------------
 *  getppid  -  Return the ID of the currently process's parent
 *------------------------------------------------------------------------
 */

pid32 getppid() {
    pid32 parent_pid;
    intmask mask;
    /* Disable interrupts */
    mask = disable();

    struct procent my_procent = proctab[currpid];
    parent_pid = my_procent.prparent;

    /* Re-enable interrupts */
    restore(mask);
    return parent_pid; 
}
