#include<xinu.h>
long host2netlb(long arg) {
    long res;
    asm ("movl %1, %%eax; \
          bswap %%eax; \
          movl %%eax, %0"
          :"=r"(res)
          : "r" (arg)); 
    return res;
}
