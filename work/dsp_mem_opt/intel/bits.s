	.file	"bits.c"
	.intel_syntax noprefix
	.text
	.comm	i,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	eax, DWORD PTR i[rip]
	and	ax, 1023
	and	ax, 1023
	lea	edx, 0[0+rax*4]
	movzx	eax, WORD PTR -8[rbp]
	and	ax, -4093
	or	eax, edx
	mov	WORD PTR -8[rbp], ax
	mov	eax, DWORD PTR i[rip]
	mov	DWORD PTR -4[rbp], eax
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
