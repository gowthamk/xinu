/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

void ts_update() {
    struct procent *p = &proctab[currpid];
    int old_ts_prio, new_ts_prio, new_ts_quantum;
    old_ts_prio = p->tsprio;
    new_ts_quantum = tsdtab[old_ts_prio].ts_quantum;
    if (currpid == 0) {
        /* null process always runs at min priority */
        new_ts_prio = 0;
        new_ts_quantum = 2;
    } else if (p->prstate == PR_CURR) {
        debug_print("[Pid %d] is cpu-intensive\n", currpid);
        new_ts_prio = tsdtab[old_ts_prio].ts_tqexp;
    } else if (p->prstate == PR_FREE){
        debug_print("[Pid %d] is finishing!\n", currpid);
        new_ts_prio = TS_INIT_PRIO;
    } else if (p->prstate == PR_READY){
        panic("Currently running process cannot be in ready queue!\n");
        return;
    } else {
        debug_print("[Pid %d] is io-intensive(%d)\n", currpid, p->prstate);
        new_ts_prio = tsdtab[old_ts_prio].ts_slpret;
    }
    debug_print("[Pid %d] New priority is %d, and quantum is %d\n"
            , currpid, new_ts_prio, new_ts_quantum);
    /* Update p's proctab entry */
    p->tsprio = new_ts_prio;
    p->tsquantum = new_ts_quantum;
    return;
}

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
    ptold->cpumsec += clkmsec - ptold->ctxswintime;
    ptold->ctxswintime = clkmsec;

    /* Update TS metrics for the current process */
    ts_update();

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
        /* Note: mlfbq_firstkey may return SYSERR, which is < 0 */
		if (currpid!=0 && ptold->tsprio > mlfbq_firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		mlfbq_insert(currpid, readylist);
	}

	/* Force context switch to highest priority ready process */

	currpid = mlfbq_dequeue(readylist);
    if (currpid == 0 && !mlfbq_is_empty(readylist)) {
        /* we reinsert null process at the end of the queue */
        mlfbq_insert(currpid,readylist);
        currpid = mlfbq_dequeue(readylist);
    }
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = ptnew->tsquantum; //QUANTUM;		/* Reset time slice for process	*/
    ptnew->ctxswintime = clkmsec; /* Set the swap-in time for the new process */
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
