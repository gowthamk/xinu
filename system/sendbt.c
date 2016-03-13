/* sendbt.c - time-bound blocking send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendbt  -  Pass a message to a process and start recipient if waiting
 *             Block until maxwait, if recipient prhasmsg is TRUE.
 *------------------------------------------------------------------------
 */
syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,		/* Contents of message		*/
      int32     maxwait     /* Time(msecs) to block */
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *recvprptr;		/* Ptr to process' table entry	*/

	if (maxwait < 0) {
		return SYSERR;
	}

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

    struct procent *sendprptr = &proctab[currpid];
    /* Sender has a valid message to send */
    sendprptr->sndmsg = msg;
    sendprptr->sndflag = TRUE;
	recvprptr = &proctab[pid];
    /* If the receiver already has a message.. */
	if ((recvprptr->prstate == PR_FREE) || recvprptr->prhasmsg) {
        if(maxwait >0) { //.. and sender specified a timeout
            /* insert sender into sleep queue */
            if (insertd(currpid,sleepq,maxwait) == SYSERR) {
                restore(mask);
                return SYSERR;
            }
            /* Set its state to PR_SENTIM */
            sendprptr->prstate = PR_SENTIM;
        } else {
            /* Set its state to PR_SEND */
            sendprptr->prstate = PR_SEND;
        }
        /* In any case, add it to recipient's sender wait queue */
        enqueueg(recvprptr->senderwaitq,(void*)currpid);
        resched();
        /* Control comes back here if either receiver makes this 
         * process ready or the maxwait timer expired. If it is the 
         * latter, then recipient's prhasmsg is still TRUE. */
        if (recvprptr->prhasmsg) {
            /* If prhasmsg is TRUE, send returns. */
            /* Note: did not dequeue from senderwaitq. Handle in receive. */
            restore(mask);
            return TIMEOUT;
        }
	}
	recvprptr->prmsg = msg;		/* Deliver message		*/
	recvprptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/
    sendprptr->sndflag = FALSE; /* Sender no longer has a valid message */

	/* If recipient waiting or in timed-wait make it ready */

	if (recvprptr->prstate == PR_RECV) {
		ready(pid);
	} else if (recvprptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
