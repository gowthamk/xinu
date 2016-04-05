#include<xinu.h>

int alarm_setter(int ms) {
    struct procent* p = &proctab[currpid];
    p->alarmms = ms;
    kprintf("[Pid %d] Alarm for %d ms.\n",currpid,ms);
    sleep(2);
    return 0;
}

void test_deltaqueue(void) {
    pid32 pid1, pid2, pid3, pid4;
    pid1 = create(alarm_setter, 1024, 20, "alarm_setter1", 1, 250);
    pid2 = create(alarm_setter, 1024, 20, "alarm_setter2", 1, 150);
    pid3 = create(alarm_setter, 1024, 20, "alarm_setter3", 1, 200);
    pid4 = create(alarm_setter, 1024, 20, "alarm_setter4", 1, 100);
    resume(pid1);
    resume(pid2);
    resume(pid3);
    resume(pid4);
    struct dqentry* hd = NULL;
    hd = insertdq(hd, &proctab[pid1]);
    hd = insertdq(hd, &proctab[pid2]);
    hd = insertdq(hd, &proctab[pid3]);
    hd = insertdq(hd, &proctab[pid4]);
    printdq(hd);
    return;
}
