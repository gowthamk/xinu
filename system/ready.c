/* ready.c - ready */

#include <xinu.h>

extern int32 lab2flag;
qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
    int32 init_prio = /* The new process hasn't run. Its prcpumsec is zero. */
                      (lab2flag == 4)? (prcpumsec_to_priority(0)): (prptr->prprio);
    //kprintf("PID %d is ready\n",pid);
	insert(pid, readylist, init_prio);
	resched();

	return OK;
}
