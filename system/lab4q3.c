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
        kprintf("[Pid %d @ t=%d] Send succeeeded.\n",currpid,clkmsec);
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
    registercbsig(MYSIGRECV,&recvcb,0);
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
void lab4q3t1(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q3T1: 1 sender and 1 receiver\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 1);
    resume(receiver_pid);
    sleep(2);
    resume(create(sender, 1024, 20, "sender", 1, receiver_pid));
    sleep(2);
    kprintf("LAB4Q3T1: Ending\n");
    return;
}
void lab4q3t2(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q3T2: 2 concurrent senders and 1 receiver\n");
    kprintf("---------------------------------------------------------------\n");
    pid32 receiver_pid = create(receiver, 1024, 20, "receiver", 1, 2);
    resume(receiver_pid);
    sleep(2);
    resume(create(sender, 1024, 20, "sender1", 1, receiver_pid));
    sleep(2);
    resume(create(sender, 1024, 20, "sender2", 1, receiver_pid));
    sleep(2);
    kprintf("LAB4Q3T2: Ending\n");
    return;
}
int sigxcpucb(void *ptr) {
    kprintf("[Pid %d @ t=%d] MYSIGXCPU callback has been called.\n", currpid, clkmsec);
    return OK;
}
void sigxcpufn(void) {
    int i;
    kprintf("[Pid %d @ t=%d] Registering a MYSIGXCPU callback.\n"
                , currpid, clkmsec);
    registercbsig(MYSIGXCPU,&sigxcpucb,0);
    kprintf("[Pid %d @ t=%d] Running.\n", currpid, clkmsec);
    for(i=0; i<99999999; i++);
    kprintf("[Pid %d @ t=%d] Exiting.\n", currpid, clkmsec);
    return;
}
void lab4q3t3(void) {
    sent=0;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q3T3: 1 long process with MYSIGXCPU hander defined. \n");
    kprintf("---------------------------------------------------------------\n");
    resume(create(sigxcpufn, 1024, 20, "sigxcpuprocess", 0));
    sleep(2);
    kprintf("LAB4Q3T3: Ending\n");
    return;
}

int alarms_raised = 0;
int alarmcb(void *ptr) {
    kprintf("[Pid %d @ t=%d] Alarm callback has been called.\n", currpid, clkmsec);
    alarms_raised++;
    return OK;
}
int alarm_proc(int numAlarms, int ms) {
    int i;
    kprintf("[Pid %d @ t=%d] Registering a MYSIGALRM callback.\n"
                , currpid, clkmsec);
    registercbsig(MYSIGALRM,&alarmcb,0);
    alarmms(ms);
    kprintf("[Pid %d @ t=%d] Alarm set for %dms.\n",currpid,clkmsec,ms);
    while(TRUE) {
        kprintf("[Pid %d @ t=%d] Running.\n", currpid, clkmsec);
        for(i=0; i<99999999; i++);
        if (alarms_raised == numAlarms) {
            kprintf("[Pid %d @ t=%d] Exiting.\n", currpid, clkmsec);
            return 0;
        }
    }
    return 0;
}
void lab4q3t4(void) {
    alarms_raised = 0;
    int nprocs = 4;
    kprintf("---------------------------------------------------------------\n");
    kprintf("LAB4Q3T4: %d processes with alarms at 850, 350, 600 and 100 ms. \n",nprocs);
    kprintf("---------------------------------------------------------------\n");
    resume(create(alarm_proc, 1024, 20, "alarm_proc", 2, nprocs, 850));
    resume(create(alarm_proc, 1024, 20, "alarm_proc", 2, nprocs, 350));
    resume(create(alarm_proc, 1024, 20, "alarm_proc", 2, nprocs, 600));
    resume(create(alarm_proc, 1024, 20, "alarm_proc", 2, nprocs, 100));
    sleep(3);
    kprintf("LAB4Q3T4: Ending\n");
    return;
}
