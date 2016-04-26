/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mad_parser.y" /* yacc.c:339  */

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
#define semicolon_error "Semicolon kadu"
#define comma_error "Comma kadu"
#define identifier_error " identifier kadu"
#define semicolon_error_for "Semicolon forlu kadu"
#define type_error "Unknown type declaration"
#define semicolon_error_return "Semicolon returnlo kadu :P"


#define vyavadhi scope
#define peru name
#define daram  string
#define dakshina code

using namespace std;

extern int yylex();
extern int lengthyy;
extern int yylineno;
extern char* textyy;

enum TYPE {VOIDF, INT, CHAR, BOOL, ERR};

struct var_record {
    bool is_param;
  	daram peru;
    int vyavadhi,var_type,dim,offset;
    TYPE type;
    daram mips_name;
};


struct func_record
{
    TYPE return_type;
    daram peru;
    vector<var_record> param_list;
    int paramlist_size;
};

//Attributes aakaramure
struct attr
{
    TYPE type;
    int ival;   //For storing values of constants
    char cval;
    float fval;
    bool bval;

    daram dakshina; //Code gen by diff non-terminals
    daram label; // Useful for if-else-operation
    vector<TYPE> types; //Types in parameter list
};


//GLOBAL VARIABLES FOR SEMANTIC ANALYSIS
int vyavadhi = 0;
int labelNumber = 0;
daram data;
vector< var_record > mips_name;
func_record *active_func_ptr, *call_name_ptr;
vector<var_record*> call_param_list;

//Tree printing
node *root;
bool arey_galti_hai_kya;

map<daram, func_record> func_table;
map<int, map<daram, var_record> > sym_table;

void pretty_print_error(const char*);
var_record* get_record (daram);
daram get_mips_name (var_record*);
daram load_mips_array(var_record* varRecord, int offSet);
daram store_mips_array(var_record* varRecord, int offSet);
int cast (TYPE typeA, TYPE typeB, int is_up); // Return type: 0-> no casting possible 1-> typeA can be casted 2-> typeB can be casted

//Function Declarations


void copy_attr( struct attr* A,struct attr* B){
  A->type = B->type;
  A->ival = B->ival;   //For storing values of constants
  A->cval = B->cval;
  A->fval = B->fval;
  A->bval = B->bval;

  A->dakshina = B->dakshina; //Code gen by diff non-terminals
  A->label = B->label; // Useful for if-else-operation

}


daram get_data_string(){
    stringstream data_string;
    data_string << '\n';
    set <daram> temp_mips_name;
    for(int i=0;i<mips_name.size();i++){
        var_record rec = mips_name[i];
        if (temp_mips_name.count( rec.mips_name ) ==0)
        {
          // peru
          temp_mips_name.insert(rec.mips_name);
          data_string << rec.mips_name << ": ";
          if(rec.var_type == SIMPLE){
              if(rec.type == INT){
                  data_string << ".word ";
                  data_string << "0";
              }
              else{
                  data_string << ".byte ";
                  data_string << "0x41";
              }
          }
          else{
              data_string << ".space ";
              if(rec.type == INT){
                  data_string << (rec.dim)*4;
              }
              else{
                  data_string << rec.dim;
              }
          }
          data_string << "\n";
        }

    }
    return data_string.str();
}

var_record* get_record(daram peru)
{
    for(int i=vyavadhi;i>=2;i--)
    {
        if (sym_table[i].find(peru) != sym_table[i].end())
        {
            return &sym_table[i][peru];
        }
    }
    return NULL;
}

daram get_mips_name (var_record* varRecord)
{
    daram mips_name;
    if (active_func_ptr == NULL){
      mips_name = "main";
    }
    else{
      mips_name = active_func_ptr -> peru;
    }
    mips_name += "_";
    mips_name += varRecord-> peru;

    stringstream s;//int ko string karne ka aur koi raasta nahe mila
    s << "_" << varRecord->type << "_" << varRecord->vyavadhi ;
    mips_name += s.str();
    return mips_name;
}


daram get_label()
{
    //Only returns the peru of the label
	stringstream s;//int ko string karne ka aur koi raasta nahe mila
	s << labelNumber;
    daram label =  "LABEL" + s.str();
    labelNumber++;
    return label;
}

daram load_mips_array(var_record* varRecord, int offSet)
{
    daram loadCode,loadType;
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
    loadCode = "li $t1 " + s.str() + "\n" ;
    loadCode += "li $t2 " + s1.str() + "\n";
    loadCode += "mul $t2 $t1 $t2\n" ;
    loadCode += "la $t1 " + get_mips_name(varRecord) + "\n";
    loadCode += "add $t1 $t1 $t2 \n";
    loadCode += loadType + " $t0 ($t1) \n";
    return loadCode;
}

daram store_mips_array(var_record* varRecord, int offSet)
{
    daram storeCode,storeType;
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
    storeCode = "li $t1 " + s.str() + "\n" ;
    storeCode += "li $t2 " + s1.str() + "\n";
    storeCode += "mul $t2 $t1 $t2\n" ;
    storeCode += "la $t1 " + get_mips_name(varRecord) + "\n";
    storeCode += "add $t1 $t1 $t2 \n";
    storeCode +=  storeType + " $t0 ($t1)\n";
    return storeCode;
}

daram load_mips_id(var_record* varRecord)
{
    daram loadCode,loadType;
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

daram store_mips_id (var_record* varRecord)
{
    daram storeCode,storeType;
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

daram intToBool()
{
    daram boolCode = "srl $t0 $t0 0x1F\n";
    boolCode += "andi $t0 $t0 0x1\n";
    boolCode += "addi $t0 $t0 0x1\n";
    boolCode += "andi $t0 $t0 0x1\n";
    return boolCode;
}

int cast (TYPE pehla_waala_type, TYPE doosra_waala_type, int is_up)
{
    if (pehla_waala_type == doosra_waala_type)
        return 0;
    if (is_up == 1){
        /* char can be converted to int, bool can be converted to int */
        if ( (pehla_waala_type == CHAR || pehla_waala_type == BOOL) && doosra_waala_type == INT)
        {
            return 1;
        }
        else if ((doosra_waala_type == CHAR || doosra_waala_type == BOOL) && pehla_waala_type == INT){
            return 2;
        }
        return -1;
    }
    else{
        //int can be converted to bool
        if ( pehla_waala_type == BOOL && doosra_waala_type == INT ){
            return 2;
        }
        else if (pehla_waala_type == INT && doosra_waala_type == BOOL){
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

node::node(daram con, node_type t)
{
	content = con;
	type = t;
	child = NULL;
	sibling = NULL;
	info = "";
}
//First SEGEMENT
node::node(const char* con, int t)
{
	content = (con);
	if(t == 0) type = NONTERM;
	else if(t == 1) type = TERM;
	else if(t == 2) type = VAL;
	info = "";
}


#line 404 "mad_parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "mad_parser.tab.h".  */
#ifndef YY_YY_MAD_PARSER_TAB_H_INCLUDED
# define YY_YY_MAD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NONTERMINAL = 0,
    ID = 258,
    COMMA = 259,
    SEMI = 260,
    OPENPAREN = 261,
    CLOSEPAREN = 262,
    OPENCURLY = 263,
    CLOSECURLY = 264,
    OPENSQUARE = 265,
    CLOSESQUARE = 266,
    OPENNEGATE = 267,
    VOID = 268,
    DTYPE_INT = 269,
    DTYPE_BOOL = 270,
    DTYPE_CHAR = 271,
    EQ = 272,
    ARITH = 273,
    RELN = 274,
    LOGICAL = 275,
    LOGICALNOT = 276,
    IF = 277,
    ELSE = 278,
    WHILE = 279,
    FOR = 280,
    RETURN = 281,
    PRINT = 282,
    READ = 283,
    BOOLCONST = 284,
    INTCONST = 285,
    CHARCONST = 286,
    TERMINAL = 1,
    VALUE = 2
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 339 "mad_parser.y" /* yacc.c:355  */

	struct attr* attr_el;
	node* node_el;
	char* node_con;

#line 485 "mad_parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAD_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 500 "mad_parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,    32,    33,     2,     2,     2,     2,     2,     2,     2,
      34,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   388,   388,   396,   399,   403,   406,   409,   414,   420,
     435,   449,   452,   455,   460,   465,   478,   478,   519,   519,
     519,   551,   571,   587,   593,   599,   607,   635,   638,   644,
     659,   665,   680,   684,   688,   692,   696,   700,   703,   731,
     737,   746,   776,   790,   812,   813,   816,   825,   836,   906,
     912,   951,   960,  1002,  1038,  1057,  1105,  1109,  1129,  1149,
    1160,  1203,  1240,  1293,  1322,  1382,  1422,  1434,  1448,  1469
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "NONTERMINAL", "error", "$undefined", "ID", "COMMA", "SEMI",
  "OPENPAREN", "CLOSEPAREN", "OPENCURLY", "CLOSECURLY", "OPENSQUARE",
  "CLOSESQUARE", "OPENNEGATE", "VOID", "DTYPE_INT", "DTYPE_BOOL",
  "DTYPE_CHAR", "EQ", "ARITH", "RELN", "LOGICAL", "LOGICALNOT", "IF",
  "ELSE", "WHILE", "FOR", "RETURN", "PRINT", "READ", "BOOLCONST",
  "INTCONST", "CHARCONST", "TERMINAL", "VALUE", "'\\n'", "$accept",
  "start_mad_program", "mad_program", "supported_declarations",
  "variable_declarations", "variable_definitions", "comma_rule", "dtype",
  "function_declarations", "$@1", "@2", "$@3", "func_name",
  "argument_list", "statement_block", "opencurly", "variable_list",
  "statement_list", "supported_statement", "if_statement",
  "else_statement", "while_statement", "return_statement",
  "alr_subexpression", "id_list", "lhs", "var_decl", "var_use",
  "supported_constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     1,     2,    10
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -63

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,   -23,   -76,   -76,   -76,   -76,    16,   -76,   113,   -76,
     133,    24,   -76,   -76,    32,   -76,   -76,    33,   -76,   -76,
      33,    11,    37,   -76,   -76,   -76,    34,    28,   -76,    20,
     -76,    63,   -76,    69,   127,   127,   -76,    57,    67,    76,
      81,    71,    82,    85,    85,   127,   127,   127,   -76,   -76,
     127,   -76,   -76,   -76,   -76,   127,    33,    25,   -76,    73,
     130,    70,    91,    70,    98,    99,    58,   -76,   -76,   -76,
     -76,    86,    25,   -76,   -76,   -76,    97,    94,   -76,   -76,
      70,   115,   109,     0,   128,    89,   131,    70,    70,    73,
     -76,   105,   -76,   -76,   -76,   -76,    70,    70,    70,    70,
     131,   138,    41,   -76,   141,   -76,   -76,   -76,   112,   126,
     -76,   -76,   131,   131,   131,   131,   123,   115,   -76,   137,
      85,    85,   144,   -76,   134,   -76,   -76,    85,   -76,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    18,    13,    14,    15,     0,     2,     0,     6,
       0,     0,     7,     5,     0,     1,     4,     0,    12,     8,
       0,    62,     0,     9,    21,    19,    62,     0,    10,     0,
      16,     0,    11,     0,    23,    23,    63,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    23,    23,    27,    17,
      28,    20,    25,    24,    22,    28,     0,     0,    29,     0,
      64,     0,     0,     0,     0,     0,     0,    68,    66,    67,
      36,     0,     0,    33,    34,    35,     0,     0,    47,    46,
       0,    59,     0,     0,    66,     0,    54,     0,     0,    44,
      42,     0,    26,    31,    37,    32,     0,     0,     0,     0,
      56,    64,     0,    58,     0,    49,    69,    51,     0,     0,
      45,    43,    50,    52,    53,    55,     0,     0,    48,    65,
       0,     0,     0,    57,    39,    41,    65,     0,    38,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   148,   -76,   -41,   -76,   -76,     2,   -76,   -76,
     -76,   -76,   145,   -22,   -43,   -76,   103,    88,   -76,   -76,
     -76,   -76,   -76,   -58,   -76,   -76,    -5,   -75,   -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    20,    37,    12,    34,
      14,    31,    22,    38,    70,    50,    57,    71,    72,    73,
     128,    74,    75,    76,   102,    77,    23,    78,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    51,    11,    83,    85,    86,   103,   105,    91,    55,
      11,    13,    27,    39,    55,    28,    15,   -21,    96,    97,
      98,    29,   100,    52,    53,    54,    59,    21,    60,   108,
     109,    61,    42,    48,   -30,    24,    26,    62,   112,   113,
     114,   115,   123,    30,    29,   117,    63,    64,   118,    65,
      33,    66,    56,     1,    67,    68,    69,    56,    40,    89,
      41,    60,    32,    90,    61,     2,     3,     4,     5,    35,
      62,    59,    46,    60,    43,   -62,    61,   124,   125,    63,
      36,    29,    62,    44,   129,    45,    47,    67,    68,    69,
      80,    63,    59,    48,    60,    92,   107,    61,    94,    67,
      68,    69,    95,    62,    87,    88,   110,    96,    97,    98,
     111,    99,    63,    -3,     1,    96,    97,    98,   101,   120,
      67,    84,    69,    96,    97,    98,     2,     3,     4,     5,
      96,    97,    98,   121,    17,   106,    81,    18,    19,   104,
      82,     3,     4,     5,    96,    97,    98,   -60,   116,    96,
      97,    98,   119,   122,   -61,   126,    16,   127,    58,    25,
      93
};

static const yytype_uint8 yycheck[] =
{
      43,    44,     0,    61,    62,    63,    81,     7,    66,    50,
       8,    34,    17,    35,    55,    20,     0,     6,    18,    19,
      20,    10,    80,    45,    46,    47,     1,     3,     3,    87,
      88,     6,    37,     8,     9,     3,     3,    12,    96,    97,
      98,    99,   117,     6,    10,     4,    21,    22,     7,    24,
      30,    26,    50,     1,    29,    30,    31,    55,     1,     1,
       3,     3,    34,     5,     6,    13,    14,    15,    16,     6,
      12,     1,     1,     3,     7,     4,     6,   120,   121,    21,
      11,    10,    12,     7,   127,     4,     4,    29,    30,    31,
      17,    21,     1,     8,     3,     9,     7,     6,     1,    29,
      30,    31,     5,    12,     6,     6,     1,    18,    19,    20,
       5,    17,    21,     0,     1,    18,    19,    20,     3,     7,
      29,    30,    31,    18,    19,    20,    13,    14,    15,    16,
      18,    19,    20,     7,     1,     7,     6,     4,     5,    30,
      10,    14,    15,    16,    18,    19,    20,    17,    10,    18,
      19,    20,    11,    30,    17,    11,     8,    23,    55,    14,
      72
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    13,    14,    15,    16,    36,    37,    38,    39,
      40,    42,    43,    34,    45,     0,    37,     1,     4,     5,
      41,     3,    47,    61,     3,    47,     3,    61,    61,    10,
       6,    46,    34,    30,    44,     6,    11,    42,    48,    48,
       1,     3,    61,     7,     7,     4,     1,     4,     8,    49,
      50,    49,    48,    48,    48,    39,    42,    51,    51,     1,
       3,     6,    12,    21,    22,    24,    26,    29,    30,    31,
      49,    52,    53,    54,    56,    57,    58,    60,    62,    63,
      17,     6,    10,    58,    30,    58,    58,     6,     6,     1,
       5,    58,     9,    52,     1,     5,    18,    19,    20,    17,
      58,     3,    59,    62,    30,     7,     7,     7,    58,    58,
       1,     5,    58,    58,    58,    58,    10,     4,     7,    11,
       7,     7,    30,    62,    49,    49,    11,    23,    55,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    38,    38,    39,    40,
      40,    40,    41,    42,    42,    42,    44,    43,    45,    46,
      43,    47,    48,    48,    48,    48,    49,    50,    51,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    55,
      55,    56,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     2,
       3,     4,     1,     1,     1,     1,     0,     7,     0,     0,
       8,     1,     4,     0,     4,     4,     4,     1,     0,     2,
       0,     2,     2,     1,     1,     1,     1,     2,     6,     0,
       2,     5,     2,     3,     2,     3,     1,     1,     4,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     1,     0,
       1,     4,     1,     4,     1,     4,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 388 "mad_parser.y" /* yacc.c:1646  */
    {
    cout <<".data\n";
    cout << get_data_string();
    cout <<"\n .text \n .globl main \n";
    cout << (yyvsp[0].attr_el)->dakshina;
  }
#line 1678 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 396 "mad_parser.y" /* yacc.c:1646  */
    {
  	(yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 1686 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 399 "mad_parser.y" /* yacc.c:1646  */
    {
  	(yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[-1].attr_el));
    (yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;
  }
#line 1695 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 403 "mad_parser.y" /* yacc.c:1646  */
    { pretty_print_error("Compilation terminating with errors"); root = NULL;}
#line 1701 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 406 "mad_parser.y" /* yacc.c:1646  */
    {
  	(yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 1709 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 409 "mad_parser.y" /* yacc.c:1646  */
    {
  	(yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 1717 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 414 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[-1].attr_el));
  }
#line 1725 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 420 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
  	if (arey_galti_hai_kya)
    {
    	(yyval.attr_el)->type = ERR;
      (yyval.attr_el)->dakshina = "";
    }
  	else
    {
    	(yyval.attr_el)->dakshina = (yyvsp[0].attr_el)->dakshina;
      (yyval.attr_el)->type = (yyvsp[-1].attr_el)->type;

    }

}
#line 1745 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 435 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
  	if (arey_galti_hai_kya)
    {
    	(yyval.attr_el)->type = ERR;
      (yyval.attr_el)->dakshina = "";
    }
  	else
    {
      (yyvsp[0].attr_el)->type = (yyvsp[-1].attr_el)->type;
    	(yyval.attr_el)->dakshina = (yyvsp[-2].attr_el)->dakshina + (yyvsp[0].attr_el)->dakshina;
      (yyval.attr_el)->type = (yyvsp[-1].attr_el)->type;
    }
  	}
#line 1764 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 449 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error("Missing comma in definitions list"); }
#line 1770 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 452 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.attr_el) = new attr(); (yyval.attr_el)->type = ((yyvsp[-1].attr_el))->type; }
#line 1776 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 455 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->type = INT;
    (yyval.attr_el)->ival = INT_SIZE;
  }
#line 1786 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 460 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->type = BOOL;
    (yyval.attr_el)->ival = BOOL_SIZE;
  }
#line 1796 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 465 "mad_parser.y" /* yacc.c:1646  */
    {
  	(yyval.attr_el) = new attr();
    (yyval.attr_el)->type = CHAR;
    (yyval.attr_el)->ival = CHAR_SIZE;
  }
#line 1806 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 478 "mad_parser.y" /* yacc.c:1646  */
    { vyavadhi = 1; }
#line 1812 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 478 "mad_parser.y" /* yacc.c:1646  */
    {
        //vyavadhi Consideration
        vyavadhi = 0;
    		int cur_offset = 0;
        //Semantic
        (yyval.attr_el) = new attr();

        // for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
        // {
        // 	switch(active_func_ptr->param_list[i].type)
        //   {
        //   	case INT: active_func_ptr->param_list[i].offset = cur_offset + INT_SIZE;
        //               cout << "\t " << active_func_ptr->param_list[i].offset << " peru: " << active_func_ptr->param_list[i].peru << endl;
        //     				cur_offset += INT_SIZE;
        //     	break;
        //     default: active_func_ptr->param_list[i].offset = cur_offset + BOOL_SIZE;
        //     				cur_offset += BOOL_SIZE;
        //     break;
        //   }
        // }
    		active_func_ptr->paramlist_size = (yyvsp[-2].attr_el)->ival ; //Setting paramlist size
        //Code Generation
        (yyval.attr_el)->dakshina = (yyvsp[-5].attr_el)->label + ":\n";
        //Store return $ra to stack and set frame pointer to $ra
        (yyval.attr_el)->dakshina += "sw $ra 0($sp)\n";
        (yyval.attr_el)->dakshina += "move $fp $sp \n";
    		(yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
    		(yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;
        (yyval.attr_el)->dakshina += "lw $ra 0($fp)\n";
        (yyval.attr_el)->dakshina += "move $sp $fp\n";

    		//Pop parameters
    		stringstream s;//int ko string karne ka aur koi raasta nahe mila
    		s << active_func_ptr->paramlist_size;
    		(yyval.attr_el)->dakshina += "addiu $sp $sp " + s.str() + "\n";
        (yyval.attr_el)->dakshina += "lw $fp 4($sp)\n";
        (yyval.attr_el)->dakshina += "addiu $sp $sp 4\n";
    		(yyval.attr_el)->dakshina += "jr $ra\n";
    		//Semantic again
    		active_func_ptr = NULL;
	}
#line 1858 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 519 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.attr_el) = new attr(); (yyval.attr_el)-> type = VOIDF; }
#line 1864 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 519 "mad_parser.y" /* yacc.c:1646  */
    { vyavadhi = 1; }
#line 1870 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 519 "mad_parser.y" /* yacc.c:1646  */
    {
		//vyavadhi Consideration
		vyavadhi = 0;

		//Semantic
    (yyval.attr_el) = new attr();
    //vyavadhi Consideration
        vyavadhi = 0;
    		int cur_offset = 0;
        //Semantic
        (yyval.attr_el) = new attr();
    		active_func_ptr->paramlist_size = (yyvsp[-2].attr_el)->ival; //Setting paramlist size
    //Code Generation
    		(yyval.attr_el)->dakshina = (yyvsp[-5].attr_el)->label + ":\n";
        //Store return $ra to stack and set frame pointer to $ra
        (yyval.attr_el)->dakshina += "sw $ra 0($sp) \n";
        (yyval.attr_el)->dakshina += "move $fp $sp \n";
    		(yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
    		(yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;
    		(yyval.attr_el)->dakshina += "move $sp $fp\n";
    		(yyval.attr_el)->dakshina += "lw $ra 0($fp)\n";          // $ra <- 0($fp)
    		(yyval.attr_el)->dakshina += "addiu $sp $sp 4\n";
    		//Pop parameters
    		stringstream s;//int ko string karne ka aur koi raasta nahe mila
    		s << active_func_ptr->paramlist_size;
    		(yyval.attr_el)->dakshina += "addiu $sp $sp " + s.str() + "\n";
    		(yyval.attr_el)-> dakshina += "jr $ra\n";

    		//Semantic again
    		active_func_ptr = NULL;
	}
#line 1906 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 551 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
		if (func_table.count((yyvsp[0].node_con)) > 0)
    {
    	arey_galti_hai_kya = true;
      pretty_print_error ("Sem mein galti: function k liye naam khatam ho gye kya :P");
    }
    else
    {
    	func_record f_temp;
      func_table[daram((yyvsp[0].node_con))] = f_temp;
      //Setting active_func_ptr
      active_func_ptr = &func_table[daram((yyvsp[0].node_con))];
      active_func_ptr -> peru = daram((yyvsp[0].node_con));
      active_func_ptr -> return_type = (yyvsp[-1].attr_el)->type;
    }
    (yyval.attr_el)->type = VOIDF;
    (yyval.attr_el)->label = (yyvsp[0].node_con);
  }
#line 1930 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 571 "mad_parser.y" /* yacc.c:1646  */
    {
      //Nothing to do - check for errors and proceed
      (yyval.attr_el) = new attr();
      if (arey_galti_hai_kya)
      {
        (yyval.attr_el)->type = ERR;
        (yyval.attr_el)->dakshina = "";
      }
      else
      {
        active_func_ptr->param_list[(yyvsp[-2].attr_el)->ival].offset = (yyvsp[0].attr_el)->ival + ( (yyvsp[-3].attr_el)->ival );
        // cout << active_func_ptr->param_list[$2->ival].peru << " has offset " << active_func_ptr->param_list[$2->ival].offset << endl;
        (yyval.attr_el)->dakshina = (yyvsp[-3].attr_el)->dakshina + (yyvsp[-2].attr_el)->dakshina;
        (yyval.attr_el)->ival = (yyvsp[0].attr_el)->ival + ((yyvsp[-3].attr_el)->ival);
      }
  }
#line 1951 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 587 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->dakshina = "";
    (yyval.attr_el)->ival = 0;
  }
#line 1962 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 593 "mad_parser.y" /* yacc.c:1646  */
    {
  	arey_galti_hai_kya = true;
    pretty_print_error (comma_error);
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->type = ERR;
  }
#line 1973 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 599 "mad_parser.y" /* yacc.c:1646  */
    {
  	arey_galti_hai_kya = true;
    pretty_print_error (identifier_error);
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->type = ERR;
  }
#line 1984 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 607 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.attr_el) = new attr();

  	if (arey_galti_hai_kya)
    {
    	(yyval.attr_el)->type = ERR;
      (yyval.attr_el)->dakshina = "";
    }
  	else
    {
    	(yyval.attr_el)->dakshina = (yyvsp[-2].attr_el)->dakshina + (yyvsp[-1].attr_el)->dakshina;
    }
  	//vyavadhi resolution
    map<daram, var_record> temp;
  	sym_table[vyavadhi] = temp;
  	vyavadhi--;
  }
#line 2006 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 635 "mad_parser.y" /* yacc.c:1646  */
    { vyavadhi++; }
#line 2012 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 638 "mad_parser.y" /* yacc.c:1646  */
    {
  	//Nothing to do
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->dakshina = "";

  }
#line 2023 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 644 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do - check for error in further productions
    (yyval.attr_el) = new attr();

    if (arey_galti_hai_kya)
    {
      (yyval.attr_el)->type = ERR;
      (yyval.attr_el)->dakshina = "";
    }
    else
      (yyval.attr_el)->dakshina = (yyvsp[-1].attr_el)->dakshina + (yyvsp[0].attr_el)->dakshina;
  }
#line 2040 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 659 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr();
    (yyval.attr_el)->dakshina = "";

  }
#line 2051 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 665 "mad_parser.y" /* yacc.c:1646  */
    {
    //Semantic Analyses - chaining
    (yyval.attr_el) = new attr();
    if (!arey_galti_hai_kya)
    {
    	(yyval.attr_el)->dakshina = (yyvsp[-1].attr_el)->dakshina + "\n" + (yyvsp[0].attr_el)->dakshina;
    }
    else
    {
      (yyval.attr_el)->type = ERR;
      (yyval.attr_el)->dakshina = "";
    }
  }
#line 2069 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 680 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[-1].attr_el));
  }
#line 2078 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 684 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 2087 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 688 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 2096 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 692 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 2105 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 696 "mad_parser.y" /* yacc.c:1646  */
    {
    //Nothing to do
    (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
  }
#line 2114 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 700 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; arey_galti_hai_kya = true; pretty_print_error("Possible missing semicolon with alr_subexpression"); }
#line 2120 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 703 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.attr_el) = new attr();
		if ((yyvsp[-3].attr_el)->type == CHAR )
    {
    	arey_galti_hai_kya = true;
      (yyval.attr_el)->type = ERR;
      pretty_print_error ("Incompatible types: if mein boolean value dene ka, nahe toh apun error dega.");
    }
		//Code Generation
	    daram startElse,endElse;
	    startElse = get_label();
	    endElse = get_label();

	    (yyval.attr_el) -> dakshina = (yyvsp[-3].attr_el)-> dakshina;
      if ((yyvsp[-3].attr_el)->type == INT){
        (yyval.attr_el)->dakshina += intToBool();
      }
	    (yyval.attr_el) -> dakshina += "li $t1 0x1\n";
	    (yyval.attr_el) -> dakshina += "bne $t0 $t1 " + startElse + "\n";
	    (yyval.attr_el) -> dakshina += (yyvsp[-1].attr_el) ->dakshina;
	    (yyval.attr_el) -> dakshina += "b " + endElse + "\n";
	    (yyval.attr_el) -> dakshina += startElse + ":\n";
	    (yyval.attr_el) -> dakshina += (yyvsp[0].attr_el)->dakshina;
	    (yyval.attr_el) -> dakshina += endElse + ":\n";

	}
#line 2151 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 731 "mad_parser.y" /* yacc.c:1646  */
    {
    	(yyval.attr_el) = new attr();
    	//Semantic Analyses - no check
    	//CodeGen
	    (yyval.attr_el)-> dakshina = "\n";
	}
#line 2162 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 737 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.attr_el) = new attr();
    //Semantic Analyses - no check
		//Code Generation
		(yyval.attr_el)->dakshina = (yyvsp[0].attr_el)->dakshina;

	}
#line 2174 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 746 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
    //Semantic Analyses
    if ((yyvsp[-2].attr_el)->type != BOOL)
    {
    	arey_galti_hai_kya = true;
      (yyval.attr_el)->type = ERR;
      pretty_print_error ("Incompatible types: while mein boolean value dene ka nahe toh apan error dega");
    }

		//Code Generation
    if (!arey_galti_hai_kya)
    {
      daram startWhile = get_label();
      daram endWhile = get_label();
      //Start While loop
      (yyval.attr_el)->dakshina = startWhile + ":\n";
      //Evaluate alr_subexpression
      (yyval.attr_el)->dakshina += (yyvsp[-2].attr_el)->dakshina;
      (yyval.attr_el)->dakshina += "li $t1 0x1\n";
      (yyval.attr_el)->dakshina += "bne $t0 $t1 " + endWhile + "\n";
      //Perform main Statement Block
      (yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;
      (yyval.attr_el)->dakshina += "b " + startWhile + "\n";
      //FinishWhile
      (yyval.attr_el)->dakshina += endWhile + ":\n";
    }
	}
#line 2207 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 776 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el) = new attr();
    //Semantic Analyses
		if ( active_func_ptr->return_type != VOIDF )
    {
      		(yyval.attr_el)->type = ERR;
          arey_galti_hai_kya = true;
          pretty_print_error("Incompatible types: function return type not void");
    }

    //Code Generation
    //Nothing to do

	}
#line 2226 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 790 "mad_parser.y" /* yacc.c:1646  */
    {
    	(yyval.attr_el) = new attr();
    	//Semantic Analyses
    	copy_attr((yyval.attr_el),(yyvsp[-1].attr_el));
      // cout << active_func_ptr-> peru << " HYT "<< func_table[active_func_ptr->peru].return_type << endl ;
      // cout << $2->type << " " << active_func_ptr->return_type << endl;
    	int downcast_needed = cast(active_func_ptr->return_type, (yyvsp[-1].attr_el)->type, 0);
      if ( active_func_ptr->return_type != (yyvsp[-1].attr_el)->type )
      {
        if (downcast_needed < 0 || (downcast_needed == 2 && (yyvsp[-1].attr_el)->type == CHAR) )
        {
          (yyval.attr_el)->type = ERR;
          arey_galti_hai_kya = true;
          pretty_print_error("Incompatible types: function return type and returned expression");
        }
        else
        {
        	//CodeGen - extra
        	(yyval.attr_el)->dakshina += intToBool();
        }
      }
	}
#line 2253 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 812 "mad_parser.y" /* yacc.c:1646  */
    {  (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error(semicolon_error_return); }
#line 2259 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 813 "mad_parser.y" /* yacc.c:1646  */
    {  (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error(semicolon_error_return); }
#line 2265 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 816 "mad_parser.y" /* yacc.c:1646  */
    {
        // $$= new attr();
	   //Semantic analyses - Nothing to check
	   (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));

	   //CodeGen


	}
#line 2279 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 826 "mad_parser.y" /* yacc.c:1646  */
    {
      //  $$= new attr();

	   //Semantic analyses - Nothing to check
     (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));

	   //CodeGen - Nothing to do


	}
#line 2294 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 836 "mad_parser.y" /* yacc.c:1646  */
    { //Function call

          (yyval.attr_el)= new attr();
        //Semantic analyses
    		call_name_ptr = NULL;
        if ( func_table.count((yyvsp[-3].node_con)) == 0 )
        {
            (yyval.attr_el)->type = ERR;
            arey_galti_hai_kya = true;
            pretty_print_error("Sem mein galti: Arey function toh declare kar do bhai.");
        }
    		else
          call_name_ptr = &func_table[(yyvsp[-3].node_con)];
          // cout << call_param_list.size() <<"-call_param_list size && " << call_name_ptr->param_list.size() << endl;
    		if ( call_name_ptr->param_list.size() != call_param_list.size() )
        {
            (yyval.attr_el)->type = ERR;
            arey_galti_hai_kya = true;
            pretty_print_error("Sem mein galti: Upar kuch aur declare karto ho ,neeche kch aur parameter ki list dekh k use karo.");
        }
        else
        {
            for ( int i = 0; i < call_param_list.size(); i++ )
            {
                // cout << " call_param_list: " << call_param_list[i]->peru << " " << call_param_list[i]->type << endl;
                // cout << " call_name_ptr ki list:  " << ca

                if ( call_param_list[i]->type != call_name_ptr->param_list[i].type )
                {
                    arey_galti_hai_kya = true;
                    (yyval.attr_el)->type = ERR;
                    pretty_print_error ("Sem mein galti: Parameter type enti? mis_match_in_parameter_list");
                }
            }
        }
    		(yyval.attr_el)->type = call_name_ptr->return_type;

        //CodeGeneration
        // $$->type = func_table[$1].return_type;
    		(yyval.attr_el)->dakshina = "sw $fp 0($sp) \n"; // $fp -> 0($sp)
        (yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
    		daram eleType;
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
              	stringstream s;//int ko string karne ka aur koi raasta nahe mila
              	s << call_param_list[i]->offset;
            		(yyval.attr_el)->dakshina += eleType + " $t1 " + s.str() + "($fp) \n";
            }
          else{
               (yyval.attr_el)->dakshina += eleType + " $t1 " + get_mips_name(call_param_list[i]) + "\n";
          }
          (yyval.attr_el)->dakshina += "sw $t1 0($sp)\n";
          stringstream s1; s1 <<eleSize;
					(yyval.attr_el)->dakshina += "addiu $sp $sp -" + s1.str() + "\n";
        }
    		(yyval.attr_el)->dakshina += "jal " +daram((yyvsp[-3].node_con)) + "\n";

				//Back to Semantic
        call_name_ptr = NULL;
  }
#line 2369 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 906 "mad_parser.y" /* yacc.c:1646  */
    {
		//Semantic Analyses - no checks needed
		//CodeGen
    (yyval.attr_el) = new attr();
		copy_attr((yyval.attr_el),(yyvsp[-1].attr_el));
  }
#line 2380 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 912 "mad_parser.y" /* yacc.c:1646  */
    {

        (yyval.attr_el) = new attr();
        // cout<< $1->type << " " << $4->type <<endl;
	    //Semantic Analyses
      //cout << $1->type << "\t"<< $1->dakshina <<endl;
	    if (cast((yyvsp[-2].attr_el)->type, (yyvsp[0].attr_el)->type, 1) < 0)
	    {
	        arey_galti_hai_kya = 1;
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error ("Sem mein galti: Arithmetic operation barabar waalo p lagaao");
	    }

//Third SEGEMENT

	    //Code Generation
	    if (!arey_galti_hai_kya){
        (yyval.attr_el)->dakshina = (yyvsp[-2].attr_el)->dakshina;
        (yyval.attr_el)->dakshina += "sw $t0 0($sp) \n";
        (yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
        (yyval.attr_el)->dakshina +=  (yyvsp[0].attr_el)->dakshina;
        (yyval.attr_el)->dakshina += "lw $t1 4($sp)\n";
        (yyval.attr_el)->dakshina += "addiu $sp $sp 4\n";
        // cout << $2 << " " << ($2 == "+") <<endl;
	        if (daram((yyvsp[-1].node_con)) == daram("+")){
	            (yyval.attr_el)->dakshina += "add $t0 $t0 $t1\n";
	        }
	        else if ( daram((yyvsp[-1].node_con)) == daram("-")){
	            (yyval.attr_el)->dakshina += "sub $t0 $t1 $t0\n";
	        }
	        else if ( daram((yyvsp[-1].node_con)) == daram("*")){
	            (yyval.attr_el)->dakshina += "mul $t0 $t0 $t1\n";
	        }
	        else if ( daram((yyvsp[-1].node_con)) == daram("/")){
	            (yyval.attr_el)->dakshina += "div $t0 $t1 $t0\n";
	        }
        (yyval.attr_el)->type = INT;
	    }
	}
#line 2424 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 951 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
		//Semantic analyses - no checks
		(yyval.attr_el) = (yyvsp[-1].attr_el);
		//Code gen
		if(!arey_galti_hai_kya){
		    (yyval.attr_el)->dakshina += "neg $t0 $t0 \n";
		}
	}
#line 2438 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 960 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
	    //Semantic Analyses
	    if ( !are_comparable((yyvsp[-2].attr_el)->type, (yyvsp[0].attr_el)->type) )
	    {
	        arey_galti_hai_kya = true;
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error ("Sem mein galti: Relational barabari barabar waalo k saath karo");
	    }

		//Code Generation
		if (!arey_galti_hai_kya){
		    (yyval.attr_el)->type = BOOL;
        (yyval.attr_el)->dakshina = (yyvsp[-2].attr_el)->dakshina;
        (yyval.attr_el)->dakshina += "sw $t0 0($sp) \n";
        (yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
        (yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;
        (yyval.attr_el)->dakshina += "lw $t1 4($sp)\n";
        (yyval.attr_el)->dakshina += "addiu $sp $sp 4\n";
	        if (daram((yyvsp[-1].node_con)) == daram("==") ){
	            (yyval.attr_el)->dakshina += "seq $t0 $t1 $t0\n";
	        }
	        else if (daram((yyvsp[-1].node_con)) == daram("<") ){
	            (yyval.attr_el)->dakshina += "slt $t0 $t1 $t0\n";
	        }
	        else if ( daram((yyvsp[-1].node_con)) == daram("<=")){
	            (yyval.attr_el)->dakshina += "sle $t0 $t1 $t0\n";
	        }
	        else if (daram((yyvsp[-1].node_con)) == daram(">")){
	            (yyval.attr_el)->dakshina += "sgt $t0 $t1 $t0\n";
	        }
	        else if (daram((yyvsp[-1].node_con)) == daram(">=")){
	            (yyval.attr_el)->dakshina += "sge $t0 $t1 $t0\n";
	        }
	        else if (daram((yyvsp[-1].node_con)) == daram("!=")){
	            (yyval.attr_el)->dakshina += "seq $t0 $t1 $t0\n";
	            (yyval.attr_el)->dakshina += "xori $t0 $t0 0x1\n";
	        }

		}
	}
#line 2484 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1002 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
        //Semantic Analyses
        if ( ((yyvsp[-2].attr_el)->type == CHAR || (yyvsp[0].attr_el)->type == CHAR) )
        {
            arey_galti_hai_kya = true;
            (yyval.attr_el)->type = ERR;
            pretty_print_error ("Sem mein galti: Gotcha !! char ko bool ki tarah mat use karo yaar.");
        }
        //Code Generation
        if (!arey_galti_hai_kya){
            (yyval.attr_el)->type = BOOL;

            (yyval.attr_el)->dakshina = (yyvsp[-2].attr_el)->dakshina;
            if ((yyvsp[-2].attr_el)->type == INT){
              (yyval.attr_el)->dakshina += intToBool();
            }
            (yyval.attr_el)->dakshina += "sw $t0 0($sp) \n";
            (yyval.attr_el)->dakshina += "addiu $sp $sp -4\n";
            (yyval.attr_el)->dakshina += (yyvsp[0].attr_el)->dakshina;

          if ((yyvsp[0].attr_el)->type == INT){
	            (yyval.attr_el)->dakshina += intToBool();
	        }
            (yyval.attr_el)->dakshina += "lw $t1 4($sp)\n";
            (yyval.attr_el)->dakshina += "addiu $sp $sp 4\n";

            if (daram((yyvsp[-1].node_con)) == daram("&&")){
                (yyval.attr_el)->dakshina += "and $t0 $t0 $t1\n";
            }
            else if (daram((yyvsp[-1].node_con)) == daram("||")){
                (yyval.attr_el)->dakshina += "or $t0 $t0 $t1\n";
            }

        }
	}
#line 2525 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1038 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el)  = new attr();
		if ((yyvsp[0].attr_el)->type == CHAR)
		{
		    arey_galti_hai_kya = true;
		    (yyval.attr_el)->type = ERR;
            pretty_print_error ("Sem mein galti: Phir se. !CHAR allowed nahe h bhai.");
		}

		//Code Generation
		if (!arey_galti_hai_kya){
        (yyval.attr_el)->type = BOOL;
		    (yyval.attr_el)->dakshina = (yyvsp[0].attr_el)->dakshina;
		    if ((yyvsp[0].attr_el)->type == INT){
		        (yyval.attr_el)->dakshina+= intToBool();
		    }
		    (yyval.attr_el)->dakshina += "xori $t0 $t0 0x1\n";
		}
	}
#line 2549 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1057 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
        //Semantic
        // if ($1->type == INT && $3->type == CHAR){
        //   cout << "pahuch gaya."<<endl;
        // }
        // cout << $1->type <<" \t " << $3->type <<endl;
        if ( ((yyvsp[-2].attr_el)->type == CHAR && (yyvsp[0].attr_el)->type != CHAR) || ((yyvsp[-2].attr_el)->type == BOOL && (yyvsp[0].attr_el)->type == CHAR ) )
        {
          (yyval.attr_el)->type = ERR;
	        (yyval.attr_el)->ival = -1;
	        pretty_print_error("Sem mein galti: equality: barabar waalo k saath");
	        arey_galti_hai_kya = true;
        }

        //Code Generation
        if (!arey_galti_hai_kya)
        {
            var_record *lhsRecord = get_record((yyvsp[-2].attr_el)->dakshina);
            (yyval.attr_el) -> dakshina = (yyvsp[0].attr_el)->dakshina;


            if ( cast((yyvsp[-2].attr_el)->type, (yyvsp[0].attr_el)->type, 0) == 2)
            {
                //CodeGen - no other casting test needed because only allowed downcast is from int to bool
                (yyval.attr_el)->dakshina += "#Casting of RHS\n";
                (yyval.attr_el)->dakshina += intToBool();
            }
            if ( (yyvsp[-2].attr_el)->type != ERR && (yyvsp[-2].attr_el)->dakshina == "$" )
            {
                lhsRecord = &active_func_ptr->param_list[(yyvsp[-2].attr_el)->ival];
                stringstream s;//int ko string karne ka aur koi raasta nahe mila
                s << lhsRecord->offset;
                (yyval.attr_el)->dakshina += "sw $t0 " + s.str() + "($fp) \n";
            }

            if ((yyvsp[-2].attr_el)->ival == -1 && (yyvsp[-2].attr_el)->type != ERR ){
                  //ID
                  (yyval.attr_el)->dakshina += store_mips_id(lhsRecord);

              }
              else if ((yyvsp[-2].attr_el)->type != ERR){
                  //ID[const]
                  (yyval.attr_el)->dakshina += store_mips_array(lhsRecord,(yyvsp[-2].attr_el)->ival);
              }
        }
	}
#line 2601 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1105 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error("Missing identifier peru"); }
#line 2607 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1109 "mad_parser.y" /* yacc.c:1646  */
    {
	   //Semantic Analyses
     (yyval.attr_el) = new attr();
	   (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[-2].attr_el));
	   if ( (yyvsp[0].attr_el)->type != ERR )
     {
    		if ((yyvsp[0].attr_el)->bval)
        {
        	call_param_list.push_back(& (call_name_ptr->param_list[(yyvsp[0].attr_el)->ival]) );
        }
       else
       {
       		call_param_list.push_back( get_record((yyvsp[0].attr_el)->label) );
       }
     }

	   //CodeGen


	}
#line 2632 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1129 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic Analyses
	   (yyval.attr_el) = new attr(); copy_attr((yyval.attr_el),(yyvsp[0].attr_el));
     if ( (yyvsp[0].attr_el)->type != ERR )
     {
    		if ((yyvsp[0].attr_el)->bval)
        {
        	call_param_list.push_back(& (call_name_ptr->param_list[(yyvsp[0].attr_el)->ival]) );
        }
       else
       {
       		call_param_list.push_back( get_record((yyvsp[0].attr_el)->label) );
       }
     }
    //  cout << "Last: " << call_param_list.back()->peru << endl ;
	   //CodeGen


	}
#line 2657 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1149 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic Analyses  - no checks needed
	   //CodeGen - nothing to do


	}
#line 2669 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1160 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses -> param
      (yyval.attr_el) = new attr();
	    var_record* id_rec = get_record((yyvsp[0].node_con));
	    if ( id_rec == NULL )
	    {
	        //Check if valid parameter
	        int flag = -1;
	        for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
	            if ( active_func_ptr->param_list[i].peru == (yyvsp[0].node_con) )
	                { flag = i; break; }
	        if (flag >= 0)
	        {
	            (yyval.attr_el)->type = active_func_ptr->param_list[flag].type;
	            (yyval.attr_el)->ival = flag;
	            (yyval.attr_el)->dakshina = "$";
	        }
	        else
	        {
	            (yyval.attr_el)->type = ERR;
    	        (yyval.attr_el)->ival = -1;
    	        pretty_print_error("Sem mein galti: Arey ID declare kar k use karo bhai");
    	        arey_galti_hai_kya = true;
	        }
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem Error:Don't try to access array as a unit scalar.");
	        arey_galti_hai_kya = true;
	    }
	    else
	    {
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->dakshina = (yyvsp[0].node_con);
	        (yyval.attr_el)->ival = -1;
	    }
	    //CodeGen
	    //No codegen



	}
#line 2717 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1203 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
        //Semantic Analyses
        var_record* id_rec = get_record((yyvsp[-3].node_con));
        if ( id_rec == NULL )
        {
            (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Arey ID declare kar k use karo bhai");
	        arey_galti_hai_kya = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Don't try to access scalar as an Array.");
	        arey_galti_hai_kya = true;
	    }
	    else
	    {
	        int iconst = atoi((yyvsp[-1].node_con));
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            (yyval.attr_el)->type = ERR;
	            pretty_print_error("Sem mein galti: Arre array se bahar chale gaye.");
	            arey_galti_hai_kya = true;
	        }
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->ival = iconst;
	        (yyval.attr_el)->dakshina = (yyvsp[-3].node_con);
	    }

        //CodeGen
        //No dakshina generated in this production


	}
#line 2757 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1240 "mad_parser.y" /* yacc.c:1646  */
    {
	   // Semantic
    (yyval.attr_el) = new attr();
    if (vyavadhi == 1)
    {
    	var_record id_rec;
      id_rec.is_param = true;
      id_rec.var_type = SIMPLE;
      id_rec.peru = (yyvsp[0].node_con);
      id_rec.vyavadhi = vyavadhi;
      id_rec.dim = 0;
      id_rec.type = ((yyvsp[-1].attr_el))->type;
      active_func_ptr->param_list.push_back(id_rec);
      (yyval.attr_el)->ival = active_func_ptr->param_list.size() - 1;
    }
    else
    {
       if( sym_table.count(vyavadhi) > 0 && sym_table[vyavadhi].count((yyvsp[0].node_con)) != 0 )
       {
            (yyval.attr_el)->type = ERR;
            pretty_print_error("Sem mein galti: Kripya is ID ko scope k bahar ja dobara declare karo.");
            arey_galti_hai_kya = true;
       }
       else
       {
              var_record id_rec;
         			id_rec.is_param = false;
              id_rec.var_type = SIMPLE;
              id_rec.peru = (yyvsp[0].node_con);
              id_rec.vyavadhi = vyavadhi;
              id_rec.dim = 0;
              id_rec.type = ((yyvsp[-1].attr_el))->type;
              if (!sym_table.count(vyavadhi))
              {
                map <daram,var_record> temp;
                temp[(yyvsp[0].node_con)] = id_rec;
                sym_table[vyavadhi] = temp;
              }
              else{
                sym_table[vyavadhi][(yyvsp[0].node_con)] = id_rec;
              }
         			(yyval.attr_el)->ival = -1;
              //cout << id_rec.type <<"\t"<<id_rec.peru<<"\n";
              // cout << $1 << " inserted." << endl;
       }

       //CodeGen
       sym_table[vyavadhi][(yyvsp[0].node_con)].mips_name = get_mips_name(&sym_table[vyavadhi][(yyvsp[0].node_con)]);
       mips_name.push_back( sym_table[vyavadhi][(yyvsp[0].node_con)] ); //For adding to data declarations
    }


	}
#line 2815 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1293 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic
	   if( sym_table.count(vyavadhi) > 0 && sym_table[vyavadhi].count((yyvsp[-3].node_con)) != 0 )
	   {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Kripya is ID ko scope k bahar ja dobara declare karo.");
	        arey_galti_hai_kya = true;
	   }
	   else
	   {
            var_record id_rec;
       			id_rec.is_param = false;
            id_rec.var_type = ARRAY;
            id_rec.peru = (yyvsp[-3].node_con);
            id_rec.vyavadhi = vyavadhi;
            id_rec.dim = atoi((yyvsp[-1].node_con));
            id_rec.type = (yyvsp[-4].attr_el)->type;
            sym_table[vyavadhi][(yyvsp[-3].node_con)] = id_rec;
	   }

       //CodeGen
     sym_table[vyavadhi][(yyvsp[-3].node_con)].mips_name = get_mips_name(&sym_table[vyavadhi][(yyvsp[-3].node_con)]);
	   mips_name.push_back(sym_table[vyavadhi][(yyvsp[-3].node_con)]); //For adding to data declarations


	}
#line 2847 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1322 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
      (yyval.attr_el) = new attr();
    	bool is_param = false;
    	int flag = -1;
	    var_record* id_rec = get_record((yyvsp[0].node_con));
	    if ( id_rec == NULL )
	    {
	        for ( int i = 0; i < active_func_ptr->param_list.size(); i++ )
	            if ( active_func_ptr->param_list[i].peru == (yyvsp[0].node_con) )
	                { flag = i;break; }
	        if (flag >= 0)
	        {
             	is_param = true;
	            (yyval.attr_el)->type = active_func_ptr->param_list[flag].type;
            	(yyval.attr_el)->bval = true;
            	(yyval.attr_el)->ival = flag; //Indicates parameter
              // cout << "var_use : " << active_func_ptr->param_list[flag].type << " " << active_func_ptr->param_list[flag].peru << " " << active_func_ptr->param_list[flag].offset <<endl;
	        }
        	else
          {
            (yyval.attr_el)->type = ERR;
            (yyval.attr_el)->bval = false;
            (yyval.attr_el)->ival = -1;
            pretty_print_error("Sem mein galti: Arey ID declare kar k use karo bhai");
            arey_galti_hai_kya = true;
          }
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Array accessed as scalar.");
	        arey_galti_hai_kya = true;
	    }
	    else
	    {

	        (yyval.attr_el)->type = id_rec->type;
        	(yyval.attr_el)->bval = false;        	//Indicates normal variable
	        (yyval.attr_el)->ival = -1;
        	(yyval.attr_el)->label = (yyvsp[0].node_con);
	    }

	    //CodeGen
	    if (!arey_galti_hai_kya){
	        //Check in local variables -> if not found, check in param list -> if found, load param by offset
          if ( is_param )
            {
                stringstream s;//int ko string karne ka aur koi raasta nahe mila
                s << active_func_ptr->param_list[flag].offset;
                (yyval.attr_el)->dakshina += "lw $t0 " + s.str() + "($fp) \n";
            }
          else{
              (yyval.attr_el)->dakshina = load_mips_id( get_record((yyvsp[0].node_con)) );
          }
	    }



	}
#line 2912 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1382 "mad_parser.y" /* yacc.c:1646  */
    {

        //Semantic Analyses
        (yyval.attr_el) = new attr();
        var_record* id_rec = get_record((yyvsp[-3].node_con));
        if ( id_rec == NULL )
        {
            (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Arey ID declare kar k use karo bhai");
	        arey_galti_hai_kya = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Sem mein galti: Arey scalar ko dekh k user karo, array nahe h woh.");
	        arey_galti_hai_kya = true;
	    }
	    else
	    {
	        int iconst = atoi((yyvsp[-1].node_con));
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            (yyval.attr_el)->type - ERR;
	            pretty_print_error("Sem mein galti: Array apne aukaat k bahar chala gya.");
	            arey_galti_hai_kya = true;
	        }
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->ival = iconst;
        	(yyval.attr_el)->label = (yyvsp[-3].node_con);
	    }

        //CodeGen
        if (!arey_galti_hai_kya){
            (yyval.attr_el)->dakshina = load_mips_array( get_record((yyvsp[-3].node_con)),atoi((yyvsp[-1].node_con)));
        }


	}
#line 2955 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1422 "mad_parser.y" /* yacc.c:1646  */
    {

	    //Semantic Analyses
        (yyval.attr_el) = new attr();
        (yyval.attr_el)->ival =  atoi((yyvsp[0].node_con));
        (yyval.attr_el)->type = INT;
        daram s = (yyvsp[0].node_con);
        (yyval.attr_el)->dakshina = "li $t0 " + s + "\n";

	    //CodeGen
	    //No codegen assoc with this production
    }
#line 2972 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1434 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
        (yyval.attr_el) = new attr();
        (yyval.attr_el)->cval =  *((yyvsp[0].node_con));
        (yyval.attr_el)->type = CHAR;

	    //CodeGen

        daram s = (yyvsp[0].node_con);
        (yyval.attr_el)->dakshina = "li $t0 \'" + s + "\' \n";



	}
#line 2991 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1448 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    if( !strcmp((yyvsp[0].node_con), "true") ){
          (yyval.attr_el)->bval = 1;
          (yyval.attr_el)->dakshina = "li $t0 1\n";
      }

	    else{
            (yyval.attr_el)->bval = 0;
            (yyval.attr_el)->dakshina = "li $t0 0\n";
      }

	    (yyval.attr_el)->type = BOOL;

        //Semantic Analyses
	    //CodeGen



	}
#line 3017 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1469 "mad_parser.y" /* yacc.c:1646  */
    {

	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    (yyval.attr_el)->ival = atoi((yyvsp[-1].node_con));
	    (yyval.attr_el)->ival = -((yyval.attr_el)->ival);
	    (yyval.attr_el)->type = INT;

	    //CodeGen
      (yyval.attr_el)->dakshina = "li $t0 -" + daram((yyvsp[-1].node_con)) + "\n" ;
	    //No codegen assoc with this production


	}
#line 3036 "mad_parser.tab.c" /* yacc.c:1646  */
    break;


#line 3040 "mad_parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1483 "mad_parser.y" /* yacc.c:1906  */

int num_times = 2;
void pretty_print_error(const char* err_msg)
{
	arey_galti_hai_kya = true;
	cout<<"Line "<<yylineno<<": "<<err_msg<<endl;
}

void print_tree(node *cur, /* pointer to list of ints   */ vector<int>& ancestors, int parent)
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
	if(!arey_galti_hai_kya)	cout<<""<<endl;
	else cout<<"Compilation terminating with errors"<<endl;
}
