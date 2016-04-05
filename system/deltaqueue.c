#include<xinu.h>

struct dqentry* insertdq(struct dqentry *head, struct procent* p) {
    if(head == NULL) {
        head = (struct dqentry*)getmem(sizeof(struct dqentry));
        head->procent = p;
        head->next = NULL;
        return head;
    }
    if (p->alarmms < head->procent->alarmms) {
        struct dqentry *new = (struct dqentry*)getmem(sizeof(struct dqentry));
        new->procent = p;
        new->next = head;
        /* old head's alarm time w.r.t new head's time. */
        head->procent->alarmms -= p->alarmms;
        return new;
    }
    /* p's alarm time w.r.t head's alarm time */
    p->alarmms -= head->procent->alarmms;
    head->next = insertdq(head->next, p);
    return head;
}

struct dqentry* dequeuedq(struct dqentry *head) {
    if (head == NULL) {
        return NULL;
    }
    head = head->next;
    return head;
}

struct procent* firstkeydq(struct dqentry* head) {
    return head->procent;
}

void printdq(struct dqentry *head) {
    kprintf("[");
    while(head != NULL) {
        struct procent* p = head->procent;
        kprintf("(%d,%d),",p->pid,p->alarmms);
        head = head->next;
    }
    kprintf("]");
    return;
}
bool8 is_emptydq(struct dqentry *head) {
    if (head == NULL)
        return TRUE;
    else
        return FALSE;
}
