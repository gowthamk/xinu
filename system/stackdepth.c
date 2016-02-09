/* stackdepth.c - stackdepth */
#include <xinu.h>


/*------------------------------------------------------------------------
 * stackdepth - print a stack depth for a process
 *------------------------------------------------------------------------
 */
syscall stackdepth() {
    int pid = getpid();
    unsigned long *topbp; 
	struct procent	*proc = &proctab[pid];
	unsigned long	*sp, *fp;
    int count = 0;
    asm ("movl %%ebp, %0"
          :"=r"(topbp)); 
		sp = topbp + 1;
		fp = (unsigned long*) *topbp;
	while (fp < (unsigned long *)proc->prstkbase) {
        if ((unsigned long*) *fp <= fp) {
			kprintf("bad stack, caller's fp (%08X) \
                    <= calle's fp (%08X)\n", *fp, fp);
			return SYSERR;
		}
        kprintf("[Pid %d] Current frame size: %d, Current EBP: 0x%08X\n", 
                    currpid, (uint32)fp - (uint32)sp, fp);
        sp = topbp+1;
        fp = (unsigned long *) *fp;
        count++;
	}
    kprintf("[Pid %d] Total number of stack frames: %d\n",currpid, count);
	return count;
}
