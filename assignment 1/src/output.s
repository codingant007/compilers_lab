org 100h

x DD 900
 JMP start 

start:
MOV bx,20
PUSH bx
POP ax
MOV bx, ax
MOV x , bx

Label0:
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
 PUSH bx
MOV bx,15
PUSH bx
POP ax
MOV bx, ax
 POP cx
 CMP cx , bx
JNG Label1
MOV bx, 1
JMP Label2
Label1:
MOV bx, 0
Label2:
CMP bx, 1
JNZ Label3
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
PUSH bx
MOV bx,1
PUSH bx
POP ax
MOV bx, ax
POP cx
SUB cx , bx
MOV x , cx
JMP Label0

Label3:

Label4:
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
 PUSH bx
MOV bx,21
PUSH bx
POP ax
MOV bx, ax
 POP cx
 CMP cx , bx
JNL Label5
MOV bx, 1
JMP Label6
Label5:
MOV bx, 0
Label6:
CMP bx, 1
JNZ Label7
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
PUSH bx
MOV bx,1
PUSH bx
POP ax
MOV bx, ax
POP cx
ADD cx , bx
MOV x , cx
JMP Label4

Label7:

Label8:
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
 PUSH bx
MOV bx,21
PUSH bx
POP ax
MOV bx, ax
 POP cx
 CMP cx , bx
JNZ Label9
MOV bx, 1
JMP Label10
Label9:
MOV bx, 0
Label10:
CMP bx, 1
JNZ Label11
MOV bx , x
PUSH bx
POP ax
MOV bx, ax
PUSH bx
MOV bx,1
PUSH bx
POP ax
MOV bx, ax
POP cx
SUB cx , bx
MOV x , cx
JMP Label8

Label11:


RET
