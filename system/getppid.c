#include <xinu.h>

/*------------------------------------------------------------------------
 *  getppid  -  Return the ID of the currently process's parent
 *------------------------------------------------------------------------
 */

pid32 getppid() {
    struct procent my_procent = proctab[currpid];
    return my_procent.prparent;
}
