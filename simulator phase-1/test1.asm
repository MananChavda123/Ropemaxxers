.data
.data
base: .word 4 2 10 6 9 1 3 
.text
lw x16 base
addi x18 x0 0
addi x21 x0 1
addi x12 x0 0
addi x4 x0 6
add x7 x0 x0
addi x31 x0 -1
loop:
bge x18 x4 exit2
addi x12 x0 0 
lw x10 0(x16)
loop1:
bge x12 x4 exit1
lw x10 0(x16)
lw x11 4(x16)
addi x12 x12 1
blt x11 x10 change
addi x16 x16 4
j loop1
exit1:
lw x16, base
addi x18 x18 1
j loop
change:
lw x19 0(x16)
lw x20 4(x16)
sw x19 4(x16)
sw x20 0(x16)
addi x16, x16, 4
j loop1
exit2: