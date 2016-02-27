/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void lab2q3t1(void);
extern void lab2q3t2(void);
extern void lab2q4t1(void);
extern void lab2q5t1(void);
int victimglobal = 0;

/* The flag used to control the scheduler policy.
 * Acceptable values are:
 *   3: For default xinu scheduling
 *   4: For the scheduling policy in Q.4
 *   5: For the scheduling policy in Q.5
 */
int32 lab2flag = 3;

process	main(void)
{
    /*
    kprintf("****** Main: current scheduling policy is %d *******\n",lab2flag);
    lab2q3t1();
    lab2q3t2();
    */
    /*
     * Setting the scheduling policy to 4. 
     * CAUTION: Make sure that lab2q3 tests finish execution
     */
    lab2flag = 4;
    kprintf("****** Main: current scheduling policy is %d *******\n",lab2flag);
    lab2q4t1();
    /*
    lab2flag = 5;
    kprintf("****** Main: current scheduling policy is %d *******\n",lab2flag);
    lab2q5t1();
    */
	/* Wait for shell to exit and recreate it */
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
