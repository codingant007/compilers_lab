global start

section .data

x DD 900

section .text
start:
MOV ebx,10
PUSH ebx
POP eax
MOV ebx, eax
MOV [x] , ebx

MOV ebx , [x]
PUSH ebx
POP eax
MOV ebx, eax
 PUSH ebx
MOV ebx,10
PUSH ebx
POP eax
MOV ebx, eax
 POP ecx
 CMP ecx , ebx
JZ Label0
MOV ebx, 1
JMP Label1
Label0:
MOV ebx, 0
Label1:

 JNZ Label2
MOV ebx,5
PUSH ebx
POP eax
MOV ebx, eax
MOV [x] , ebx

Label2:


RET
