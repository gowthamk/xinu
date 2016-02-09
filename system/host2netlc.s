	.file	"host2netlc.c"
	.text
	.globl	host2netlc
	.type	host2netlc, @function
host2netlc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movb	11(%ebp), %al
	movb	%al, -4(%ebp)
	movb	10(%ebp), %al
	movb	%al, -3(%ebp)
	movb	9(%ebp), %al
	movb	%al, -2(%ebp)
	movb	8(%ebp), %al
	movb	%al, -1(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	host2netlc, .-host2netlc
	.ident	"GCC: (Gentoo 4.9.3 p1.4, pie-0.6.4) 4.9.3"
	.section	.note.GNU-stack,"",@progbits
