%{
#include <bits/stdc++.h>
#include "node.h"

#define SIMPLE 0
#define ARRAY 1
#define INT_SIZE 4
#define BOOL_SIZE 1
#define CHAR_SIZE 1

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

enum TYPE {VOIDF, INT, CHAR, BOOL, ERR};

struct var_record {
    bool is_param;
  	string name;
    int scope,var_type,dim,offset;
    TYPE type;
};


struct func_record
{
    TYPE return_type;
    string name;
    vector<var_record> param_list;
    int paramlist_size;
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
    string label; // Useful for if-else-operation
    vector<TYPE> types; //Types in parameter list
};


//GLOBAL VARIABLES FOR SEMANTIC ANALYSIS
int scope = 0;
int labelNumber = 0;
string data;
vector< var_record > mips_name;
func_record *active_func_ptr, *call_name_ptr;
vector<var_record*> call_param_list;

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

void copy_attr( struct attr* A,struct attr* B){
  A->type = B->type;
  A->ival = B->ival;   //For storing values of constants
  A->cval = B->cval;
  A->fval = B->fval;
  A->bval = B->bval;

  A->code = B->code; //Code gen by diff non-terminals
  A->label = B->label; // Useful for if-else-operation

}



var_record* get_record(string name)
{
    for(int i=scope;i>=2;i--)
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

    stringstream s;
    s << "_" << varRecord->type << "_" << scope ;
    mips_name += s.str();
    return mips_name;
}

string get_label()
{
    //Only returns the name of the label
	stringstream s;
	s << labelNumber;
    string label =  "LABEL" + s.str();
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

%type <attr_el> mad_program supported_declarations variable_declarations function_declarations variable_definitions dtype argument_list statement_block
%type <attr_el> variable_list statement_list supported_statement if_statement else_statement while_statement return_statement
%type <attr_el> var_decl var_use id_list supported_constant alr_subexpression lhs func_name comma_rule

%%

mad_program:
	supported_declarations {
  	$$ = new attr(); copy_attr($$,$1);
    cout << $$->code;
  }
	| supported_declarations mad_program {
  	$$ = new attr(); copy_attr($$,$1);
    $$->code += $2->code;
    cout << $$->code;
  }
	| error '\n' { pretty_print_error("Compilation terminating with errors"); root = NULL;}

supported_declarations:
	variable_declarations {
  	$$ = new attr(); copy_attr($$,$1);
  }
	| function_declarations {
  	$$ = new attr(); copy_attr($$,$1);
  }

variable_declarations:
	variable_definitions SEMI {
    $$ = new attr(); copy_attr($$,$1);
  }
//	| variable_definitions error { $$ = new attr(); $$->type = ERR; pretty_print_error(semicolon_error); }

variable_definitions:
	dtype var_decl {
    $$ = new attr();
  	if (has_error)
    {
    	$$->type = ERR;
      $$->code = "";
    }
  	else
    {
    	$$->code = $2->code;
      $$->type = $1->type;

    }

}
	| variable_definitions comma_rule var_decl {
    $$ = new attr();
  	if (has_error)
    {
    	$$->type = ERR;
      $$->code = "";
    }
  	else
    {
      $3->type = $2->type;
    	$$->code = $1->code + $3->code;
      $$->type = $2->type;
    }
  	}
	| variable_definitions error var_decl '\n' { $$ = new attr(); $$->type = ERR; pretty_print_error("Missing comma in definitions list"); }

comma_rule:
  COMMA {$$ = new attr(); $$->type = ($<attr_el>0)->type; }

dtype:
	DTYPE_INT {
    $$ = new attr();
    $$->type = INT;
    $$->ival = INT_SIZE;
  }
	| DTYPE_BOOL {
    $$ = new attr();
    $$->type = BOOL;
    $$->ival = BOOL_SIZE;
  }
	| DTYPE_CHAR {
  	$$ = new attr();
    $$->type = CHAR;
    $$->ival = CHAR_SIZE;
  }
	// | error {
  //   $$ = new attr();
  //   $$->type = ERR;
  //   $$->ival = -1;
  //   pretty_print_error(type_error);
  // }

function_declarations:
	dtype func_name  OPENPAREN { scope = 1; } argument_list CLOSEPAREN statement_block {
        //Scope Consideration
        scope = 0;
    		int cur_offset = 0;
        //Semantic
        $$ = new attr();
    		active_func_ptr->return_type = (TYPE)$1->ival;
    		for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
        {
        	switch(active_func_ptr->param_list[i].type)
          {
          	case INT: active_func_ptr->param_list[i].offset = cur_offset + INT_SIZE;
            				cur_offset += INT_SIZE;
            	break;
            default: active_func_ptr->param_list[i].offset = cur_offset + BOOL_SIZE;
            				cur_offset += BOOL_SIZE;
            break;
          }
        }
    		active_func_ptr->paramlist_size = cur_offset; //Setting paramlist size
        //Code Generation
        $$->code = $2->label + ":\n";
        //Store return $ra to stack and set frame pointer to $ra
        $$->code += "sw $ra 0($sp)\n";
        $$->code += "move $fp $sp \n";
    		$$->code += "addiu $sp $sp -4\n";
    		$$->code += $7->code;
    		$$->code += "move $sp $fp\n";
    		$$->code += "lw $ra 0($fp)\n";          // $ra <- 0($fp)
    		$$->code += "addiu $sp $sp 4\n";
    		//Pop parameters
    		stringstream s;
    		s << active_func_ptr->paramlist_size;
    		$$->code += "addiu $sp $sp " + s.str() + "\n";
    		$$->code += "jr $ra\n";
    		//Semantic again
    		active_func_ptr = NULL;
	}
	| VOID func_name { scope = 1; } OPENPAREN argument_list CLOSEPAREN statement_block {
		//Scope Consideration
		scope = 0;

		//Semantic
    $$ = new attr();
    //Scope Consideration
        scope = 0;
    		int cur_offset = 0;
        //Semantic
        $$ = new attr();
    		active_func_ptr->return_type = VOIDF;
    		for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
        {
        	switch(active_func_ptr->param_list[i].type)
          {
          	case INT: active_func_ptr->param_list[i].offset = cur_offset + INT_SIZE;
            				cur_offset += INT_SIZE;
            	break;
            default: active_func_ptr->param_list[i].offset = cur_offset + BOOL_SIZE;
            				cur_offset += BOOL_SIZE;
            break;
          }
        }
    		active_func_ptr->paramlist_size = cur_offset; //Setting paramlist size
    //Code Generation
    		$$->code = $2->label + ":\n";
        //Store return $ra to stack and set frame pointer to $ra
        $$->code += "sw $ra 0($sp) \n";
        $$->code += "move $fp $sp \n";
    		$$->code += "addiu $sp $sp -4\n";
    		$$->code += $7->code;
    		$$->code += "move $sp $fp\n";
    		$$->code += "lw $ra 0($fp)\n";          // $ra <- 0($fp)
    		$$->code += "addiu $sp $sp 4\n";
    		//Pop parameters
    		stringstream s;
    		s << active_func_ptr->paramlist_size;
    		$$->code += "addiu $sp $sp " + s.str() + "\n";
    		$$-> code += "jr $ra\n";

    		//Semantic again
    		active_func_ptr = NULL;
	}
func_name:
	ID {
    $$ = new attr();
		if (func_table.count($1) > 0)
    {
    	has_error = true;
      pretty_print_error ("Semantic error: Redeclaration of function name");
    }
    else
    {
    	func_record f_temp;
      func_table[$1] = f_temp;
      //Setting active_func_ptr
      active_func_ptr = &func_table[$1];
      active_func_ptr -> name = $1;
    }
    $$->type = VOIDF;
    $$->label = $1;
  }
argument_list:
		 dtype var_decl COMMA argument_list {
      //Nothing to do - check for errors and proceed
      $$ = new attr();
      if (has_error)
      {
        $$->type = ERR;
        $$->code = "";
      }
      else
      {
        $$->code = $1->code + $2->code;
        $$->ival = $4->ival + ($1->ival);
      }
  }
  |%empty /*epsilon production*/ {
    //Nothing to do
    $$ = new attr();
    $$->code = "";
    $$->ival = 0;
  }
	| dtype ID error argument_list {
  	has_error = true;
    pretty_print_error (comma_error);
    $$ = new attr();
    $$->type = ERR;
  }
	| dtype error COMMA argument_list {
  	has_error = true;
    pretty_print_error (identifier_error);
    $$ = new attr();
    $$->type = ERR;
  }

statement_block:
opencurly variable_list statement_list CLOSECURLY {
		$$ = new attr();

  	if (has_error)
    {
    	$$->type = ERR;
      $$->code = "";
    }
  	else
    {
    	$$->code = $2->code + $3->code;
    }
  	//Scope resolution
    map<string, var_record> temp;
  	sym_table[scope] = temp;
  	scope--;
  }
	// | OPENCURLY variable_list statement_list error {
  // 	has_error = true;
  //   pretty_print_error (" Possible missing closing brace in statement block ");
  //   $$ = new attr();
  //   $$->type = ERR;
  // }

opencurly:
  OPENCURLY { scope++; }

variable_list:
	%empty /*epsilon production*/ {
  	//Nothing to do
    $$ = new attr();
    $$->code = "";

  }
	| variable_declarations variable_list {
    //Nothing to do - check for error in further productions
    $$ = new attr();

    if (has_error)
    {
      $$->type = ERR;
      $$->code = "";
    }
    else
      $$->code = $1->code + $2->code;
  }


statement_list:
	%empty {
    //Nothing to do
    $$ = new attr();
    $$->code = "";

  }
	| supported_statement statement_list {
    //Semantic Analyses - chaining
    $$ = new attr();
    if (!has_error)
    {
    	$$->code = $1->code + "\n" + $2->code;
    }
    else
    {
      $$->type = ERR;
      $$->code = "";
    }
  }

supported_statement:
	alr_subexpression SEMI {
    //Nothing to do
    $$ = new attr(); copy_attr($$,$1);
  }
	| if_statement {
    //Nothing to do
    $$ = new attr(); copy_attr($$,$1);
  }
	| while_statement {
    //Nothing to do
    $$ = new attr(); copy_attr($$,$1);
  }
	| return_statement {
    //Nothing to do
    $$ = new attr(); copy_attr($$,$1);
  }
	| statement_block {
    //Nothing to do
    $$ = new attr(); copy_attr($$,$1);
  }
	| alr_subexpression error { $$ = new attr(); $$->type = ERR; has_error = true; pretty_print_error("Possible missing semicolon with alr_subexpression"); }

if_statement:
	IF OPENPAREN alr_subexpression CLOSEPAREN statement_block else_statement {
		$$ = new attr();
		if ($3->type != BOOL)
    {
    	has_error = true;
      $$->type = ERR;
      pretty_print_error ("Incompatible types: Expected boolean expression in if condition");
    }
		//Code Generation
	    string startElse,endElse;
	    startElse = get_label();
	    endElse = get_label();

	    $$ -> code = $3-> code;
	    $$ -> code += "li $t1 0x1\n";
	    $$ -> code += "bne $t0 $t1 " + startElse + "\n";
	    $$ -> code += $5 ->code;
	    $$ -> code += "b " + endElse + "\n";
	    $$ -> code += startElse + ":\n";
	    $$ -> code += $6->code;
	    $$ -> code += endElse + ":\n";

	}

else_statement:
	%empty {
    	$$ = new attr();
    	//Semantic Analyses - no check
    	//CodeGen
	    $$-> code = "\n";
	}
	| ELSE statement_block {
		$$ = new attr();
    //Semantic Analyses - no check
		//Code Generation
		$$->code = $2->code;

	}

while_statement:
	WHILE OPENPAREN alr_subexpression CLOSEPAREN statement_block {
    $$ = new attr();
    //Semantic Analyses
    if ($3->type != BOOL)
    {
    	has_error = true;
      $$->type = ERR;
      pretty_print_error ("Incompatible types: Expected boolean expression in while condition");
    }

		//Code Generation
    if (!has_error)
    {
      string startWhile = get_label();
      string endWhile = get_label();
      //Start While loop
      $$->code = startWhile + ":\n";
      //Evaluate alr_subexpression
      $$->code += $3->code;
      $$->code += "li $t1 0x1\n";
      $$->code += "bne $t0 $t1 " + endWhile + "\n";
      //Perform main Statement Block
      $$->code += $5->code;
      $$->code += "b " + startWhile + "\n";
      //FinishWhile
      $$->code += endWhile + ":\n";
    }
	}

return_statement:
	RETURN SEMI {
    $$ = new attr();
    //Semantic Analyses
		if ( active_func_ptr->return_type != VOIDF )
    {
      		$$->type = ERR;
          has_error = true;
          pretty_print_error("Incompatible types: function return type not void");
    }

    //Code Generation
    //Nothing to do

	}
	| RETURN alr_subexpression SEMI {
    	$$ = new attr();
    	//Semantic Analyses
    	$$ = $2;
    	int downcast_needed = cast(active_func_ptr->return_type, $2->type, 0);
      if ( active_func_ptr->return_type != $2->type )
      {
        if (downcast_needed < 0 || (downcast_needed == 2 && $2->type == CHAR) )
        {
          $$->type = ERR;
          has_error = true;
          pretty_print_error("Incompatible types: function return type and returned expression");
        }
        else
        {
        	//CodeGen - extra
        	$$->code += intToBool();
        }
      }
	}
	| RETURN error {  $$ = new attr(); $$->type = ERR; pretty_print_error(semicolon_error_return); }
	| RETURN alr_subexpression error {  $$ = new attr(); $$->type = ERR; pretty_print_error(semicolon_error_return); }

alr_subexpression:
	 supported_constant {
        // $$= new attr();
	   //Semantic analyses - Nothing to check
	   $$ = new attr(); copy_attr($$,$1);

	   //CodeGen

	   // Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
	| var_use
    {
      //  $$= new attr();

	   //Semantic analyses - Nothing to check
	   $$ = new attr(); copy_attr($$,$1);

	   //CodeGen - Nothing to do

	   //Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
	| ID OPENPAREN id_list CLOSEPAREN  { //Function call

          $$= new attr();
        //Semantic analyses
    		call_name_ptr = NULL;
        if ( func_table.count($1) == 0 )
        {
            $$->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Function not declared");
        }
    		else
          call_name_ptr = &func_table[$1];

    		if ( call_name_ptr->param_list.size() != call_param_list.size() )
        {
            $$->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Parameter list length mismatch");
        }
        else
        {
            for ( int i = 0; i < call_param_list.size(); i++ )
            {
                if ( call_param_list[i]->type != call_name_ptr->param_list[i].type )
                {
                    has_error = true;
                    $$->type = ERR;
                    pretty_print_error ("Semantic error: Parameter type mismatch in parameter list");
                }
            }
        }
    		$$->type = call_name_ptr->return_type;

        //CodeGeneration
        // $$->type = func_table[$1].return_type;
    		$$->code = "sw $fp 0($sp) \n"; // $fp -> 0($sp)
    		string eleType;
    		int eleSize;
        for (int i=0;i< call_param_list.size(); i++){

          if (call_param_list[i]->type == INT){
          	eleType = "lw";
            eleSize = 4;
          }
          else{
           	eleType = "lb";
            eleSize = 1;
          }
            if (call_param_list[i]->is_param == true){
              	stringstream s;
              	s << call_param_list[i]->offset;
            		$$->code += eleType + " $t1 " + s.str() + "($fp) \n";
            }
          else{
               $$->code += eleType + " $t1 " + get_mips_name(call_param_list[i]) + "\n";
          }
          $$->code += "sw $t1 0($sp)\n";
          stringstream s1; s1 <<eleSize;
					$$->code += "addiu $sp $sp -" + s1.str() + "\n";
        }
    		$$->code += "jal " +string($1) + "\n";

				//Back to Semantic
        call_name_ptr = NULL;
  }
	| OPENPAREN alr_subexpression CLOSEPAREN {
		//Semantic Analyses - no checks needed
		//CodeGen
		$$ = $2;
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
        // cout<< $1->type << " " << $4->type <<endl;
	    //Semantic Analyses
      //cout << $1->type << "\t"<< $1->code <<endl;
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
	}
	| OPENNEGATE alr_subexpression CLOSEPAREN {
        $$= new attr();
		//Semantic analyses - no checks
		$$ = $2;
		//Code gen
		if(!has_error){
		    $$->code += "neg $t0 $t0 \n";
		}
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
	}
  | lhs EQ alr_subexpression {
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


            if ( cast($1->type, $3->type, 0) == 2)
            {
                //CodeGen - no other casting test needed because only allowed downcast is from int to bool
                $$->code += "#Casting of RHS";
                $$->code += intToBool();
            }
            if ( $1->type != ERR && $1->code == "$" )
            {
                lhsRecord = &active_func_ptr->param_list[$1->ival];
                stringstream s;
                s << lhsRecord->offset;
                $$->code += "sw " + s.str() + "($fp) $t0\n";
            }

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

	| error EQ alr_subexpression { $$ = new attr(); $$->type = ERR; pretty_print_error("Missing identifier name"); }
	//| var_use error alr_subexpression {$$ = new attr(); $$->type = ERR; pretty_print_error("Possible missing equalty sign"); }
	//| var_use OPENPAREN id_list error { $$ = new attr(); $$->type = ERR; pretty_print_error("Possible missing closing parenthesis"); }

id_list:
	id_list COMMA var_use {
	   //Semantic Analyses
     $$ = new attr();
	   $$ = new attr(); copy_attr($$,$1);
	   if ( $3->type != ERR )
     {
    		if ($3->bval)
        {
        	call_param_list.push_back(& (call_name_ptr->param_list[$3->ival]) );
        }
       else
       {
       		call_param_list.push_back( get_record($3->label) );
       }
     }

	   //CodeGen

	   //Tree stuff
	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1; node *comma = as_tree_n("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3;
	}
	| var_use {
      $$ = new attr();
	   //Semantic Analyses
	   $$ = new attr(); copy_attr($$,$1);
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

	// | error COMMA id_list {
  //     $$ = new attr();
	//     $$->type = ERR; pretty_print_error("Missing identifier name");
	// }

lhs:
    ID {
	    //Semantic Analyses -> param
      $$ = new attr();
	    var_record* id_rec = get_record($1);
	    if ( id_rec == NULL )
	    {
	        //Check if valid parameter
	        int flag = -1;
	        for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
	            if ( active_func_ptr->param_list[i].name == $1 )
	                { flag = i; break; }
	        if (flag >= 0)
	        {
	            $$->type = active_func_ptr->param_list[flag].type;
	            $$->ival = flag;
	            $$->code = "$";
	        }
	        else
	        {
	            $$->type = ERR;
    	        $$->ival = -1;
    	        pretty_print_error("Semantic Error: ID not declared before use");
    	        has_error = true;
	        }
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
	            $$->type = ERR;
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
    if (scope == 1)
    {
    	var_record id_rec;
      id_rec.is_param = true;
      id_rec.var_type = SIMPLE;
      id_rec.name = $1;
      id_rec.scope = scope;
      id_rec.dim = 0;
      id_rec.type = ($<attr_el>0)->type;
      active_func_ptr->param_list.push_back(id_rec);
      $$->ival = active_func_ptr->param_list.size() - 1;
    }
    else
    {
       if( sym_table.count(scope) > 0 && sym_table[scope].count($1) != 0 )
       {
            $$->type = ERR;
            pretty_print_error("Semantic Error: ID redeclaration in same scope.");
            has_error = true;
       }
       else
       {
              var_record id_rec;
         			id_rec.is_param = false;
              id_rec.var_type = SIMPLE;
              id_rec.name = $1;
              id_rec.scope = scope;
              id_rec.dim = 0;
              id_rec.type = ($<attr_el>0)->type;
              if (!sym_table.count(scope))
              {
                map <string,var_record> temp;
                temp[$1] = id_rec;
                sym_table[scope] = temp;
              }
              else{
                sym_table[scope][$1] = id_rec;
              }
         			$$->ival = -1;
              //cout << id_rec.type <<"\t"<<id_rec.name<<"\n";
              // cout << $1 << " inserted." << endl;
       }

       //CodeGen
       mips_name.push_back( sym_table[scope][$1] ); //For adding to data declarations
    }

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
       			id_rec.is_param = false;
            id_rec.var_type = ARRAY;
            id_rec.name = $1;
            id_rec.scope = scope;
            id_rec.dim = atoi($3);
            id_rec.type = $<attr_el>0->type;
            sym_table[scope][$1] = id_rec;
	   }

       //CodeGen
	   mips_name.push_back(sym_table[scope][$1]); //For adding to data declarations

	   //Tree stuff
	   // $$ = as_tree_n("decl_ID[arr]", NONTERMINAL); $$->info = "decl_ID[arr]";
	}

var_use:
	ID {
	    //Semantic Analyses
      $$ = new attr();
    	bool is_param = false;
    	int flag = -1;
	    var_record* id_rec = get_record($1);
	    if ( id_rec == NULL )
	    {
	        for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
	            if ( active_func_ptr->param_list[i].name == $1 )
	                { flag = i;break; }
	        if (flag >= 0)
	        {
             	is_param = true;
	            $$->type = active_func_ptr->param_list[flag].type;
            	$$->bval = true;
            	$$->ival = flag; //Indicates parameter
	        }
        	else
          {
            $$->type = ERR;
            $$->bval = false;
            $$->ival = -1;
            pretty_print_error("Semantic Error: ID not declared before use");
            has_error = true;
          }
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
        	$$->bval = false;        	//Indicates normal variable
	        $$->ival = -1;
        	$$->label = $1;
	    }

	    //CodeGen
	    if (!has_error){
	        //Check in local variables -> if not found, check in param list -> if found, load param by offset
          if ( is_param )
            {
                stringstream s;
                s << active_func_ptr->param_list[flag].offset;
                $$->code += "sw " + s.str() + "($fp) $t0\n";
            }
          else{
              $$->code = load_mips_id( get_record($1) );
          }
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
        	$$->label = $1;
	    }

        //CodeGen
        if (!has_error){
            $$->code = load_mips_array( get_record($1),atoi($3));
        }

        //Tree-related stuff
	    // $$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";
	}

supported_constant:
	INTCONST {

	    //Semantic Analyses
        $$ = new attr();
        $$->ival =  atoi($1);
        $$->type = INT;
        $$->code = "li $t0 " + string($1) + "\n";

	    //CodeGen
	    //No codegen assoc with this production
    }
| CHARCONST {
	    //Semantic Analyses
        $$ = new attr();
        $$->cval =  *($1);
        $$->type = CHAR;

	    //CodeGen

        $$->code = "li $t0 \'" + string($1) + "\' \n";


	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;
	}
	| BOOLCONST {
	    //Semantic Analyses
      $$ = new attr();
	    if( !strcmp($1, "true") ){
          $$->bval = 1;
          $$->code = "li $t0 1\n";
      }

	    else{
            $$->bval = 0;
            $$->code = "li $t0 0\n";
      }

	    $$->type = BOOL;

        //Semantic Analyses
	    //CodeGen


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
