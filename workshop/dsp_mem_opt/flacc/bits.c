struct bits
{
	unsigned short low : 2;
	unsigned short mid: 10;
	signed short : 4;
};
unsigned short i = 0x12;
int main()
{
	struct bits b = {-1};
	unsigned short xxx;
	xxx = i;
	b.mid = 33;
	xxx = b.mid;
	return 0;
}
/*
esekilxv9236 [11:22] [/home/exxxngc] -> flacc -S -O0 bits.c
esekilxv9236 [11:22] [/home/exxxngc] -> cat bits.s

	subsp      3
	mv         0, a0h
	mv         a0h, *dp(-1)

	mv         *dp(-2), a0h 	// 10 bits.c
	or         49152, a0h   	// 10
	mv         a0h, *dp(-2) 	// 10
	mv         *dp(-2), a0h 	// 10
	and        49167, a0h   	// 10
	mv         a0h, *dp(-2) 	// 10

	mv         #i, r0       	// 12
	mv         *r0, a0h     	// 12
	mv         a0h, *dp(-3) 	// 12

	mv         *dp(-2), a0h 	// 13
	and        49167, a0h   	// 13
	addh       528, a0      	// 13
	mv         a0h, *dp(-2) 	// 13


	mv         *dp(-2), a0h 	// 14
	exz        a0, 20, 9, a0h	// 14
	mv         a0h, *dp(-3) 	// 14


	sub        a0, a0, a0   	// 15
	//APP
	// barrier                      	// 15
	//NO_APP
	addsp      4            	// 15
|	mv         *dp(0), dp   	// 15
__END_main:
	rets                    	// 15

*/


