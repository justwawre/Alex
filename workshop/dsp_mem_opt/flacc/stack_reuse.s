	.section .text,code
__FILE_START:
	.global	main                    // -- Begin function main
main:                                   // @main
//*****************************************************************************
// Function:		main
// File:		a.c
// Input arguments:
// Returns:		a0h
//*****************************************************************************
					// MF#0
// %bb.0:                               // %entry
	push       dp           	// (*)
	mv         sp, dp       	// (*)
|	subsp      1            	// (*)
	pushg      acch         	// (*)


	
	callr      #rand        	// 6 a.c (*), CurrBundle: 4, CriticalPath: 4
	mv         a0h, *dp(-1) 	// 6 (*), CurrBundle: 1, CriticalPath: 1, 1-byte Folded Spill
|	callr      #rand        	// 7 (*)
	.rule_off               	// 7
	copy       a0, a5       	// 7 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 8 (*)
	copy       a0, a6       	// 8 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 9 (*)
	copy       a0, a7       	// 9 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 10 (*)
	copy       a0, a4       	// 10 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 11 (*)
	.rule_on
	mv         *dp(-1), a1h 	// (*), 1-byte Folded Reload

	cmp        101, a1h     	// 13 (*), CurrBundle: 2, CriticalPath: 2
	if         .a1:ge       	// 14
|	addh       a1h, a5      	// 14 (*)
|	mv         #s, r0       	// 14
	if         .a1:ge       	// 14
|	addh       a5h, a6      	// 14 (*)
|	mv         *r0, a1h     	// 14
	addh       a6h, a7, .a1:ge	// 14 (*)
	addh       a7h, a4, .a1:ge	// 14 (*)
	addh       a4h, a0, .a1:ge	// 14 (*)
	addh       a1h, a0, .a1:ge	// 14 (*)
	mv         a0h, *r0, .a1:ge	// 14 (*), CurrBundle: 7, CriticalPath: 7
	
	
	
	callr      #rand        	// 17 (*), CurrBundle: 1, CriticalPath: 1
	mv         a0h, *dp(-1) 	// 17 (*), CurrBundle: 1, CriticalPath: 1, 1-byte Folded Spill
|	callr      #rand        	// 18 (*)
	.rule_off               	// 18
	copy       a0, a5       	// 18 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 19 (*)
	copy       a0, a6       	// 19 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 20 (*)
	copy       a0, a7       	// 20 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 21 (*)
	copy       a0, a4       	// 21 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 22 (*)
	.rule_on                	// 23
	cmp        301, a5h     	// 23 (*)
	brr        #.LBB0_2, .a5:lt	// 23 (*), CurrBundle: 2, CriticalPath: 2


// %bb.1:                               // %if.then24
	mv         *dp(-1), a1h 	// 24 (*), 1-byte Folded Reload
|	mv         #s, r0       	// 24
	addh       a1h, a5      	// 24 (*)
|	mv         *r0, a1h     	// 24
	addh       a5h, a6      	// 24 (*)
	addh       a6h, a7      	// 24 (*)
	addh       a7h, a4      	// 24 (*)
	addh       a4h, a0      	// 24 (*)
	subh       a0h, a1      	// 24 (*)
	mv         a1h, *r0     	// 24 (*), CurrBundle: 8, CriticalPath: 8
.LBB0_2:                                // %if.end30
	mv         #s, r0       	// 26 (*)
	mv         *r0, a0h     	// 26 (*)
	popg       acch         	// 26 CurrBundle: 3, CriticalPath: 2
	//APP
	// barrier                      	// 26
	//NO_APP
	addsp      2            	// 26 (*)
|	mv         *dp(0), dp   	// 26 (*)
__END_main:
	rets                    	// 26 (*), CurrBundle: 2, CriticalPath: 2

// Procedure estimates:
// Code size: 101 words (28 bits/instr)
// Instructions / cycles: 57 / 39
// Loop weighted cycles: 39
// Stack allocation: 16

