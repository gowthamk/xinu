/* stackdepth.c - stackdepth */
#include <xinu.h>


/*------------------------------------------------------------------------
 * stackdepth - print a stack depth for a process
 *------------------------------------------------------------------------
 */
syscall stackdepth() {
    int pid = getpid();
    unsigned long *topsp, *topbp; 
	struct procent	*proc = &proctab[pid];
	unsigned long	*sp, *fp;
    int count = 0;
    asm ("movl %%esp, %0"
          :"=r"(topsp)); 
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
        kprintf("Current frame size: %d, Current EBP: 0x%08X\n", 
                    (uint32)fp - (uint32)sp, fp);
        sp = topbp+1;
        fp = (unsigned long *) *fp;
        count++;
	}
    kprintf("Total number of stack frames: %d\n",count);
	return count;
}
