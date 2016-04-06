#include <xinu.h>
int sent = 0;
void sender(pid32 recvpid) {
    umsg32 msg = (umsg32) currpid;
    kprintf("[Pid %d @ t=%d] Attempting to send my pid.\n",currpid,clkmsec);
    int32 status = send(recvpid, msg);
    if (status == SYSERR) {
        kprintf("[Pid %d] Send did not succeed!\n",currpid);
    } else if (status == TIMEOUT) {
        kprintf("[Pid %d @ t=%d] Send timed out!\n",currpid,clkmsec);
    } else {
        kprintf("[Pid %d @ t=%d] Message sent succesfully.\n",currpid,clkmsec);
    }
    return;
}
int recvcb(void *ptr) {
    kprintf("[Pid %d @ t=%d] Receive callback has been called.\n", currpid, clkmsec);
    umsg32 msg = receive();
    kprintf("[Pid %d @ t=%d] Received %d\n",currpid,clkmsec,msg);
    sent++;
    return OK;
}
void receiver(int numSenders) {
    int i;
    kprintf("[Pid %d @ t=%d] Receive process. Registering a callback.\n"
                , currpid, clkmsec);
    registercb(&recvcb);
    while(TRUE) {
        for(i=0; i<99999999; i++);
        kprintf("[Pid %d @ t=%d] Receiver Running.\n", currpid, clkmsec);
        if (sent == numSenders) {
            kprintf("[Pid %d @ t=%d] Receiver Exiting.\n", currpid, clkmsec);
            return;
        }
    }
    return;
}
void receiver_io(int numSenders) {
    kprintf("[Pid %d @ t=%d] Receive process. Registering a callback.\n"
                , currpid, clkmsec);
    registercb(&recvcb);
    while(TRUE) {
        kprintf("[Pid %d @ t=%d] Receiver about to sleep.\n", currpid, clkmsec);
        sleepms(750);
        kprintf("[Pid %d @ t=%d] Receiver wokeup.\n", currpid, clkmsec);
        if (sent == numSenders) {
            kprintf("[Pid %d @ t=%d] Receiver Exiting.\n", currpid, clkmsec);
            return;
        }
    }
    return;
}
void lab4q2t1(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q2T1: 1 sender and 1 cpubound receiver\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 1);
    resume(receiver_pid);
    sleep(1);
    resume(create(sender, 1024, 20, "sender", 1, receiver_pid));
    sleep(1);
    kprintf("LAB4Q2T1: Ending\n");
    return;
}
void lab4q2t2(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q2T2: 2 concurrent senders and 1 cpubound receiver\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 2);
    resume(receiver_pid);
    sleep(1);
    resume(create(sender, 1024, 20, "sender1", 1, receiver_pid));
    sleepms(100);
    resume(create(sender, 1024, 20, "sender2", 1, receiver_pid));
    sleep(1);
    kprintf("LAB4Q2T2: Ending\n");
    return;
}
void lab4q2t3(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q2T3: 2 concurrent senders and 1 iobound receiver\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver_io, 1024, 20, "receiver", 1, 2);
    resume(receiver_pid);
    sleep(2);
    resume(create(sender, 1024, 20, "sender1", 1, receiver_pid));
    sleep(1);
    resume(create(sender, 1024, 20, "sender2", 1, receiver_pid));
    sleep(2);
    kprintf("LAB4Q2T3: Ending\n");
    return;
}
