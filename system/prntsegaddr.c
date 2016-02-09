#include<xinu.h>

void doit(char *segptr) {
    int i;
    for(i=0;i<8;i++) {
        kprintf("%02X ",(uint8)*(segptr+i));
    }
    kprintf("\n");
    return;
}

void print_size(char* segdesc, uint32 low, uint32 high) {
	kprintf("%s length: %10d\n",
        segdesc, high - low);
    return;
}

void prntsegaddr() {
	kprintf("text end at 0x%08X following ", (uint32)&etext -1);
    doit((char*)etext);
	kprintf("data end at 0x%08X following ", (uint32)&edata -1);
    doit((char*)edata);
	kprintf("bss end at 0x%08X following ", (uint32)&ebss -1);
    doit((char*)ebss);
    print_size("text",(uint32)&text,(uint32)&etext);
    print_size("data",(uint32)&data,(uint32)&edata);
    print_size("bss",(uint32)&bss,(uint32)&ebss);
    return;
}
