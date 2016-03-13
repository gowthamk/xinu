#include<xinu.h>

struct mlfbq* mlfbq_new() {
    int i;
    char* mem = getmem(sizeof(struct mlfbq));
    if ((int32)mem == SYSERR) {
        panic("Could not allocate space for fbq!");
        return (struct mlfbq*)SYSERR;
    }
    for (i=0;i<sizeof(struct mlfbq); i++) {
        mem[i] = 0;
    }
    return (struct mlfbq*)mem;
}

status	mlfbq_insert(
        pid32	pid,		/* ID of the process to insert	*/
        struct mlfbq* fbq   /* Multi-level queue to insert into */
	) 
{
    struct procent* p = &proctab[pid];
    int tsprio = p->tsprio;
    struct gpqueue* gpq = &fbq->queues[tsprio];
    if (enqueueg(gpq,(void*)pid) < 0) {
        return SYSERR;
    }
    return OK;
}

int top_nonempty_prio(struct mlfbq* fbq) {
    int i;
    for(i=TS_MAX_PRIO; i>=0; i--) {
        struct gpqueue* gpq = &fbq->queues[i];
        if (!is_emptyg(gpq)) {
            return i;
        }
    }
    return -1;
}

int mlfbq_firstkey(
        struct mlfbq* fbq   /* Multi-level queue whose firstkey is needed. */
    )
{
    int top_prio = top_nonempty_prio(fbq);
    if (top_prio < 0) {
        return SYSERR;
    }
    return top_prio;
}

pid32 mlfbq_dequeue(
        struct mlfbq* fbq   /* Multi-level queue to dequeue from */
    )
{
    int top_prio = top_nonempty_prio(fbq);
    if (top_prio < 0) {
        return SYSERR;
    }
    struct gpqueue* top_gpq = &fbq->queues[top_prio];
    return (pid32) dequeueg(top_gpq);
}
