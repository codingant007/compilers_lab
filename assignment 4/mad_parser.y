%{
#include <bits/stdc++.h>
#include "node.h"

#define pretty_print_error yyerror
#define as_tree_n new node
#define lengthyy yyleng
#define textyy yytext
#define semicolon_error "Semicolon not found in variable declaration list :P"
#define comma_error "Comma not found in argument list :P"
#define identifier_error "Missing identifier in argument list"
#define semicolon_error_for "Semicolon not found in for"
#define type_error "Unknown type declaration"
#define semicolon_error_return "Semicolon not found with return :P"

using namespace std;

extern int yylex();
extern int lengthyy;
extern int yylineno;
extern char* textyy;

void pretty_print_error(const char*);


node::node(string con, node_type t)
{
	content = con;
	type = t;
	child = NULL;
	sibling = NULL;
	info = "";
}
node::node(const char* con, int t)
{
	content = (con);
	if(t == 0) type = NONTERM;
	else if(t == 1) type = TERM;
	else if(t == 2) type = VAL;
	info = "";
}

node *root;
bool has_error;

%}

%union{
	int dtype_int;
	bool dtype_bool;
	int opertype_int;
	node* node_el;
	char* node_con;
}

%start mad_program

%token <node_con> ID
%token COMMA
%token SEMI
%token OPENPAREN
%token CLOSEPAREN
%token OPENCURLY
%token CLOSECURLY
%token OPENSQUARE
%token CLOSESQUARE
%token OPENNEGATE
%token VOID
%token DTYPE_INT
%token DTYPE_BOOL
%token DTYPE_FLOAT
%token DTYPE_CHAR
%token <node_con> EQ
%token <node_con> ARITH
%token <node_con> RELN
%token <node_con> LOGICAL
%token <node_con> LOGICALNOT
%token IF
%token ELSE
%token WHILE
%token FOR
%token RETURN
%token PRINT
%token READ
%token <node_con> BOOLCONST
%token <node_con> INTCONST
%token <node_con> CHARCONST

%token NONTERMINAL 0
%token TERMINAL 1
%token VALUE 2

%type <node_el> mad_program supported_declarations variable_declarations function_declarations variable_definitions dtype argument_list statement_block
%type <node_el> variable_list statement_list supported_statement id_list supported_constant alr_subexpression
%type <node_el> if_statement else_statement while_statement return_statement var_decl var_use

%%

mad_program:
	supported_declarations { $$ = as_tree_n("mad_program", NONTERMINAL); $$->child = $1; root = $$;}
	| supported_declarations mad_program { $$ = as_tree_n("mad_program", NONTERMINAL); $$->child = $1; $1->sibling = $2; root = $$;}
	| error '\n' { pretty_print_error("Compilation terminating with errors"); root = NULL;}

supported_declarations:
	variable_declarations { $$ = as_tree_n("supported_declarations", NONTERMINAL); $$->child = $1; }
	| function_declarations {$$ = as_tree_n("supported_declarations", NONTERMINAL); $$->child = $1;}

variable_declarations:
	variable_definitions SEMI {$$ = as_tree_n("variable_declarations", NONTERMINAL); $$->child = $1; $1->sibling = as_tree_n("SEMI", TERMINAL);}
	| variable_definitions error { $$ = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error); }

variable_definitions:
	dtype var_decl {$$ = as_tree_n("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = $2;}
	| variable_definitions COMMA var_decl {$$ = as_tree_n("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = as_tree_n("COMMA", TERMINAL); $1->sibling->sibling = $3; }
	| variable_definitions error var_decl '\n' { $$ = as_tree_n("error", TERMINAL); pretty_print_error("Missing comma in definitions list"); }

dtype:
	DTYPE_INT {$$ = as_tree_n("DTYPE_INT", TERMINAL); /*$$->child = $1;*/}
	| DTYPE_BOOL {$$ = as_tree_n("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
	| DTYPE_FLOAT {$$ = as_tree_n("DTYPE_FLOAT", TERMINAL); /*$$->child = $1;*/}
	| DTYPE_CHAR {$$ = as_tree_n("DTYPE_CHAR", TERMINAL); /*$$->child = $1;*/}
	| error {$$ = as_tree_n("error", TERMINAL); pretty_print_error(type_error); }

function_declarations:
	dtype ID OPENPAREN argument_list CLOSEPAREN statement_block {$$ = as_tree_n("function_declarations", NONTERMINAL); $$->child = $1; node* id = as_tree_n("ID", VALUE); id->info = $2; $1->sibling = id; node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = $4; node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $4->sibling = closeparen; closeparen->sibling = $6; }
	| VOID ID OPENPAREN argument_list CLOSEPAREN statement_block {
		$$ = as_tree_n("function_declarations", NONTERMINAL);
		$$->child = as_tree_n("VOID", TERMINAL);
		node* id = as_tree_n("ID", VALUE); id->info = $2; $$->child->sibling = id;
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen;
		openparen->sibling = $4;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $4->sibling = closeparen;
		closeparen->sibling = $6;
	}

argument_list:
	dtype var_decl COMMA argument_list {
		$$ = as_tree_n("argument_list", NONTERMINAL); $$->child = $1;
		 $1->sibling = $2; //node* id = as_tree_n("ID", VALUE); id->info = $2;
		node* comma= as_tree_n("COMMA", TERMINAL); $2->sibling = comma; comma->sibling = $4; } |dtype ID {$$ = as_tree_n("argument_list", NONTERMINAL); $$->child = $1; node* id = as_tree_n("ID", VALUE); id->info = $2; $1->sibling = id;} |%empty /*epsilon production*/ {$$ = as_tree_n("function_declarations", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| dtype ID error argument_list { $$ = as_tree_n("error", TERMINAL); pretty_print_error(comma_error); }
	| dtype error COMMA argument_list { $$ = as_tree_n("error", TERMINAL); pretty_print_error(identifier_error); }

statement_block:
	OPENCURLY variable_list statement_list CLOSECURLY { $$ = as_tree_n("statement_block", NONTERMINAL); $$->child = as_tree_n("OPENCURLY", TERMINAL); $$->child->sibling = $2; $2->sibling = $3; $3->sibling = as_tree_n("CLOSECURLY", TERMINAL); }
	| OPENCURLY variable_list statement_list error { $$ = as_tree_n("error", TERMINAL); pretty_print_error("Possible missing semicolon in statement block"); }

variable_list:
	%empty /*epsilon production*/ {$$ = as_tree_n("variable_list", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| variable_declarations variable_list { $$ = as_tree_n("variable_list", NONTERMINAL); $$->child = $1; $1->sibling = $2; }

statement_list:
	%empty {$$ = as_tree_n("statement_list", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| supported_statement statement_list {$$ = as_tree_n("statement_list", NONTERMINAL); $$->child = $1; $1->sibling = $2;}

supported_statement:
	alr_subexpression SEMI {$$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; $1->sibling = as_tree_n("SEMI", TERMINAL);}
	| if_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| while_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| return_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| statement_block { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| alr_subexpression error { pretty_print_error("Possible missing semicolon with alr_subexpression"); $$ = as_tree_n("error", TERMINAL); }

if_statement:
	IF OPENPAREN alr_subexpression CLOSEPAREN statement_block else_statement { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		$$ = as_tree_n("if_statement", NONTERMINAL);
		$$->child = as_tree_n("IF", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
		closeparen->sibling = $5;
		$5->sibling = $6;
	}

else_statement:
	%empty {$$ = as_tree_n("else_statement", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| ELSE supported_statement {
		$$ = as_tree_n("else_statement", NONTERMINAL);
		$$->child = as_tree_n("ELSE", TERMINAL);
		$$->child->sibling = $2;
	}

while_statement:
	WHILE OPENPAREN alr_subexpression CLOSEPAREN {
		$$ = as_tree_n("while_statement", NONTERMINAL);
		$$->child = as_tree_n("WHILE", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
	}

return_statement:
	RETURN SEMI {
		$$ = as_tree_n("return_statement", NONTERMINAL);
		$$->child = as_tree_n("RETURN", TERMINAL);
		node* semi = as_tree_n("SEMI", TERMINAL); $$->child->sibling = semi;
	}
	| RETURN alr_subexpression SEMI {
		$$ = as_tree_n("return_statement", NONTERMINAL);
		$$->child = as_tree_n("RETURN", TERMINAL);
		$$->child->sibling = $2;
		node* semi = as_tree_n("SEMI", TERMINAL); $2->sibling = semi;
	}
	| RETURN error { $$ = as_tree_n("error", TERMINAL);pretty_print_error(semicolon_error_return); }
	| RETURN alr_subexpression error {$$ = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error_return); }

alr_subexpression:
	var_use EQ alr_subexpression {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = $1;
		node* openparen = as_tree_n("EQ", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
	}
	| supported_constant {$$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;}
	| var_use {$$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;}
	| ID OPENPAREN id_list CLOSEPAREN  {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = as_tree_n("ID", VALUE);$$->child->info = $1;
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
	}
	| OPENPAREN alr_subexpression CLOSEPAREN {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = as_tree_n("OPENPAREN", TERMINAL);
		$$->child->sibling = $2;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;
	}
	| alr_subexpression ARITH alr_subexpression {$$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1; $1->sibling= as_tree_n("ARITH", VALUE); $1->sibling->info = $2; $1->sibling->sibling = $3;}
	| OPENNEGATE alr_subexpression CLOSEPAREN {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = as_tree_n("OPENNEGATE", TERMINAL);
		$$->child->sibling = $2;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;
	}
	| alr_subexpression RELN alr_subexpression {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = $1;
		node* reln = as_tree_n("RELN", VALUE); reln->info = $2;$1->sibling = reln;
		reln->sibling = $3;
	}
	| alr_subexpression LOGICAL alr_subexpression {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = $1;
		node* reln = as_tree_n("LOGICAL", VALUE);reln->info=$2; $1->sibling = reln;
		reln->sibling = $3;
	}
	| LOGICALNOT alr_subexpression {
		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
		$$->child = as_tree_n("LOGICALNOT", VALUE); $$->child->info = "!";
		$$->child->sibling = $2;
	}
	| error EQ alr_subexpression { $$ = as_tree_n("error", TERMINAL);pretty_print_error("Missing identifier name"); }
	| var_use error alr_subexpression { $$ = as_tree_n("error", TERMINAL);pretty_print_error("Possible missing equalty sign"); }
	| var_use OPENPAREN id_list error { $$ = as_tree_n("error", TERMINAL);pretty_print_error("Possible missing closing parenthesis"); }

id_list:
	var_use COMMA id_list { $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1; node *comma = as_tree_n("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3; }
	| var_use {$$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1;}
	| %empty {$$ = as_tree_n("id_list", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| error COMMA id_list { $$ = as_tree_n("error", TERMINAL); pretty_print_error("Missing identifier name"); }
var_decl:
	ID {$$ = as_tree_n("decl_ID", NONTERMINAL); $$->info = "decl_ID";}
	| ID OPENSQUARE INTCONST CLOSESQUARE {$$ = as_tree_n("decl_ID[arr]", NONTERMINAL); $$->info = "decl_ID[arr]";}
var_use:
	ID {$$ = as_tree_n("use_ID", NONTERMINAL); $$->info = "use_ID";}
	| ID OPENSQUARE INTCONST CLOSESQUARE {$$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";}
supported_constant:
	INTCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;}
	| CHARCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("CHARCONST", VALUE); $$->child->info = $1;}
	| BOOLCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("BOOLCONST", VALUE); $$->child->info = $1;}
	| OPENNEGATE INTCONST CLOSEPAREN {
		$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("OPENNEGATE", TERMINAL);
		node* intconst = as_tree_n("INTCONST", VALUE); $$->child->sibling = intconst;intconst->info = $2;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}

%%
int num_times = 2;
void pretty_print_error(const char* err_msg)
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
	cout<<cur->content;
	if(cur->type == VAL) cout<<" [`"<<cur->info<<"']";
	cout<<endl;

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
