/* ready.c - ready */

#include <xinu.h>

extern int32 lab2flag;
extern uint32 normalized_priority(uint32,uint32);
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
    /* Set the begin timestamp */
    prptr->prbegintime = clktimemsec;
    int32 init_prio;
    if (lab2flag == 4) {
        if (currpid!=0) {
            /* The new process hasn't run. Its prcpumsec is zero. */
            init_prio = prcpumsec_to_priority(0);
        } else {
            //init_prio = min_priority;
            init_prio = prcpumsec_to_priority(0);
        } 
    } else if (lab2flag == 5) {
        init_prio = normalized_priority(prptr->prbegintime,0);
        debug_print("[Pid %d] initial normalized priority: %d\n",pid,init_prio);
    } else {
        init_prio = prptr->prprio;
    }
	insert(pid, readylist, init_prio);
	resched();

	return OK;
}
