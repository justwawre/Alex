	.file	"bits.c"
	.intel_syntax noprefix
	.text
	.globl	i
	.data
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	18
	.text
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
	mov	DWORD PTR -8[rbp], 0
	movzx	eax, BYTE PTR -8[rbp]
	or	eax, 3
	mov	BYTE PTR -8[rbp], al
	mov	eax, DWORD PTR i[rip]
	mov	DWORD PTR -4[rbp], eax
	movzx	eax, WORD PTR -8[rbp]
	and	ax, -4093
	or	al, -124
	mov	WORD PTR -8[rbp], ax
	movzx	eax, WORD PTR -8[rbp]
	shr	ax, 2
	and	ax, 1023
	movzx	eax, ax
	mov	DWORD PTR -4[rbp], eax
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
