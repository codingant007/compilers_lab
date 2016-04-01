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
bool has_error;

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
%type <node_el> variable_list statement_list supported_statement id_list supported_constant alr_subexpression 
%type <node_el> if_statement else_statement while_statement for_statement return_statement print_statement

%%

mad_program:
	supported_declarations { $$ = new node("mad_program", NONTERMINAL); $$->child = $1; root = $$;}
	| supported_declarations mad_program { $$ = new node("mad_program", NONTERMINAL); $$->child = $1; $1->sibling = $2; root = $$;}
	| error '\n' { yyerror("Compilation terminating with errors"); root = NULL;}

supported_declarations:
	variable_declarations { $$ = new node("supported_declarations", NONTERMINAL); $$->child = $1; }
	| function_declarations {$$ = new node("supported_declarations", NONTERMINAL); $$->child = $1;}

variable_declarations:
	variable_definitions SEMI {$$ = new node("variable_declarations", NONTERMINAL); $$->child = $1; $1->sibling = new node("SEMI", TERMINAL);}
	| variable_definitions error { $$ = new node("error", TERMINAL); yyerror("Possible missing semicolon in variable declaration list"); }

variable_definitions:
	dtype ID {$$ = new node("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = new node("ID", VALUE);}
	| variable_definitions COMMA ID {$$ = new node("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = new node("COMMA", TERMINAL); $1->sibling->sibling = new node("ID", VALUE);}
	| variable_definitions error ID '\n' { $$ = new node("error", TERMINAL); yyerror("Missing comma in definitions list"); }

dtype:
	DTYPE_INT {$$ = new node("DTYPE_INT", TERMINAL); /*$$->child = $1;*/} 
	| DTYPE_BOOL {$$ = new node("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
	| error {$$ = new node("error", TERMINAL); yyerror("Unknown type declaration"); }

function_declarations:
	dtype ID OPENPAREN argument_list CLOSEPAREN statement_block {$$ = new node("function_declarations", NONTERMINAL); $$->child = $1; node* id = new node("ID", VALUE); $1->sibling = id; node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = $4; node* closeparen = new node("CLOSEPAREN", TERMINAL); $4->sibling = closeparen; closeparen->sibling = $6; }
	| VOID ID OPENPAREN argument_list CLOSEPAREN statement_block {
		$$ = new node("function_declarations", NONTERMINAL);
		$$->child = new node("VOID", TERMINAL);
		node* id = new node("ID", VALUE); $$->child->sibling = id;
		node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen;
		openparen->sibling = $4;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $4->sibling = closeparen;
		closeparen->sibling = $6;
	}

argument_list:
	dtype ID COMMA argument_list {
		$$ = new node("argument_list", NONTERMINAL); $$->child = $1;
		node* id = new node("ID", VALUE); $1->sibling = id;
		node* comma= new node("COMMA", TERMINAL); id->sibling = comma;
		comma->sibling = $4;
	} 
	|dtype ID {$$ = new node("argument_list", NONTERMINAL); $$->child = $1; node* id = new node("ID", VALUE); $1->sibling = id;} 
	|%empty /*epsilon production*/ {$$ = new node("function_declarations", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| dtype ID error argument_list { $$ = new node("error", TERMINAL); yyerror("Missing comma in argument list"); }
	| dtype error COMMA argument_list { $$ = new node("error", TERMINAL); yyerror("Missing identifier in argument list"); }

statement_block: 
	OPENCURLY variable_list statement_list CLOSECURLY { $$ = new node("statement_block", NONTERMINAL); $$->child = new node("OPENCURLY", TERMINAL); $$->child->sibling = $2; $2->sibling = $3; $3->sibling = new node("CLOSECURLY", TERMINAL); }
	| OPENCURLY variable_list statement_list error { $$ = new node("error", TERMINAL); yyerror("Possible missing semicolon in statement block"); }

variable_list:
	%empty /*epsilon production*/ {$$ = new node("variable_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| variable_declarations variable_list { $$ = new node("variable_list", NONTERMINAL); $$->child = $1; $1->sibling = $2; }

statement_list:
	%empty {$$ = new node("statement_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| supported_statement statement_list {$$ = new node("statement_list", NONTERMINAL); $$->child = $1; $1->sibling = $2;}

supported_statement:
	alr_subexpression SEMI {$$ = new node("supported_statement", NONTERMINAL); $$->child = $1; $1->sibling = new node("SEMI", TERMINAL);}
	| if_statement { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| while_statement { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| for_statement { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| return_statement { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| print_statement { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| statement_block { $$ = new node("supported_statement", NONTERMINAL); $$->child = $1; }
	| alr_subexpression error { yyerror("Possible missing semicolon with alr_subexpression"); $$ = new node("error", TERMINAL); }

if_statement:
	IF OPENPAREN alr_subexpression CLOSEPAREN statement_block else_statement { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		$$ = new node("if_statement", NONTERMINAL);
		$$->child = new node("IF", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
		closeparen->sibling = $5;
		$5->sibling = $6;
	}

else_statement:
	%empty {$$ = new node("else_statement", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| ELSE supported_statement {
		$$ = new node("else_statement", NONTERMINAL); 
		$$->child = new node("ELSE", TERMINAL); 
		$$->child->sibling = $2;
	} 

while_statement:
	WHILE OPENPAREN alr_subexpression CLOSEPAREN {
		$$ = new node("while_statement", NONTERMINAL);
		$$->child = new node("WHILE", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
	}

for_statement:
	FOR OPENPAREN alr_subexpression SEMI alr_subexpression SEMI alr_subexpression CLOSEPAREN statement_block { //CHANGED FOR EXPRESSION INTERNAL TO STATEMENT BLOCK
		$$ = new node("for_statement", NONTERMINAL);
		$$->child = new node("FOR", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		$3->sibling = new node("SEMI", TERMINAL);
		$3->sibling->sibling = $5;
		$5->sibling = new node("SEMI", TERMINAL);
		$5->sibling->sibling = $7;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $7->sibling = closeparen;
		closeparen->sibling = $9;		
	}
	| FOR OPENPAREN alr_subexpression error alr_subexpression SEMI alr_subexpression CLOSEPAREN statement_block { $$ = new node("error", TERMINAL);yyerror("Possible missing semicolon in for"); }
	| FOR OPENPAREN alr_subexpression SEMI alr_subexpression error alr_subexpression CLOSEPAREN statement_block { $$ = new node("error", TERMINAL);yyerror("Possible missing semicolon in for"); }
	| FOR OPENPAREN alr_subexpression SEMI alr_subexpression SEMI alr_subexpression error statement_block { $$ = new node("error", TERMINAL); yyerror("Possible missing closing parenthesis in for"); }

return_statement: 
	RETURN SEMI {
		$$ = new node("return_statement", NONTERMINAL);
		$$->child = new node("RETURN", TERMINAL);
		node* semi = new node("SEMI", TERMINAL); $$->child->sibling = semi;
	}
	| RETURN alr_subexpression SEMI {
		$$ = new node("return_statement", NONTERMINAL);
		$$->child = new node("RETURN", TERMINAL);		
		$$->child->sibling = $2;
		node* semi = new node("SEMI", TERMINAL); $2->sibling = semi;
	}
	| RETURN error { $$ = new node("error", TERMINAL);yyerror("Missing semicolon with return"); }
	| RETURN alr_subexpression error {$$ = new node("error", TERMINAL); yyerror("Missing semicolon with return"); }

print_statement:
	PRINT OPENPAREN alr_subexpression CLOSEPAREN SEMI {
		$$ = new node("print_statement", NONTERMINAL);
		$$->child = new node("PRINT", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
		closeparen->sibling = new node("SEMI", TERMINAL);;
	}
	| PRINT error alr_subexpression CLOSEPAREN SEMI { $$ = new node("error", TERMINAL);yyerror("Possile missing open parenthesis"); }
	| PRINT OPENPAREN alr_subexpression error SEMI { $$ = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
	| PRINT OPENPAREN alr_subexpression CLOSEPAREN error { $$ = new node("error", TERMINAL);yyerror("Missing semicolon with print"); }

alr_subexpression:
	ID EQ alr_subexpression {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = new node("ID", VALUE);
		node* openparen = new node("EQ", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
	}	
	| supported_constant {$$ = new node("alr_subexpression", NONTERMINAL); $$->child = $1;}
	| ID {$$ = new node("alr_subexpression", NONTERMINAL); $$->child = new node("ID", VALUE);}
	| ID OPENPAREN id_list CLOSEPAREN  {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = new node("ID", VALUE);
		node* openparen = new node("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
	}
	| OPENPAREN alr_subexpression CLOSEPAREN {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = new node("OPENPAREN", TERMINAL);
		$$->child->sibling = $2;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;
	}
	| alr_subexpression ARITH alr_subexpression {}
	| OPENNEGATE alr_subexpression CLOSEPAREN {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = new node("OPENNEGATE", TERMINAL);
		$$->child->sibling = $2;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;
	}
	| alr_subexpression RELN alr_subexpression {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = $1;
		node* reln = new node("RELN", TERMINAL); $1->sibling = reln;
		reln->sibling = $3;
	}
	| alr_subexpression LOGICAL alr_subexpression {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = $1;
		node* reln = new node("LOGICAL", TERMINAL); $1->sibling = reln;
		reln->sibling = $3;
	}	
	| LOGICALNOT alr_subexpression {
		$$ = new node("alr_subexpression", NONTERMINAL);
		$$->child = new node("LOGICALNOT", TERMINAL);
		$$->child->sibling = $2;
	}
	| READ OPENPAREN CLOSEPAREN {
		$$ = new node("alr_subexpression", NONTERMINAL); 
		$$->child = new node("READ", TERMINAL);
		node* intconst = new node("OPENPAREN", VALUE); $$->child->sibling = intconst;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}
	| error EQ alr_subexpression { $$ = new node("error", TERMINAL);yyerror("Missing identifier name"); }
	| ID error alr_subexpression { $$ = new node("error", TERMINAL);yyerror("Possible missing equalty sign"); }
	| ID OPENPAREN id_list error { $$ = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
	| READ OPENPAREN error { $$ = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
	| READ error CLOSEPAREN { $$ = new node("error", TERMINAL);yyerror("Possible missing opening parenthesis"); }

id_list:
	ID COMMA id_list { $$ = new node("id_list", NONTERMINAL); $$->child = new node("ID", VALUE); node *comma = new node("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3; }
	| ID {$$ = new node("id_list", NONTERMINAL); $$->child = new node("ID", VALUE);}
	| %empty {$$ = new node("id_list", NONTERMINAL); $$->child = new node("EPSILON", TERMINAL); }
	| error COMMA id_list { $$ = new node("error", TERMINAL); yyerror("Missing identifier name"); }

supported_constant:
	INTCONST {$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("INTCONST", VALUE); }
	| BOOLCONST {$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("BOOLCONST", VALUE); }
	| OPENNEGATE INTCONST CLOSEPAREN {
		$$ = new node("supported_constant", NONTERMINAL); $$->child = new node("OPENNEGATE", TERMINAL);
		node* intconst = new node("INTCONST", VALUE); $$->child->sibling = intconst;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}

%%
int num_times = 2;
void yyerror(const char* err_msg)
{
	has_error = true;
	cout<<"Line "<<yylineno<<": "<<err_msg<<endl;
}

void print_tree(node *cur, vector<int>& ancestors, int parent)
{
	if(!cur) return;
	//for(int i = 0; i < ancestors.size(); i++) cout<<ancestors[i]<<" "; cout<<endl; 
	for (int k = 0; k < num_times; k++)
	{	
		for(int i = 0, j = 0; j < ancestors.size() && i < parent; i++)
		{
			if(i == ancestors[j]) j++, cout<<"|";
			else cout<<" ";
		}
		if(k!=num_times-1) cout<<endl;
	}
	if(ancestors.size()) cout<<"--+";
	cout<<cur->content<<endl;

	ancestors.push_back(parent);
	print_tree(cur->child, ancestors, parent+4);
	ancestors.pop_back();
	print_tree(cur->sibling, ancestors, parent);
}

int main()
{
	vector<int> print_vec;
	yydebug = 0;
	yyparse();
	if(!has_error)	print_tree(root, print_vec, 0);
	else cout<<"Compilation terminating with errors"<<endl;
}
