#include<xinu.h>
void print_pid(pid32 pid) {
    kprintf("%d",pid);
}
void test_gpqueue(struct gpqueue* gpq) {
    int i;
    kprintf("NPROC is %d. gpg.size = %d\n",NPROC,gpq->size);
    kprintf("Testing GP Queue\n");
    for(i=1;i<=NPROC;i++) {
        enqueueg(gpq,(void*)i);
    }
    kprintf("After NPROC enqueues, queue is: ");
    printgq(gpq,(void (*)(void *))&print_pid);
    kprintf("The results of 4 dequeues are: ");
    for(i=1;i<=4;i++) {
        kprintf("%d ",(int)dequeueg(gpq));
    }
    kprintf("\n");
    for(i=1;i<=4;i++) {
        enqueueg(gpq,(void*)(NPROC+i));
    }
    kprintf("After 4 more enqueues, queue is: ");
    printgq(gpq,(void (*)(void *))&print_pid);
    return;
}
