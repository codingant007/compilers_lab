%{
#include <bits/stdc++.h>
#include "node.h"

#define SIMPLE 0
#define ARRAY 1

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

enum TYPE {INT, CHAR, BOOL, ERR};

struct var_record {
    string name;
    int scope,var_type,dim,offset;
    TYPE type;
};


struct func_record
{
    TYPE return_type;
    string name;
    vector<var_record> param_list;
};

//Attributes Structure
struct attr
{
    TYPE type;
    int ival;   //For storing values of constants
    char cval;
    float fval;
    bool bval;

    string code; //Code gen by diff non-terminals
    vector<TYPE> types; //Types in parameter list
};


//GLOBAL VARIABLES FOR SEMANTIC ANALYSIS
int scope = 0;
int labelNumber = 0;
string data;
set<string> mips_name;
func_record *active_func_ptr, *call_name_ptr;

//Tree printing
node *root;
bool has_error;



map<string, func_record> func_table;
map<int, map<string, var_record> > sym_table;

void pretty_print_error(const char*);
var_record* get_record (string);
string get_mips_name (var_record*);
string load_mips_array(var_record* varRecord, int offSet);
string store_mips_array(var_record* varRecord, int offSet);
int cast (TYPE typeA, TYPE typeB, int is_up); // Return type: 0-> no casting possible 1-> typeA can be casted 2-> typeB can be casted

//Function Declarations

var_record* get_record(string name)
{
    for(int i=scope;i>=0;i--)
    {
        if (sym_table[i].find(name) != sym_table[i].end())
        {
            return &sym_table[i][name];
        }
    }
    return NULL;
}

string get_mips_name (var_record* varRecord)
{
    string mips_name;
    if (active_func_ptr == NULL){
      mips_name = "main";
    }
    else{
      mips_name = active_func_ptr -> name;
    }
    mips_name += "_";
    mips_name += varRecord-> name;
    mips_name += "_";
    stringstream s;
    s << scope;
    mips_name += s.str();
    return mips_name;
}

string get_label()
{
	stringstream s;
	s << labelNumber;
    string label =  "LABEL" + s.str() + ":\n";
    labelNumber++;
    return label;
}

string load_mips_array(var_record* varRecord, int offSet)
{
    string loadCode,loadType;
    int eleSize;
    if (varRecord->type == INT){
        eleSize = 4;
        loadType = "lw";
    }
    else if (varRecord -> type == BOOL || varRecord -> type == CHAR){
        eleSize = 1;
        loadType = "lb";
    }
    else{
        printf("Incorrect type of array in load.\n");
        exit(1);
    }
    stringstream s,s1;
    s << offSet;
    s1 << eleSize;
    loadCode = "mul $t1 " + s.str() + " " + s1.str() + "\n";
    loadCode += "la $t2 " + get_mips_name(varRecord) + "\n";
    loadCode += "add $t3 $t1 $t2 \n";
    loadCode += loadType + " $t0 ($t3) \n";
    return loadCode;
}

string store_mips_array(var_record* varRecord, int offSet)
{
    string storeCode,storeType;
    int eleSize;
    if (varRecord->type == INT){
        eleSize = 4;
        storeType = "sw";
    }
    else if (varRecord -> type == BOOL || varRecord -> type == CHAR){
        eleSize = 1;
        storeType = "sb";
    }
    else{
        printf("Incorrect type of array in store.\n");
        exit(1);
    }
    stringstream s,s1;
    s << offSet;
    s1 << eleSize;
    storeCode = "mul $t1 " + s.str() + " " + s1.str() + "\n";
    storeCode += "la $t2 " + get_mips_name(varRecord) + "\n";
    storeCode += "add $t3 $t1 $t2 \n";
    storeCode +=  storeType + " $t0 ($t3)\n";
    return storeCode;
}

string load_mips_id(var_record* varRecord)
{
    string loadCode,loadType;
    if (varRecord->type == INT){
        loadType = "lw";
    }
    else if (varRecord->type == BOOL || varRecord-> type == CHAR){
        loadType = "lb";
    }
    else{
        printf("Incorrect type of ID in load.\n");
        exit(1);
    }
    loadCode = loadType + " $t0 " + get_mips_name(varRecord) + "\n";
    return loadCode;
}

string store_mips_id (var_record* varRecord)
{
    string storeCode,storeType;
    if (varRecord->type == INT){
        storeType = "sw";
    }
    else if (varRecord->type == BOOL || varRecord->type == CHAR){
        storeType = "sb";
    }
    else{
        printf("Incorrect type of ID in load.\n");
        exit(1);
    }
    storeCode = storeType + " $t0 " + get_mips_name(varRecord) + "\n";
    return storeCode;
}

string intToBool()
{
    string boolCode = "srl $t0 0x1F\n";
    boolCode += "andi $t1 $t0 0x1\n";
    boolCode += "addi $t0 $t1 0x1\n";
    boolCode += "andi $t1 $t0 0x1\n";
    boolCode += "ori $t0 $t1 0x0\n";
    return boolCode;
}

int cast (TYPE typeA, TYPE typeB, int is_up)
{
    if (typeA == typeB)
        return 0;
    if (is_up == 1){
        /* char can be converted to int, bool can be converted to int */
        if ( (typeA == CHAR || typeA == BOOL) && typeB == INT)
        {
            return 1;
        }
        else if ((typeB == CHAR || typeB == BOOL) && typeA == INT){
            return 2;
        }
        return -1;
    }
    else{
        //int can be converted to bool
        if ( typeA == BOOL && typeB == INT ){
            return 2;
        }
        else if (typeA == INT && typeB == BOOL){
            return 1;
        }
        return -1;
    }
}

int are_comparable(TYPE typeA, TYPE typeB)
{
    //Bool-Char, Bool-Bool combinations can't be compared
    if ( (typeA == CHAR && typeB == BOOL) || (typeA == BOOL && typeB == CHAR) )
        return false;
    else return true;
}

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

%}

%union{
	struct attr* attr_el;
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
%type <node_el> variable_list statement_list supported_statement if_statement else_statement while_statement return_statement
%type <attr_el> var_decl var_use id_list supported_constant alr_subexpression lhs

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
	dtype var_decl {cout<<"dtype var_decl"<<endl; $$ = as_tree_n("variable_definitions", NONTERMINAL); $$->child = $1;}// $1->sibling = $2;}
	| variable_definitions COMMA var_decl {$$ = as_tree_n("variable_definitions", NONTERMINAL); $$->child = $1; $1->sibling = as_tree_n("COMMA", TERMINAL); } //$1->sibling->sibling = $3; }
	| variable_definitions error var_decl '\n' { $$ = as_tree_n("error", TERMINAL); pretty_print_error("Missing comma in definitions list"); }

dtype:
	DTYPE_INT {$$ = as_tree_n("DTYPE_INT", TERMINAL); /*$$->child = $1;*/}
	| DTYPE_BOOL {$$ = as_tree_n("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
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
		/* $1->sibling = $2; //node* id = as_tree_n("ID", VALUE); id->info = $2;
		node* comma= as_tree_n("COMMA", TERMINAL); $2->sibling = comma; comma->sibling = $4; } |dtype ID {$$ = as_tree_n("argument_list", NONTERMINAL); $$->child = $1; node* id = as_tree_n("ID", VALUE); id->info = $2; $1->sibling = id;} */
  }
  |%empty /*epsilon production*/ {$$ = as_tree_n("function_declarations", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
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
	alr_subexpression SEMI {cout<<$1->code<<endl; $$ = as_tree_n("supported_statement", NONTERMINAL);}// $$->child = $1; $1->sibling = as_tree_n("SEMI", TERMINAL);}
	| if_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| while_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| return_statement { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| statement_block { $$ = as_tree_n("supported_statement", NONTERMINAL); $$->child = $1; }
	| alr_subexpression error { pretty_print_error("Possible missing semicolon with alr_subexpression"); $$ = as_tree_n("error", TERMINAL); }

if_statement:
	IF OPENPAREN alr_subexpression CLOSEPAREN statement_block else_statement { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		$$ = as_tree_n("if_statement", NONTERMINAL);
		$$->child = as_tree_n("IF", TERMINAL);
		/*node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
		closeparen->sibling = $5;
		$5->sibling = $6;*/
	}

else_statement:
	%empty {$$ = as_tree_n("else_statement", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL); }
	| ELSE supported_statement {
		$$ = as_tree_n("else_statement", NONTERMINAL);
		$$->child = as_tree_n("ELSE", TERMINAL);
		$$->child->sibling = $2;
	}

while_statement:
	WHILE OPENPAREN alr_subexpression CLOSEPAREN statement_block {
		$$ = as_tree_n("while_statement", NONTERMINAL);
		$$->child = as_tree_n("WHILE", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		/*openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;*/
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
		/*$$->child->sibling = $2;
		node* semi = as_tree_n("SEMI", TERMINAL); $2->sibling = semi;*/
	}
	| RETURN error { $$ = as_tree_n("error", TERMINAL);pretty_print_error(semicolon_error_return); }
	| RETURN alr_subexpression error {$$ = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error_return); }

alr_subexpression:
	lhs EQ alr_subexpression {
        $$= new attr();
        //Semantic
        if ( cast($1->type, $3->type, 0) <  0)
        {
          $$->type = ERR;
	        $$->ival = -1;
	        pretty_print_error("Semantic Error: Incompatible types in equality assignment");
	        has_error = true;
        }


        //Code Generation
        if (!has_error)
        {
            var_record *lhsRecord = get_record($1->code);
            $$ -> code = $3->code;
            cout << $1 ->type << "\t" << $3->type <<"\t" << cast($1->type,$3->type,0) << endl;
            if ( cast($1->type, $3->type, 0) == 2)
            {
                //CodeGen - no other casting test needed because only allowed downcast is from int to bool
                $$->code += "#Casting of RHS";
                $$->code += intToBool();
            }
            else{
              if ($1->ival == -1 && $1->type != ERR ){
                  //ID

                  $$->code += store_mips_id(lhsRecord);

              }
              else if ($1->type != ERR){
                  //ID[const]
                  $$->code += store_mips_array(lhsRecord,$1->ival);
              }
            }


        }

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* openparen = as_tree_n("EQ", TERMINAL); $$->child->sibling = openparen;
// 		openparen->sibling = $3;
	}
	| supported_constant {
        $$= new attr();
	   //Semantic analyses - Nothing to check
	   $$ = $1;

	   //CodeGen - Nothing to do

	   // Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
	| var_use {
        $$= new attr();

	   //Semantic analyses - Nothing to check
	   $$ = $1;

	   //CodeGen - Nothing to do

	   //Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
	| ID OPENPAREN id_list CLOSEPAREN  { //Function call

          $$= new attr();
        //Semantic analyses
        if ( func_table.count($1) == 0 )
        {
            $$->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Function not declared");
        }
        else if ( func_table[$1].param_list.size() != $3->types.size() )
        {
            $$->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Parameter list length mismatch");
        }
        else
        {
            for ( int i = 0; i < $3->types.size(); i++ )
            {
                if ( $3->types[i] != func_table[$1].param_list[i].type )
                {
                    has_error = true;
                    $$->type = ERR;
                    pretty_print_error ("Semantic error: Parameter type mismatch in parameter list");
                }
            }
        }

        //CodeGeneration
        // $$->type = func_table[$1].return_type;
        //We will implement code generation for functions in next stage.


//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("ID", VALUE);$$->child->info = $1;
// 		node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
// 		openparen->sibling = $3;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
	}
	| OPENPAREN alr_subexpression CLOSEPAREN {
        $$= new attr();
		//Semantic Analyses - no checks needed
		//CodeGen
		$$ = $2;

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("OPENPAREN", TERMINAL);
// 		$$->child->sibling = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;

	}
	| alr_subexpression
      {
	    //Semantic Analyses
	    //Code Generation
      $<attr_el>$ = new attr();
	        if (!has_error){
	            $<attr_el>$->code = ($<attr_el>0)->code;
    	        $<attr_el>$->code += "sw $t0 0($s0) \n";
    	        $<attr_el>$->code += "addiu $sp $sp -4\n";
	        }
	    }

	    ARITH alr_subexpression {
        $$ = new attr();
	    //Semantic Analyses
	    if (cast($1->type, $4->type, 1) < 0)
	    {
	        has_error = 1;
	        $$->type = ERR;
	        pretty_print_error ("Semantic error: Arithmetic operation on incompatible types");
	    }

	    //Code Generation
	    if (!has_error){
	        $$->code = $<attr_el>2->code;
	        $$->code += $4->code;
            $$->code += "lw $t1 4($sp)\n";
            $$->code += "addiu $sp $sp 4\n";
	        if ($3 == "+"){
	            $$->code += "add $t0 $t0 $t1\n";
	        }
	        else if ($3 == "-"){
	            $$->code += "sub $t0 $t1 $t0\n";
	        }
	        else if ($3 == "*"){
	            $$->code += "mul $t0 $t0 $t1\n";
	        }
	        else if ($3 == "/"){
	            $$->code += "div $t0 $t1 $t0\n";
	        }
	    }

	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL);
	   // $$->child = $1; $1->sibling= as_tree_n("ARITH", VALUE);
	   // $1->sibling->info = $2;
	   // $1->sibling->sibling = $3;
	}
	| OPENNEGATE alr_subexpression CLOSEPAREN {
        $$= new attr();
		//Semantic analyses - no checks
		$$ = $2;
		//Code gen
		if(!has_error){
		    $$->code += "neg $t0 $t0 \n";
		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("OPENNEGATE", TERMINAL);
// 		$$->child->sibling = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;

	}
	| alr_subexpression
	    {
	    //Semantic Analyses - no checks
	    //Code Generation
      $<attr_el>$ = new attr();
	        if (!has_error){
	            $<attr_el>$->code = ($<attr_el>0)->code;
    	        $<attr_el>$->code += "sw $t0 0($s0) \n";
    	        $<attr_el>$->code += "addiu $sp $sp -4\n";
	        }
	    }

	    RELN alr_subexpression {
        $$ = new attr();
	    //Semantic Analyses
	    if ( !are_comparable($1->type, $4->type) )
	    {
	        has_error = true;
	        $$->type = ERR;
	        pretty_print_error ("Semantic error: Relational operator between incompatible types");
	    }

		//Code Generation
		if (!has_error){
		    $$->type = BOOL;
		    $$->code = $<attr_el>2->code;
	        $$->code += $4->code;
            $$->code += "lw $t1 4($sp)\n";
            $$->code += "addiu $sp $sp 4\n";
	        if ($3 == "=="){
	            $$->code += "seq $t0 $t1 $t0\n";
	        }
	        else if ($3 == "<"){
	            $$->code += "slt $t0 $t1 $t0\n";
	        }
	        else if ($3 == "<="){
	            $$->code += "sle $t0 $t1 $t0\n";
	        }
	        else if ($3 == ">"){
	            $$->code += "sgt $t0 $t1 $t0\n";
	        }
	        else if ($3 == ">="){
	            $$->code += "sge $t0 $t1 $t0\n";
	        }
	        else if ($3 == "!="){
	            $$->code += "seq $t0 $t1 $t0\n";
	            $$->code += "xori $t0 $t0 0x1\n";
	        }

		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* reln = as_tree_n("RELN", VALUE); reln->info = $2;$1->sibling = reln;
// 		reln->sibling = $3;
	}

	| alr_subexpression
	    {
        $<attr_el>$ = new attr();
	    //Semantic Analyses - no checks
	    if ($<attr_el>$->type == CHAR){
	        has_error = true;
	    }
	    //Code Generation

	        if (!has_error){
	            $<attr_el>$->code = ($<attr_el>0)->code;
	            if ($<attr_el>$->type == INT){
	                $<attr_el>$->code += intToBool();
	            }
    	        $<attr_el>$->code += "sw $t0 0($s0) \n";
    	        $<attr_el>$->code += "addiu $sp $sp -4\n";
	        }
	    }
	  LOGICAL alr_subexpression {
        $$ = new attr();
        //Semantic Analyses
        if ( ($1->type == CHAR || $4->type == CHAR) )
        {
            has_error = true;
            $$->type = ERR;
            pretty_print_error ("Semantic Error: Logical comparison with a CHAR type");
        }


        //Code Generation
        if (!has_error){
            $$->type = BOOL;
            $$->code = $<attr_el>2->code;
	        $$->code += $4->code;
	        if ($4->type == INT){
	            $$->code += intToBool();
	        }
            $$->code += "lw $t1 4($sp)\n";
            $$->code += "addiu $sp $sp 4\n";

            if ($3 == "&&"){
                $$->code += "and $t0 $t0 $t1\n";
            }
            else if ($3 == "||"){
                $$->code += "or $t0 $t0 $t1\n";
            }

        }

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* reln = as_tree_n("LOGICAL", VALUE);reln->info=$2; $1->sibling = reln;
// 		reln->sibling = $3;
	}
	| LOGICALNOT alr_subexpression {
    $$  = new attr();
		if ($2->type == CHAR)
		{
		    has_error = true;
		    $$->type = ERR;
            pretty_print_error ("Semantic Error: Logical NOT on CHAR type");
		}

		//Code Generation
		if (!has_error){
		    $$->code = $2->code;
		    if ($2->type == INT){
		        $$->code+= intToBool();
		    }
		    $$->code += "xori $t0 $t0 0x1\n";
		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("LOGICALNOT", VALUE); $$->child->info = "!";
// 		$$->child->sibling = $2;

	}

	| error EQ alr_subexpression { $$ = new attr(); $$->type = ERR; pretty_print_error("Missing identifier name"); }
	| var_use error alr_subexpression {$$ = new attr(); $$->type = ERR; pretty_print_error("Possible missing equalty sign"); }
	| var_use OPENPAREN id_list error { $$ = new attr(); $$->type = ERR; pretty_print_error("Possible missing closing parenthesis"); }

id_list:
	id_list COMMA var_use {
	   //Semantic Analyses
     $$ = new attr();
	   $$ = $1;
	   $$->types.push_back($3->type);

	   //CodeGen

	   //Tree stuff
	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1; node *comma = as_tree_n("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3;
	}
	| var_use {
      $$ = new attr();
	   //Semantic Analyses
	   $$ = $1;
	   $$->types.push_back($1->type);

	   //CodeGen

	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1;
	}
	| %empty {
      $$ = new attr();
	   //Semantic Analyses  - no checks needed
	   //CodeGen - nothing to do

	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL);
	}

	| error COMMA id_list {
      $$ = new attr();
	    $$->type = ERR; pretty_print_error("Missing identifier name");
	}

lhs:
    ID {
	    //Semantic Analyses
      $$ = new attr();
	    var_record* id_rec = get_record($1);
	    if ( id_rec == NULL )
	    {
	        $$->type = ERR;
	        $$->ival = -1;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: Array accessed as scalar.");
	        has_error = true;
	    }
	    else
	    {
	        $$->type = id_rec->type;
	        $$->code = $1;
	        $$->ival = -1;
	    }
	    //CodeGen
	    //No codegen

	    //Tree-related stuff
	    // $$ = as_tree_n("use_ID", NONTERMINAL); $$->info = "use_ID";
	}
	| ID OPENSQUARE INTCONST CLOSESQUARE {
        $$ = new attr();
        //Semantic Analyses
        var_record* id_rec = get_record($1);
        if ( id_rec == NULL )
        {
            $$->type = ERR;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: Scalar accessed as array.");
	        has_error = true;
	    }
	    else
	    {
	        int iconst = atoi($3);
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            $$->type - ERR;
	            pretty_print_error("Semantic Error: Array dimensions violated.");
	            has_error = true;
	        }
	        $$->type = id_rec->type;
	        $$->ival = iconst;
	        $$->code = $1;
	    }

        //CodeGen
        //No code generated in this production

        //Tree-related stuff
	    // $$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";
	}

var_decl:
	ID {
	   // Semantic
    $$ = new attr();
     if( sym_table.count(scope) > 0 && sym_table[scope].count($1) != 0 )
	   {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: ID redeclaration in same scope.");
	        has_error = true;
	   }
	   else
	   {
            var_record id_rec;
            id_rec.var_type = SIMPLE;
            id_rec.name = $1;
            id_rec.scope = scope;
            id_rec.dim = 0;
            id_rec.type = $$->type;
            if (!sym_table.count(scope))
            {
              map <string,var_record> temp;
              temp[$1] = id_rec;
              sym_table[scope] = temp;
            }
            else{
              sym_table[scope][$1] = id_rec;
            }
            // cout << $1 << " inserted." << endl;
	   }

	   //CodeGen
	   mips_name.insert(get_mips_name(&sym_table[scope][$1])); //For adding to data declarations

       //Tree stuff
	   // $$ = as_tree_n("decl_ID", NONTERMINAL); $$->info = "decl_ID";
	}
	| ID OPENSQUARE INTCONST CLOSESQUARE {
      $$ = new attr();
	   //Semantic
	   if( sym_table.count(scope) > 0 && sym_table[scope].count($1) != 0 )
	   {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: ID redeclaration in same scope.");
	        has_error = true;
	   }
	   else
	   {
            var_record id_rec;
            id_rec.var_type = ARRAY;
            id_rec.name = $1;
            id_rec.scope = scope;
            id_rec.dim = atoi($3);
            id_rec.type = $$->type;
            sym_table[scope][$1] = id_rec;
	   }

       //CodeGen
	   mips_name.insert(get_mips_name(&sym_table[scope][$1])); //For adding to data declarations

	   //Tree stuff
	   // $$ = as_tree_n("decl_ID[arr]", NONTERMINAL); $$->info = "decl_ID[arr]";
	}

var_use:
	ID {
	    //Semantic Analyses
      $$ = new attr();
	    var_record* id_rec = get_record($1);
	    if ( id_rec == NULL )
	    {
	        $$->type = ERR;
	        $$->ival = -1;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: Array accessed as scalar.");
	        has_error = true;
	    }
	    else
	    {
        cout << $1 << id_rec->type <<endl;
	        $$->type = id_rec->type;
	        $$->ival = -1;
	    }

	    //CodeGen
	    if (!has_error){
	        $$->code = load_mips_id( get_record($1) );
	    }


	    //Tree-related stuff
	    // $$ = as_tree_n("use_ID", NONTERMINAL); $$->info = "use_ID";
	}
	| ID OPENSQUARE INTCONST CLOSESQUARE {

        //Semantic Analyses
        $$ = new attr();
        var_record* id_rec = get_record($1);
        if ( id_rec == NULL )
        {
            $$->type = ERR;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        $$->type = ERR;
	        pretty_print_error("Semantic Error: Scalar accessed as array.");
	        has_error = true;
	    }
	    else
	    {
	        int iconst = atoi($3);
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            $$->type - ERR;
	            pretty_print_error("Semantic Error: Array dimensions violated.");
	            has_error = true;
	        }
	        $$->type = id_rec->type;
	        $$->ival = iconst;


	    }

        //CodeGen
        if (!has_error){
            $$->code = load_mips_array( get_record($1),atoi($3));
        }

        //Tree-related stuff
	    // $$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";
	}

supported_constant:
<<<<<<< HEAD
	INTCONST {

	    //Semantic Analyses
        $$ = new attr();
        $$->ival =  atoi($1);
        $$->type = INT;

	    //CodeGen
	    //No codegen assoc with this production

	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;
=======
	INTCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;}
	| CHARCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("CHARCONST", VALUE); $$->child->info = $1;}
	| BOOLCONST {$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("BOOLCONST", VALUE); $$->child->info = $1;}
	| OPENNEGATE INTCONST CLOSEPAREN {
		$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("OPENNEGATE", TERMINAL);
		node* intconst = as_tree_n("INTCONST", VALUE); $$->child->sibling = intconst;intconst->info = $2;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
>>>>>>> 6198c678c8bf261b975b9b3d9c8028944fad926b
	}
	| CHARCONST {
	    //Semantic Analyses
        $$ = new attr();
        $$->cval =  *($1);
        $$->type = CHAR;
	    //CodeGen

	    //No codegen assoc with this production

	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;
	}
	| BOOLCONST {
	    //Semantic Analyses
      $$ = new attr();
	    if( !strcmp($1, "true") )
	        $$->bval = 1;
	    else
	        $$->bval = 0;
	    $$->type = BOOL;

        //Semantic Analyses
	    //CodeGen
	    //No codegen assoc with this production

	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("BOOLCONST", VALUE); $$->child->info = $1;
	}
	| OPENNEGATE INTCONST CLOSEPAREN {

	    //Semantic Analyses
      $$ = new attr();
	    $$->ival = atoi($2);
	    $$->ival = -($$->ival);
	    $$->type = INT;

	    //CodeGen
	    //No codegen assoc with this production

		//Tree-related stuff
// 		$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("OPENNEGATE", TERMINAL);
// 		node* intconst = as_tree_n("INTCONST", VALUE); $$->child->sibling = intconst;intconst->info = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
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
	if(!has_error)	cout<<"hurray no error"<<endl;
	else cout<<"Compilation terminating with errors"<<endl;
}
