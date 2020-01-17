/*
gcc -masm=intel -S

//xxx = i;
mov	eax, DWORD PTR i[rip]
mov	DWORD PTR -4[rbp], eax

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

*/
struct bits
{
	unsigned int low : 2;
	unsigned int mid : 10;
	unsigned int high : 20;
};
int  i = 0x12;
int main()
{
	struct bits b = {-1};
	unsigned int xxx;
	xxx = i;
	b.mid = 33;
	xxx = b.mid;
	return 0;
}
