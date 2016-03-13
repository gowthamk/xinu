/* sendbt.c - time-bound blocking send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendbt  -  Pass a message to a process and start recipient if waiting
 *             Block until timeout, if recipient prhasmsg is TRUE.
 *------------------------------------------------------------------------
 */
syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,		/* Contents of message		*/
      int32     timeout     /* Time(msecs) to block */
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *recvprptr;		/* Ptr to process' table entry	*/

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
	if ((recvprptr->prstate == PR_FREE) || recvprptr->prhasmsg) {
        /* If the receiver already has a message.. */
        sendprptr->prstate = PR_SEND;
        /* Add sender to recipient's sender wait queue */
        enqueueg(recvprptr->senderwaitq,(void*)currpid);
        resched();
        /* Control comes here iff receiver makes this process ready */
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
