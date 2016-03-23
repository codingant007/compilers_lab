%{
#include <bits/stdc++.h>
%}

%option noyywrap

%{
int num_lines = 0, num_chars = 0;
%}

ID [a-zA-Z][a-zA-Z0-9]*
COMMA (",")
SEMI (";")
OPENPAREN "(" 
CLOSEPAREN ")"
OPENCURLY "{"
CLOSECURLY "}"
VOID ("void")
DTYPE ("int"|"bool")
EQ ("=")
ARITH [-+*/%] 
RELN ("=="|"<"|">"|"<="|">="|"!=")
LOGICAL ("&&"|"||"|"!")
IF ("if")
ELSE ("else")
WHILE ("while")
FOR ("for")
RETURN ("return")
PRINT ("print")
READ ("readInteger"|"readBool")
BOOLCONST ("true"|"false")
INTCONST [0-9]+

%%
{DTYPE} {printf( "%s : DTYPE\n", yytext );}
{VOID} {printf( "%s : VOID\n", yytext );}
{IF} {printf( "%s : IF\n", yytext );}
{ELSE} {printf( "%s : ELSE\n", yytext );}
{WHILE} {printf( "%s : WHILE\n", yytext );}
{FOR} {printf( "%s : FOR\n", yytext );}
{RETURN} {printf( "%s : RETURN\n", yytext );}
{PRINT} {printf( "%s : PRINT\n", yytext );}
{READ} {printf( "%s : READ\n", yytext );}
{COMMA} {printf( "%s : COMMA\n", yytext );}
{SEMI} {printf( "%s : SEMI\n", yytext );}
{OPENPAREN} {printf( "%s : OPENPAREN\n", yytext );}
{CLOSEPAREN} {printf( "%s : CLOSEPAREN\n", yytext );}
{OPENCURLY} {printf( "%s : OPENCURLY\n", yytext );}
{CLOSECURLY} {printf( "%s : CLOSECURLY\n", yytext );}
{EQ} {printf( "%s : EQ\n", yytext );}
{ARITH} {printf( "%s : ARITH\n", yytext ); }
{RELN} {printf( "%s : RELN\n", yytext );}
{LOGICAL} {printf( "%s : LOGICAL\n", yytext );}
{BOOLCONST} {printf( "%s : BOOLCONST\n", yytext );}
{INTCONST} {printf( "%s : INTCONST\n", yytext );}
{ID} {printf( "%s : ID\n", yytext );}

[ \t]+          /* eat up whitespace */
[\n]+ ++num_lines;
.          printf( "Unrecognized character: %s\n", yytext );
%%

int main( int argc, char **argv )
{
        yylex();
}
