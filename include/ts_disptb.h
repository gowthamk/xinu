struct ts_disptb {
  int ts_tqexp;         // new priority: CPU-bound (time quantum expired)
  int ts_slpret;        // new priority: I/O-bound (sleep return)
  int ts_quantum;       // new time slice
};

extern struct ts_disptb tsdtab[];

#define TS_MAX_PRIO 19
#define TS_INIT_PRIO ((TS_MAX_PRIO / 2) + 1)
/* TS_NUM_PRIO must be TS_MAX_PRIO+1. It must be divisible by 5 */
#define TS_NUM_PRIO (TS_MAX_PRIO + 1)
/* TS_MAX_QUANTUM must be divisible by 5 */
#define TS_MAX_QUANTUM 100
