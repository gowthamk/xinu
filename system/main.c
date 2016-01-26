/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
extern int app1(void);
extern int app2(void);

process	main(void)
{
    /* An new application process */
    resume(create(app1, 65536, 20, "app1", 0));
    /* Another new application process */
    resume(create(app2, 65536, 20, "app2", 0));
    /* Sleeping for concurrency to end */
    sleep(6);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
