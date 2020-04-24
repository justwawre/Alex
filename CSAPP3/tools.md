单独一文，写一下用到的工具

# objdump
Can display all of the information in an object file. Its most useful function is disassembling the binary instructions in the .text section.

```
#decode the object file or a.out
objdump -D  <filename>

#only dump a specific section
objdump -d -j .rodata  a.out

```

# generate the M$ masm file
```
gcc  -S -masm=intel *.c
```

