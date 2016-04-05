/* alarmms.c - alarmms */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  alarmms  -  Set an alarm for the calling process to be raised in n milliseconds
 *------------------------------------------------------------------------
 */
syscall	alarmms(
	  uint32	delay		/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();
    
    struct procent* p = &proctab[currpid];
    p->alarmset = TRUE;
    p->alarmms = delay;
    alarmq = insertdq(alarmq,p);

	restore(mask);
	return OK;
}
