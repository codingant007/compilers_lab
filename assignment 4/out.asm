.data

main_z_3_2: .byte 0x41
main_a_2_2: .byte 0x41

 .text 
 .globl main 
main:
sw $ra 0($sp)
move $fp $sp 
addiu $sp $sp -4
li $t0 'f' 
sb $t0 main_a_2_2

li $t0 1
sb $t0 main_z_3_2

lw $ra 0($fp)
move $sp $fp
addiu $sp $sp 0
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra

