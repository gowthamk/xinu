/* ready.c - ready */

#include <xinu.h>

//qid16	readylist;			/* Index of ready list		*/
struct mlfbq *readylist;     /* ready list is now mlfbq for TS scheduling */

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
	mlfbq_insert(pid, readylist);
	resched();

	return OK;
}
