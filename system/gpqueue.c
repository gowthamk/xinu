#include<xinu.h>
#include<stdlib.h>
#include<gpqueue.h>

int32 enqueueg(struct gpqueue *gpq, void* data) {
    if (gpq->size >= NPROC) {
        return -1;
    }
    if (gpq->size == 0) {
        gpq->entries[0].data = data;
        gpq->entries[0].next = gpq->entries[0].prev = -1;
        gpq->head = 0; gpq->tail = 0;
    } else {
        qid16 cur_tail = gpq->tail;
        struct gpqentry *cur_tail_entry = &(gpq->entries[cur_tail]);
        qid16 new_tail = (gpq->tail + 1) % NPROC;
        cur_tail_entry->next = new_tail;
        struct gpqentry *new_tail_entry = &(gpq->entries[new_tail]);
        new_tail_entry->data = data;
        new_tail_entry->prev = cur_tail;
        new_tail_entry->next = -1;
        gpq->tail = new_tail;
    }
    gpq->size += 1;
    return 0;
}

void* dequeueg(struct gpqueue *gpq) {
    if (gpq->size <= 0) {
        return NULL;
    }
    struct gpqentry *cur_head_entry = &(gpq->entries[gpq->head]);
    if (gpq->size == 1) {
        /* reset head and tail, if we are dequeuing the last entry */
        gpq->head = gpq->tail = 0;
    } else {
        qid16 new_head = cur_head_entry->next;
        struct gpqentry *new_head_entry = &(gpq->entries[new_head]);
        new_head_entry->prev = -1;
        /* update head to new_head */
        gpq->head = new_head;
    }
    gpq->size -= 1;
    return cur_head_entry->data;
}

void printgq(struct gpqueue *gpq, void (*print_data)(void*)) {
    int i;
    struct gpqentry *cur_entry = &(gpq->entries[gpq->head]);
    kprintf("[");
    for(i=1;i<=gpq->size;i++) {
        print_data(cur_entry->data);
        if(i < gpq->size) {
            kprintf(", ");
        }
        cur_entry = &(gpq->entries[cur_entry->next]);
    }
    kprintf("]\n");
    return;
}
