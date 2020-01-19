/*
check what kind of mem a const array locate?


typical sections of elf file：
.text     code 
.rodata   const, no matter global or not
.data:    global or static vars with intial values
.bss:     global or static vars without intial values, need allocate space in elf file,


can use the objdump to check 
if arr is const, no matter inside or outside the main()
    gcc -c const.c
    objdump -x const.o
    objdump -s -j .rodata const.o
if arr is not const, and outside the main()
    gcc -c  const.c      //arr in  .data
    objdump -s -j .data const.o
if arr is not const, and inside the main()
    gcc -c  const.c 
    objdump -s const.o   //arr init in .text
    objdump -d const.o
*/

int main()
{
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    return 0;
}