#include<xinu.h>

void sender(pid32 recvpid) {
    umsg32 msg = (umsg32) currpid;
    kprintf("[Pid %d] Sending message.\n",currpid);
    sendbt(recvpid, msg, 1000);
    kprintf("[Pid %d] Sent message.\n",currpid);
    return;
}
