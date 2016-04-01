%{
#include <bits/stdc++.h>
#include "node.h"

using namespace std;

extern int yylex();
extern int yyleng;
extern int yylineno;
extern char* yytext;

void yyerror(const char*);


	node::node(string con, node_type t)
	{	
		content = con;
		type = t;
		child = NULL;
		sibling = NULL;
	}
	node::node(const char* con, int t)
	{
		content = (con);
		if(t == 0) type = NONTERM;
		else if(t == 1) type = TERM;
		else if(t == 2) type = VAL;
	}
node *root;
%}

%union{
	int dtype_int;
	bool dtype_bool;
	int opertype_int;
	node* node_el;
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

%token NONTERMINAL 0
%token TERMINAL 1
%token VALUE 2

%type <node_el> mad_program supported_declarations variable_declarations function_declarations variable_definitions dtype argument_list statement_block
%type <node_el> variable_list statement_list supported_statement id_list supported_constant
%%

mad_program:
	supported_declarations { $$ = new node("mad_program", NONTERMINAL); $$->child = $1; root = $$;}
	| supported_declarations mad_program { $$ = new node("mad_program", NONTERMINAL); $$->child = $1; $1->sibling = $2; root = $$;}
	| error '\n' { yyerror("Compilation terminating with errors"); }

supported_declarations:
	variable_declarations { $$ = new node("supported_declarations", NONTERMINAL); $$->child = $1; }
	| function_declarations {$$ = new node("supported_declarations", NONTERMINAL); $$->child = $1;}

variable_declarations:
	variable_definitions SEMI {$$ = new node("variable_declarations", NONTERMINAL); $$->child = $1; $1->sibling = new node("SEMI", TERMINAL);}
	| variable_definitions error { yyerror("Possible missing semicolon in variable declaration list"); }

variable_definitions:
	dtype ID {$$ = new node("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = new node("ID", VALUE);}
	| variable_definitions COMMA ID {$$ = new node("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = new node("COMMA", TERMINAL); $1->sibling->sibling = new node("ID", VALUE);}
	| variable_definitions error ID '\n' { yyerror("Missing comma in definitions list"); }

dtype:
	DTYPE_INT {$$ = new node("DTYPE_INT", TERMINAL); /*$$->child = $1;*/} 
	| DTYPE_BOOL {$$ = new node("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
	| error { yyerror("Unknown type declaration"); }

function_declarations:
	dtype ID OPENPAREN argument_list CLOSEPAREN statement_block {$$ = new node("function_declarations", NONTERMINAL); $$->child = $1; node* id = new node("ID", VALUE); $1->sibling = id; node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = $4; node* closeparen = new node("CLOSEPAREN", TERMINAL); $4->sibling = closeparen; closeparen->sibling = $6; }
	| VOID ID OPENPAREN argument_list CLOSEPAREN statement_block {$$ = new node("function_declarations", NONTERMINAL); $$->child = new node("VOID", TERMINAL); node* id = new node("ID", VALUE); $$->child->sibling = id; node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = $4; node* closeparen = new node("CLOSEPAREN", TERMINAL); $4->sibling = closeparen; closeparen->sibling = $6;}

argument_list:
	dtype ID COMMA argument_list {$$ = new node("argument_list", NONTERMINAL); $$->child = $1; node* id = new node("ID", VALUE); $1->sibling = id; node* comma= new node("COMMA", TERMINAL); id->sibling = comma; comma->sibling = $4;} 
	|dtype ID {$$ = new node("argument_list", NONTERMINAL); $$->child = $1; node* id = new node("ID", VALUE); $1->sibling = id;} 
	|%empty /*epsilon production*/ {$$ = new node("function_declarations", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| dtype ID error argument_list { yyerror("Missing comma in argument list"); }
	| dtype error COMMA argument_list { yyerror("Missing identifier in argument list"); }

statement_block: 
	OPENCURLY variable_list statement_list CLOSECURLY { $$ = new node("statement_block", NONTERMINAL); $$->child = new node("OPENCURLY", TERMINAL); $$->child->sibling = $2; $2->sibling = $3; $3->sibling = new node("CLOSECURLY", TERMINAL); }
	| OPENCURLY variable_list statement_list error { yyerror("Possible missing semicolon in statement block"); }

variable_list:
	%empty /*epsilon production*/ {$$ = new node("variable_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| variable_declarations variable_list { $$ = new node("variable_list", NONTERMINAL); $$->child = $1; $1->sibling = $2; }

statement_list:
	%empty {$$ = new node("statement_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
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
	ID COMMA id_list { $$ = new node("id_list", NONTERMINAL); $$->child = new node("ID", VALUE); node *comma = new node("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3; }
	| ID {$$ = new node("id_list", NONTERMINAL); $$->child = new node("ID", VALUE);}
	| %empty {$$ = new node("id_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| error COMMA id_list { yyerror("Missing identifier name"); }

supported_constant:
	INTCONST {$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("INTCONST", VALUE); }
	| BOOLCONST {$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("BOOLCONST", VALUE); }
	| OPENNEGATE INTCONST CLOSEPAREN {$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("OPENNEGATE", TERMINAL); node* intconst = new node("INTCONST", VALUE); $$->child->sibling = intconst; node* closeparen = new node("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;}


%%

void yyerror(const char* err_msg)
{
	cout<<"Line "<<yylineno<<": "<<err_msg<<endl;
}

/*void print_tree()
{
	stack<int> depth_prod;	
	stack< vector<string> > prod_stack;
	int tab_count=0;
	for(;!depth.empty() && !productions.empty();depth.pop(),productions.pop())
	{
		//vector<string> ts = new vector<string>();
		cout<<tab_count<<":("<<depth.top()<<","<<(depth_prod.empty()?1000:depth_prod.top())<<") ";
		for(int j = 0; j < tab_count; j++)
			cout<<"\t";
		for(;!productions.empty() && productions.top() != DELIMITER; productions.pop())
		{
			cout<<productions.top()<<"   ";
		//	ts.push_back(productions.top());
		}
		cout<<endl;
		//prod_stack.push(ts);
		if(!depth.empty() && depth.top())
		{
			tab_count++;
			depth_prod.push(depth.top()-1);
		}
		else
		{
			for(;!depth_prod.empty() && !depth_prod.top(); depth_prod.pop()) tab_count--;
			if(!depth_prod.empty()) { int ti = depth_prod.top(); depth_prod.pop(); depth_prod.push(ti-1); }
		}
	}
		for(;!productions.empty() && productions.top() != DELIMITER; productions.pop())
		{
			cout<<productions.top()<<"   ";
		//	ts.push_back(productions.top());
		}
}*/

int main()
{
	yydebug = 0;
	yyparse();
	print_tree();
}
