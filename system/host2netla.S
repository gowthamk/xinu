# host2netla assembly function
.section .text
.globl host2netla
.type host2netla, @function

host2netla:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
    bswap   %eax
	popl	%ebp
    ret
