/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
extern void sender(pid32,int);
extern void receiver(void);
extern void lab3q3t1(void);
extern void lab3q3t2(void);
extern void lab3q3t3(void);
extern void test_gpqueue(struct gpqueue*);
process	main(void)
{
    /*struct gpqueue* gpq = (struct gpqueue*)getstk(sizeof(struct gpqueue));
    gpq->size = gpq->head = gpq->tail = 0;
    test_gpqueue(gpq);*/
    /*
    kprintf("Main creating a receiver and three senders...\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 0);
    sleepms(100);
    resume(create(sender, 1024, 20, "sender1", 2, receiver_pid, 0));
    sleepms(100);
    resume(create(sender, 1024, 20, "sender2", 2, receiver_pid, 100));
    sleepms(100);
    resume(create(sender, 1024, 20, "sender3", 2, receiver_pid, 0));
    resume(receiver_pid);
    sleep(8);
    */
    kprintf("*** Main running lab3q3t1 testcase\n");
    lab3q3t1();
    kprintf("*** Main running lab3q3t2 testcase\n");
    lab3q3t2();
    kprintf("*** Main running lab3q3t3 testcase\n");
    lab3q3t3();
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
