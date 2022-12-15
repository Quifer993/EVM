	.file	"main.c"
	.text
	.p2align 4,,15
	.globl	exponential_function
	.def	exponential_function;	.scl	2;	.type	32;	.endef
	.seh_proc	exponential_function
exponential_function:
	.seh_endprologue
	movsd	.LC0(%rip), %xmm4
	movsd	.LC1(%rip), %xmm5
	movapd	%xmm4, %xmm2
	movapd	%xmm4, %xmm1
	movapd	%xmm4, %xmm3
	.p2align 4,,10
.L2:
	mulsd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	addsd	%xmm4, %xmm2
	comisd	%xmm2, %xmm5
	addsd	%xmm1, %xmm3
	ja	.L2
	movapd	%xmm3, %xmm0
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC2:
	.ascii "Enter the number\0"
.LC3:
	.ascii "%.10f\12\0"
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	%ecx, %ebx
	movq	%rdx, %rsi
	call	__main
	cmpl	$1, %ebx
	je	.L10
	movq	8(%rsi), %rcx
	call	atof
	movsd	.LC0(%rip), %xmm4
	movsd	.LC1(%rip), %xmm5
	movapd	%xmm4, %xmm3
	movapd	%xmm4, %xmm2
	movapd	%xmm4, %xmm1
	.p2align 4,,10
.L8:
	mulsd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	addsd	%xmm4, %xmm2
	comisd	%xmm2, %xmm5
	addsd	%xmm1, %xmm3
	ja	.L8
	leaq	.LC3(%rip), %rcx
	movapd	%xmm3, %xmm1
	movq	%xmm3, %rdx
	call	printf
	xorl	%eax, %eax
.L5:
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
.L10:
	leaq	.LC2(%rip), %rcx
	call	puts
	movl	$1, %eax
	jmp	.L5
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC1:
	.long	1610612736
	.long	1105859512
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	atof;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
