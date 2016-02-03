org 100h

x DD 900
y DD 1000
h DD 1100
 JMP start 

start:
MOV bx,5
PUSH bx
POP ax
MOV bx, ax
MOV x , bx

MOV bx , x
PUSH bx
POP ax
MOV bx, ax
 PUSH bx
MOV bx,5
PUSH bx
POP ax
MOV bx, ax
 POP cx
 CMP cx , bx
JNZ Label0
MOV bx, 1
JMP Label1
Label0:
MOV bx, 0
Label1:
CMP bx, 1

 JNZ Label2
MOV bx,20
PUSH bx
POP ax
MOV bx, ax
MOV y , bx
MOV bx , y
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
JNG Label3
MOV bx, 1
JMP Label4
Label3:
MOV bx, 0
Label4:
CMP bx, 1

 JNZ Label5
MOV bx,20
PUSH bx
POP ax
MOV bx, ax
MOV h , bx

Label5:

Label2:


RET
