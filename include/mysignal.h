/* mysignal.h - Lab4 signal handlers */

#ifndef NMYSIGNALS
#define NMYSIGNALS 3
#endif

/* Signal identifiers */
#define    MYSIGRECV 5
#define    MYSIGXCPU 6
#define    MYSIGALRM 7

#define isValidSig(x) (x>=5 && x<=7)
#define sigToIndex(x) (x-5)
