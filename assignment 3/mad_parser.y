%{
#include <bits/stdc++.h>

using namespace std;

extern int yylex();
extern int yyleng;
extern int yylineno;
extern char* yytext;

void yyerror(const char*);
%}

%union{
	int dtype_int;
	bool dtype_bool;
	int opertype_int;
}

%token ID
%token COMMA
%token SEMI
%token OPENPAREN
%token CLOSEPAREN
%token OPENCURLY
%token CLOSECURLY
%token OPENNEGATE
%token VOID
%token DTYPE_INT
%token DTYPE_BOOL
%token EQ
%token ARITH
%token RELN
%token LOGICAL
%token LOGICALNOT
%token IF
%token ELSE
%token WHILE
%token FOR
%token RETURN
%token PRINT
%token READ
%token BOOLCONST
%token INTCONST

%%



%%

void yyerror(const char* err_msg)
{
	cout<<"Line "<<yylineno<<": "<<err_msg<<" at "<<string(yytext, yyleng)<<endl;
}

int main()
{
	yydebug = 0;
	yyparse();
}
