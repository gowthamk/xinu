#include<xinu.h>

long host2netlc(long arg) {
    long res;
    char *argptr = ((char*)&arg) + sizeof(long) -1;
    char *resptr = (char*)&res;
    int i;
    for(i=0; i<sizeof(long); i++) 
        *(resptr++) = *(argptr--);
    return res;
}
