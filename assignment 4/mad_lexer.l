%{
#include <bits/stdc++.h>
#include "node.h"
#include "mad_parser.tab.h"
%}

%option noyywrap yylineno

%{
int num_lines = 0, num_chars = 0;
%}

ID [a-zA-Z][_a-zA-Z0-9]*
COMMA (",")
SEMI (";")
OPENPAREN "("
CLOSEPAREN ")"
OPENCURLY "{"
CLOSECURLY "}"
OPENSQUARE "["
CLOSESQUARE "]"
OPENNEGATE "-("
VOID ("void")
DTYPE ("char"|"int"|"bool")
EQ ("=")
ARITH [-+*/]
RELN ("=="|"<"|">"|"<="|">="|"!=")
LOGICAL ("&&"|"||")
LOGICALNOT ("!")
IF ("if")
ELSE ("else")
WHILE ("while")
RETURN ("return")
BOOLCONST ("true"|"false")
INTCONST [0-9]+

%%

{DTYPE} {if (yyleng == 3) return DTYPE_INT; else if (yyleng == 4){ if(strcmp("char", yytext)) return DTYPE_BOOL; else return DTYPE_CHAR; } }
{VOID} {return VOID; }
{IF} {return IF; }
{ELSE} {return ELSE; }
{WHILE} {return WHILE; }
{RETURN} {return RETURN; }
{COMMA} {return COMMA; }
{SEMI} {return SEMI; }
{OPENPAREN} {return OPENPAREN; }
{CLOSEPAREN} {return CLOSEPAREN; }
{OPENCURLY} {return OPENCURLY; }
{CLOSECURLY} {return CLOSECURLY; }
{OPENSQUARE} {return OPENSQUARE; }
{CLOSESQUARE} {return CLOSESQUARE; }
{OPENNEGATE} {return OPENNEGATE; } /*Added token for negation*/
{EQ} {return EQ; }
{ARITH} {yylval.node_con=strdup(yytext);return ARITH; }
{RELN} {yylval.node_con=strdup(yytext);return RELN; }
{LOGICAL} {yylval.node_con=strdup(yytext);return LOGICAL; }
{LOGICALNOT} {return LOGICALNOT; } /*Separated LOGICALNOT from LOGICAL as it is unary*/
{BOOLCONST} {yylval.node_con=strdup(yytext);return BOOLCONST; }
{INTCONST} {yylval.node_con=strdup(yytext);return INTCONST; }
{ID} {yylval.node_con=strdup(yytext); return ID; }

[ \t]+          /* eat up whitespace */
[\n]+ ++num_lines;
.          printf( "Unrecognized character: %s\n", yytext );
%%
