/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}
    clkmsec++;
    /* Incrementing prcpumsec of the current process */
    struct procent* p = &proctab[currpid];
    p->cpumsec++;
    /* If the current processes requested MYSIGXCPU service, then call the
     * signal handler. */
    if (p->sighandlers[sigToIndex(MYSIGXCPU)] != NULL && 
                    !p->prdidtime && p->cpumsec >= MYSIGXCPUTIME) {
        p->prdidtime=TRUE;
        (p->sighandlers[sigToIndex(MYSIGXCPU)])(NULL);
    }
    /* Alarms */
    if (alarmq != NULL) {
        struct procent* p = alarmq->procent;
        p->alarmms--;
        if (p->alarmms <= 0) {
            alarmq = dequeuedq(alarmq);
        }
    }

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
        /* If this process remains eligible AND its tsquantum is not
         * updated in resched (shouldn't be the case) then the following
         * setting will use the exisiting tsquantum value. */
		preempt = proctab[currpid].tsquantum;//QUANTUM;
		resched();
	}
}
