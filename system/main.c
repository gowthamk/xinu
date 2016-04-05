/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
extern void lab4q2t1(void);
extern void lab4q2t2(void);
extern void lab4q3t1(void);
extern void lab4q3t2(void);
extern void lab4q3t3(void);
process	main(void)
{
    /*
    kprintf("*** Main running lab3q3t1 testcase\n");
    lab3q3t1();
    kprintf("*** Main running lab3q3t2 testcase\n");
    lab3q3t2();
    kprintf("*** Main running lab3q3t3 testcase\n");
    lab3q3t3();
    kprintf("*** Main running lab3q3t4 testcase\n");
    lab3q3t4();

    lab3q4t1();
    lab3q4t2();
    lab3q4t3();
    lab3q4t4();
    */

    lab4q3t1();
    lab4q3t2();
    lab4q3t3();
    sleep(4);
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
