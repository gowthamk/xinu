#include<xinu.h>
#include<stdio.h>

extern int victimglobal;
extern unsigned long* plzhackme;

int hacked = 0;

void victim_dummy(unsigned long* caller_ret) {
    unsigned long* my_bp, *my_ret;
    asm ("movl %%ebp, %0"
          :"=r"(my_bp)); 
    my_ret = my_bp+1;
    *my_ret = *caller_ret;
    kprintf("victim_dummy: set my ret to my caller's ret\n");
    return;
}

void victim_sleeper() {
    /*
    int x = 1;
    int y = 2;
    int z = x*x*x + y*y;
    kprintf("%d\n",z);
    */
    unsigned long *my_bp, *caller_sp, *my_ret;
    asm ("movl %%ebp, %0"
          :"=r"(my_bp)); 
    my_ret = my_bp+1;
    hacked = 1;
    victim_dummy(my_ret);
    int x = 1;
    int y = 2;
    int z = x*x*x + y*y;
    /*
    kprintf("[Victim %d] about to sleep\n",currpid);
    //sleepms(3000);
    kprintf("[Victim %d] woke up from sleep\n",currpid);
    */
}

void myvictim() {
    int x = 1;
    int y = 2;
    int z = x*x + y*y*y;
    if(hacked ==0 )
        victim_sleeper();
    kprintf("myvictim function\n");
    return;
}
