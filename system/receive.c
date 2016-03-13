/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
void unblock_a_sender(void) {
    struct procent *prptr = &proctab[currpid];
    if(!is_emptyg(prptr->senderwaitq)) {
        pid32 sender = (pid32) dequeueg(prptr->senderwaitq);
        struct procent *sendprptr = &proctab[sender];
        if (sendprptr->prstate == PR_SEND) {
            /* If the sender is blocked on send call, make it ready */
            ready(sender);
        }
    }
    return;
}
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
    /* Following was added for lab3 */
    unblock_a_sender();
	restore(mask);
	return msg;
}
