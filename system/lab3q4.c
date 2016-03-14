#include <xinu.h>

void sender(pid32 recvpid, int maxwait) {
    umsg32 msg = (umsg32) currpid;
    kprintf("[Pid %d @ t=%d] Attempting to send my pid.\n",currpid,clkmsec);
    int32 status = sendbt(recvpid, msg, maxwait);
    if (status == SYSERR) {
        kprintf("[Pid %d] Send did not succeed!\n",currpid);
    } else if (status == TIMEOUT) {
        kprintf("[Pid %d @ t=%d] Send timed out!\n",currpid,clkmsec);
    } else {
        kprintf("[Pid %d @ t=%d] Message sent succesfully.\n",currpid,clkmsec);
    }
    return;
}

void receiver(int delay) {
    while(TRUE) {
        sleepms(delay);
        kprintf("[Pid %d @ t=%d] Attempting receive\n",currpid,clkmsec);
        umsg32 msg = receive();
        kprintf("[Pid %d @ t=%d] Received %d\n",currpid,clkmsec,msg);
    }
}
void lab3q4t1(void) {
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB3Q4T1: 4 blocking senders and 1 receiver (with delay = 1500ms)\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 1500);
    int i;
    for(i=0; i<4; i++) {
        resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 0));
        if (i<3) {
            sleepms(20);
        }
    }
    resume(receiver_pid);
    sleep(8);
    kill(receiver_pid);
    kprintf("LAB3Q4T1: Ending\n");
    return;
}
void lab3q4t2(void) {
    kprintf("------------------------------------------------------------------------\n");
    kprintf("LAB3Q4T2: 4 Non-blocking senders (timeout=200ms) and 1 receiver (delay = 1500ms)\n");
    kprintf("------------------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 1500);
    int i;
    for(i=0; i<4; i++) {
        resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 200));
        if (i<3) {
            sleepms(20);
        }
    }
    resume(receiver_pid);
    sleep(8);
    kill(receiver_pid);
    kprintf("LAB3Q4T2: Ending\n");
    return;
}
void lab3q4t3(void) {
    kprintf("------------------------------------------------------------------------\n");
    kprintf("LAB3Q4T2: 4 Non-blocking senders (timeout=300ms) and 1 receiver (delay = 20ms)\n");
    kprintf("------------------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 20);
    int i;
    for(i=0; i<4; i++) {
        resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 300));
        if (i<3) {
            sleepms(20);
        }
    }
    resume(receiver_pid);
    sleep(2);
    kill(receiver_pid);
    kprintf("LAB3Q4T3: Ending\n");
    return;
}
void lab3q4t4(void) {
    kprintf("------------------------------------------------------------------------\n");
    kprintf("LAB3Q4T2: 2/3 Blocking/Non-blocking senders (timeout=200ms) and 1 receiver (delay = 200ms)\n");
    kprintf("------------------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 200);
    resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 0));
    sleepms(20);
    resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 0));
    sleepms(20);
    resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 200));
    sleepms(20);
    resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 200));
    sleepms(20);
    resume(create(sender, 1024, 20, "sender", 2, receiver_pid, 200));
    resume(receiver_pid);
    sleep(2);
    kill(receiver_pid);
    kprintf("LAB3Q4T4: Ending\n");
    return;
}
/*
void lab3q4(void) {
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
}
*/
