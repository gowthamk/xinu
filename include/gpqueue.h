/* gpqueue.h (Generic Process Queue) - enqueueg, dequeueg, is_emptyg */
struct gpqentry {
    void *data;
    qid16 prev;
    qid16 next;
};

struct gpqueue {
    int size;
    struct gpqentry entries[NPROC];
    qid16 head;
    qid16 tail;
};

extern int32 enqueueg(struct gpqueue*, void*);
extern void* dequeueg(struct gpqueue*);
extern void  printgq(struct gpqueue*, void (*print_data)(void*));
