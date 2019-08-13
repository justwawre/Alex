/*
gcc -masm=intel -S

main:
.LFB0:
.cfi_startproc
push	rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
mov	rbp, rsp
.cfi_def_cfa_register 6
mov	DWORD PTR -8[rbp], 0

//init the struct
movzx	eax, BYTE PTR -8[rbp]
or	eax, 3
mov	BYTE PTR -8[rbp], al

//b.mid  = 33;
movzx	eax, WORD PTR -8[rbp]
and	ax, -4093  //0XFF03
or	al, -124   //0x84=132=33*4
mov	WORD PTR -8[rbp], ax

//xxx = b.mid;
movzx	eax, WORD PTR -8[rbp]
shr	ax, 2
and	ax, 1023
movzx	eax, ax
mov	DWORD PTR -4[rbp], eax

mov	eax, 0
pop	rbp
.cfi_def_cfa 7, 8
ret
*/
struct bits
{
	unsigned int low : 2;
	unsigned int mid : 10;
	unsigned int high : 20;
};

int main()
{
	struct bits b = {-1};
	unsigned int xxx;
	b.mid = 33;
	xxx = b.mid;
	return 0;
}
