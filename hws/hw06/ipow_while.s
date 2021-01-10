	.file	"ipow_while.c"
	.text
	.globl	ipow
	.type	ipow, @function
ipow:
.LFB0:
	.cfi_startproc
	movl	$0, %edx
	movl	$1, %eax
	jmp	.L2
.L3:
	imull	%edi, %eax
	addl	$1, %edx
.L2:
	cmpl	%esi, %edx
	jl	.L3
	rep ret
	.cfi_endproc
.LFE0:
	.size	ipow, .-ipow
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
