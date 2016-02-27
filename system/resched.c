/* resched.c - resched, resched_cntl */

#include <xinu.h>
extern int32 lab2flag;
struct	defer	Defer;


/*
 * @param begin_time is the creation timestamp (msecs) of the process.
 * @param cpu_time is the cpu time (msecs) that this process recieved.
 * @return normalized_priority of this process, defined as:
 *
 *     normalized_priority = max_priority(1 - cpu_time/elapsed_time)
 *
 *  where elapsed_time is the time elapsed since the begin_time.
 */
uint32 normalized_priority(uint32 begin_time, uint32 cpu_time) {
    /*
     * If cpu_time receieved by this process is zero, then the
     * process gets max priority.
     */
    if (cpu_time == 0) {
        return max_priority;
    }
    uint32 elapsed_time = clktimemsec - begin_time;
    /*
     * elapsed_time cannot be zero since cpu_time is not zero.
     */
    debug_print("[Pid %d] cpu_time = %d. elapsed_time=%d\n",currpid
            , cpu_time, elapsed_time);
    uint32 offset = (max_priority/elapsed_time) * (cpu_time);
    debug_print("[Pid %d] max_priority is %d. offset is %d\n"
                , currpid, max_priority, offset);
    uint32 normalized_priority = max_priority - offset;
    debug_print("[Pid %d] normalized prio is %d\n",currpid, normalized_priority);
    /*
     * If normalized_priority is less than min_priority, we return 
     * min_priority instead.
     */
    if(normalized_priority < min_priority) {
        debug_print("[Pid %d] returning min_priority %d\n",currpid, min_priority);
        return min_priority;
    }
    return normalized_priority;
}

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
    uint32 ptold_normalized_prio = min_priority; /* For lab2Q5. */

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
        } else if (lab2flag == 5) {/* NORMALIZED SCHEDULING */
            /* Old process normalized priority */
            ptold_normalized_prio = normalized_priority(ptold->prbegintime
                                                       , ptold->prcpumsec);

            debug_print("[Pid %d @ %d msec] normalized_priority(%d,%d)=%d\n"
                    , currpid, clktimemsec, ptold->prbegintime
                    , ptold->prcpumsec, ptold_normalized_prio);
            if (ptold_normalized_prio > firstkey(readylist)) {
                return;
            }
        } else {/* DEFAULT SCHEDULING */ 
            if (ptold->prprio > firstkey(readylist)) {
                return;
            }
        }

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
        uint32 ptold_prio;
        if (lab2flag == 4) {
            if (currpid!=0) {
                ptold_prio = prcpumsec_to_priority(ptold->prcpumsec);
            } else {
                //ptold_prio = min_priority;
                ptold_prio = prcpumsec_to_priority(ptold->prcpumsec);
            }
        } else if (lab2flag == 5) {
            ptold_prio = ptold_normalized_prio;
            //kprintf("[Pid %d] Swapping. New normalized priority: %d\n"
            //            , currpid, ptold_prio);
        } else {
            ptold_prio = ptold->prprio;
        }
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
