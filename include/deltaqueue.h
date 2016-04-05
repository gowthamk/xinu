/* deltaqueue.h */
struct dqentry {
    struct procent* procent;
    struct dqentry *next;
};
extern struct dqentry* insertdq(struct dqentry*, struct procent*);
extern struct dqentry* dequeuedq(struct dqentry*);
extern struct procent* firstkeydq(struct dqentry*);
extern void  printdq(struct dqentry*);
extern bool8 is_emptydq(struct dqentry*);
