.data

main_x_1_2: .word 0
main_z_1_2: .word 0
main_w_1_2: .word 0

 .text 
 .globl main 
main:
sw $ra 0($sp)
move $fp $sp 
addiu $sp $sp -4
sw $t0 main_x_1_2

lw $t0 main_x_1_2
sw $t0 0($sp) 
addiu $sp $sp -4
li $t0 5
lw $t1 4($sp)
addiu $sp $sp 4
mul $t0 $t0 $t1
sw $t0 0($sp) 
addiu $sp $sp -4
li $t0 3
lw $t1 4($sp)
addiu $sp $sp 4
div $t0 $t1 $t0
sw $t0 main_z_1_2

lw $t0 main_z_1_2
neg $t0 $t0 
sw $t0 main_w_1_2

move $sp $fp
lw $ra 0($fp)
addiu $sp $sp 4
addiu $sp $sp 0
jr $ra

