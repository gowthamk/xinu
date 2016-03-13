#include<xinu.h>

void receiver() {
    while(TRUE) {
        sleepms(1500);
        kprintf("[Pid %d] Receiving a message\n",currpid);
        umsg32 msg = receive();
        kprintf("[Pid %d] Received %d\n",currpid,msg);
    }
}
