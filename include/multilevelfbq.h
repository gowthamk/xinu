struct mlfbq {
    struct gpqueue queues[TS_NUM_PRIO];
};

extern status mlfbq_insert(pid32, struct mlfbq*);
extern pid32 mlfbq_dequeue(struct mlfbq*);
extern int mlfbq_firstkey(struct mlfbq*);
extern struct mlfbq* mlfbq_new(void);
