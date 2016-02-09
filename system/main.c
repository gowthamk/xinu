/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
extern int app1(void);
extern int app2(void);
extern long host2netlb(long);
extern long host2netlc(long);
extern void prntsegaddr(void);
extern syscall stackdepth(void);
extern int stacktop(void);
extern int myappA(char*);
extern void myvictim(void);
extern void myhacker(int);

int victimglobal = 0;

process	main(void)
{
    /* An new application process */
    resume(create(app1, 65536, 20, "app1", 0));
    /* Another new application process */
    //resume(create(app2, 65536, 20, "app2", 0));
    /* Sleeping for concurrency to end */
    sleep(1);
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */
    long arg = 0x12345678;
    long resa = host2netlb(arg);
    long resb = host2netlc(arg);
    kprintf("host2netlb(%x) = %x\n",arg,resa);
    kprintf("host2netlc(%x) = %x\n",arg,resb);
    prntsegaddr();
    stackdepth();

    /* myappA */
    int appa_pid;
    char *msg = "Greetings from main";
    char *name = "myappA";
    kprintf("\n--- Inside main. Before creating myappA. ----\n");
    stacktop();
    appa_pid = create(myappA, 1024, 20, name, 1, msg);
    kprintf(" --- Inside main. After creating myappA. ----\n");
    stacktop();
    resume(appa_pid);
    /* Sleeping for concurrency to end */
    sleep(1);

    /* Stack Smashing */
    kprintf("******** STACK SMASHING ********\n");
    int victim_pid = create(myvictim, 2048, 20, "victim", 0);
    resume(victim_pid);
    resume(create(myhacker, 2048, 20, "hacker", 1, victim_pid));
    /* Sleeping for concurrency to end */
    sleep(4);
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
