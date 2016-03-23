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

%start mad_program

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
%token <opertype_int> EQ
%token <opertype_int> ARITH
%token <opertype_int> RELN
%token <opertype_int> LOGICAL
%token <opertype_int> LOGICALNOT
%token IF
%token ELSE
%token WHILE
%token FOR
%token RETURN
%token PRINT
%token READ
%token <dtype_bool> BOOLCONST
%token <dtype_int> INTCONST

%%

mad_program:
	supported_declarations {}
	| supported_declarations mad_program {}
	| error '\n' { yyerror("Compilation terminating with errors"); }

supported_declarations:
	variable_declarations {}
	| function_declarations {}

variable_declarations:
	variable_definitions SEMI {}
	| variable_definitions error { yyerror("Possible missing semicolon in variable declaration list"); }

variable_definitions:
	dtype ID {}
	| variable_definitions COMMA ID {}
	| variable_definitions error ID { yyerror("Missing comma in definitions list"); }

dtype:
	DTYPE_INT {}
	| DTYPE_BOOL {}
	| error { yyerror("Unknown type declaration"); }

function_declarations:
	dtype ID OPENPAREN argument_list CLOSEPAREN statement_block {}
	| VOID ID OPENPAREN argument_list CLOSEPAREN statement_block {}

argument_list:
	dtype ID COMMA argument_list {}
	|dtype ID {}
	|%empty /*epsilon production*/ {}
	| dtype ID error argument_list { yyerror("Missing semicolon in argument list"); }
	| dtype error COMMA argument_list { yyerror("Missing identifier in argument list"); }

statement_block: 
	OPENCURLY variable_list statement_list CLOSECURLY {}
	| OPENCURLY variable_list statement_list error { yyerror("Possible missing semicolon in statement block"); }

variable_list:
	%empty /*epsilon production*/ {}
	| variable_declarations variable_list {}

statement_list:
	%empty
	| supported_statement statement_list

supported_statement:
	alr_subexpression SEMI {}
	| if_statement {}
	| while_statement {}
	| for_statement {}
	| return_statement {}
	| print_statement {}
	| statement_block {}
	| alr_subexpression error { yyerror("Possible missing semicolon with alr_subexpression"); }

if_statement:
	IF OPENPAREN alr_subexpression CLOSEPAREN statement_block else_statement {} //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK

else_statement:
	%empty {}
	| ELSE supported_statement {}

while_statement:
	WHILE OPENPAREN alr_subexpression CLOSEPAREN {}

for_statement:
	FOR OPENPAREN alr_subexpression SEMI alr_subexpression SEMI alr_subexpression CLOSEPAREN statement_block {} //CHANGED FOR EXPRESSION INTERNAL TO STATEMENT BLOCK
	| FOR OPENPAREN alr_subexpression error alr_subexpression SEMI alr_subexpression CLOSEPAREN statement_block { yyerror("Possible missing semicolon in for"); }
	| FOR OPENPAREN alr_subexpression SEMI alr_subexpression error alr_subexpression CLOSEPAREN statement_block { yyerror("Possible missing semicolon in for"); }
	| FOR OPENPAREN alr_subexpression SEMI alr_subexpression SEMI alr_subexpression error statement_block { yyerror("Possible missing closing parenthesis in for"); }

return_statement: 
	RETURN SEMI {}
	| RETURN alr_subexpression SEMI {}
	| RETURN error { yyerror("Missing semicolon with return"); }
	| RETURN alr_subexpression error { yyerror("Missing semicolon with return"); }

print_statement:
	PRINT OPENPAREN alr_subexpression CLOSEPAREN SEMI {}
	| PRINT error alr_subexpression CLOSEPAREN SEMI { yyerror("Possile missing open parenthesis"); }
	| PRINT OPENPAREN alr_subexpression error SEMI { yyerror("Possible missing closing parenthesis"); }
	| PRINT OPENPAREN alr_subexpression CLOSEPAREN error { yyerror("Missing semicolon with print"); }

alr_subexpression:
	ID EQ alr_subexpression {}	
	| supported_constant {}
	| ID {}
	| ID OPENPAREN id_list CLOSEPAREN  {}
	| OPENPAREN alr_subexpression CLOSEPAREN {}
	| alr_subexpression ARITH alr_subexpression {}
	| OPENNEGATE alr_subexpression CLOSEPAREN {}
	| alr_subexpression RELN alr_subexpression {}
	| alr_subexpression LOGICAL alr_subexpression {}	
	| LOGICALNOT alr_subexpression {}
	| READ OPENPAREN CLOSEPAREN {}
	| error EQ alr_subexpression { yyerror("Missing identifier name"); }
	| ID error alr_subexpression { yyerror("Possible missing equalty sign"); }
	| ID OPENPAREN id_list error { yyerror("Possible missing closing parenthesis"); }
	| READ OPENPAREN error { yyerror("Possible missing closing parenthesis"); }
	| READ error CLOSEPAREN { yyerror("Possible missing opening parenthesis"); }

id_list:
	ID COMMA id_list {}
	| ID {}
	| %empty {}
	| error COMMA id_list { yyerror("Missing identifier name"); }

supported_constant:
	INTCONST {}
	| BOOLCONST {}
	| OPENNEGATE INTCONST CLOSEPAREN {}


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
