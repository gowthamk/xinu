#include <xinu.h>
#include <stdio.h>

void stacktop() {
	unsigned long *my_bp, *my_sp;
    asm ("movl %%ebp, %0"
          :"=r"(my_bp)); 
    asm ("movl %%esp, %0"
          :"=r"(my_sp)); 
    kprintf("stack top : 0x%08X (0x%08X)\n",
                            *my_sp,my_sp);
    kprintf("stack base : 0x%08X (0x%08X)\n",
                            *my_bp,my_bp);
    return;
}
