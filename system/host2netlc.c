#include<xinu.h>

long host2netlc(long arg) {
    long res;
    char *argptr = &arg + sizeof(long) -1, *resptr = &res;
    int i;
    for(i=0; i<=sizeof(long); i++) {
        *(resptr) = *(argptr);
        resptr ++;
        argptr --;
    }
    return res;
}
