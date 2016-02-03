#include <bits/stdc++.h>

using namespace std;

#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define MUL		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM 	6	/* Decimal Number  */
//Relational Operators
#define GR       7 /* Greater then > */
#define LS       8 /*Less then < */
#define EQ       9 /* Equals (single) = */
#define EQQ      10 /*Double Equals == */

#define ID       11 /* Identifier */

#define MINUS   12 /* - */
#define DIV      13 /* divide ( / ) */

//Reserved Keywords
#define  IF     14
#define THEN 	15
#define WHILE 	16
#define DO 		17
#define BEGIN 	18
#define END 	19

#define ERR 	20  //Error 


extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;

//New Functions Added
int lex();
void advance();
int match(int token);
string getCurrentToken();