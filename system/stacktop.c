#include <xinu.h>
#include <stdio.h>

void stacktop() {
    int pid = getpid();
	unsigned long *my_bp, *caller_sp;
    asm ("movl %%ebp, %0"
          :"=r"(my_bp)); 
    caller_sp = my_bp+1;
    kprintf("[Pid %d] Top of the stack[0x%08X] contains 0x%08X.\n",
                    pid,caller_sp,*caller_sp);
    return;
}
