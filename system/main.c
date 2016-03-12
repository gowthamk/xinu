/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include<gpqueue.h>

struct gpqueue gpq;
extern void test_gpqueue(void);
process	main(void)
{
    test_gpqueue();
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
