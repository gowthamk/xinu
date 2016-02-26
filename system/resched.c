/* resched.c - resched, resched_cntl */

#include <xinu.h>
extern int32 lab2flag;
struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

    /* Update time counters for the old process */
    ptold->prcpumsec += clktimemsec - ptold->prctxswintime;
    ptold->prctxswintime = clktimemsec;

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
	
        if (lab2flag == 4) {/* CPUTIME-BASED SCHEDULING */
            /* If old process's prcpumsec is less than that of head 
             * process in the readylist, old proces continues running. */
            if (ptold->prcpumsec < priority_to_prcpumsec(firstkey(readylist))) {
                return;
            }
        } else {/* DEFAULT SCHEDULING */ 
            if (ptold->prprio > firstkey(readylist)) {
                return;
            }
        }

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
        uint32 ptold_prio = (lab2flag == 4)?
                  (prcpumsec_to_priority(ptold->prcpumsec))
                : (ptold->prprio);
		insert(currpid, readylist, ptold_prio);
	}

	/* Force context switch to highest priority ready process */
    
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/

    /* Increase swap count for old process */
    ptold->prctxswcount += 1;
    /* Set the swap-in time for the new process */
    ptnew->prctxswintime = clktimemsec;

    /* Perform the context switch */
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
