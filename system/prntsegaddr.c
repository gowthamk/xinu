#include<xinu.h>

void doit(char* segdesc, char *segptr) {
    int i;
    kprintf("Last 8 bytes of %s segment are:\n",segdesc);
    for(i=0;i<8;i++) {
        kprintf("0x%02X\t",(uint8)*(segptr+i));
    }
    kprintf("\n");
    return;
}

void print_size(char* segdesc, uint32 low, uint32 high) {
	kprintf("Size of %s segment: %10d\n",
        segdesc, high - low);
    return;
}

void prntsegaddr() {
	kprintf("Text segment ends at: 0x%08X.\n", (uint32)&etext -1);
	kprintf("Data segment ends at: 0x%08X.\n", (uint32)&edata -1);
	kprintf("BSS segment ends at: 0x%08X.\n", (uint32)&ebss -1);
    doit("text",(char*)etext);
    doit("data",(char*)edata);
    doit("BSS",(char*)ebss);
    print_size("Text",(uint32)&text,(uint32)&etext);
    print_size("Data",(uint32)&data,(uint32)&edata);
    print_size("BSS",(uint32)&bss,(uint32)&ebss);
    return;
}
