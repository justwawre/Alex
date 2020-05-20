# generate the M$ masm file
```bash
gcc  -S -masm=intel *.c
```
# disable the " division by zero" warning

```bash
gcc -g -Wno-div-by-zero
```
