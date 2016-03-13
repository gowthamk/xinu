#include<xinu.h>

void sender(pid32 recvpid, int maxwait) {
    umsg32 msg = (umsg32) currpid;
    kprintf("[Pid %d] Sending message.\n",currpid);
    int32 status = sendbt(recvpid, msg, maxwait);
    if (status == SYSERR) {
        kprintf("[Pid %d] Send did not succeed!\n");
    } else if (status == TIMEOUT) {
        kprintf("[Pid %d] Send timed out!\n");
    } else {
        kprintf("[Pid %d] Sent message.\n",currpid);
    }
    return;
}
