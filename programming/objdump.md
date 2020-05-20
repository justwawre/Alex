Can display all of the information in an object file. Its most useful function is disassembling the binary instructions in the .text section.

```
#decode the object file or a.out
objdump -D  <filename>

#only dump a specific section
objdump -d -j .rodata  a.out

```