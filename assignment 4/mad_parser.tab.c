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


#line 335 "mad_parser.tab.c" /* yacc.c:339  */

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
#line 270 "mad_parser.y" /* yacc.c:355  */

	struct attr* attr_el;
	node* node_el;
	char* node_con;

#line 416 "mad_parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAD_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 431 "mad_parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

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
       0,   319,   319,   320,   321,   324,   325,   328,   329,   332,
     333,   334,   337,   338,   339,   340,   343,   344,   355,   360,
     361,   362,   365,   366,   369,   370,   373,   374,   377,   378,
     379,   380,   381,   382,   385,   396,   397,   404,   413,   418,
     424,   425,   428,   474,   484,   495,   536,   550,   549,   596,
     613,   612,   671,   670,   725,   750,   751,   752,   755,   766,
     776,   784,   790,   819,   857,   892,   920,   953,   995,  1005,
    1017,  1033
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
  "mad_program", "supported_declarations", "variable_declarations",
  "variable_definitions", "dtype", "function_declarations",
  "argument_list", "statement_block", "variable_list", "statement_list",
  "supported_statement", "if_statement", "else_statement",
  "while_statement", "return_statement", "alr_subexpression", "@1", "@2",
  "@3", "id_list", "lhs", "var_decl", "var_use", "supported_constant", YY_NULLPTR
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

#define YYPACT_NINF -85

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-85)))

#define YYTABLE_NINF -65

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     162,   -15,    43,   -85,   -85,   -85,    51,    48,   -85,   196,
      52,   -85,   -85,    59,   -85,   -85,    85,    85,   -85,     0,
     -85,   178,    44,    66,   -85,   178,    77,   -85,    36,   102,
     -85,   116,   103,   120,    68,   124,   125,   125,   -85,   178,
     178,   178,    65,   -85,   -85,   -85,   -85,   -85,    65,    85,
      14,   -85,   118,    50,   131,   135,   131,   142,   145,   100,
     -85,   -85,   -85,   -85,     7,    14,   -85,   -85,   -85,   149,
     136,   139,   -85,   131,   112,   143,    63,   165,    91,   184,
     131,   131,   118,   -85,   169,   -85,   -85,   -85,   -85,   -85,
     163,   161,   170,   131,   131,    89,   184,   187,   172,    20,
     -85,   185,   -85,   -85,   -85,   164,   179,   -85,   -85,   131,
     131,   131,   -85,   184,   138,   112,   175,   192,   -85,   189,
     125,   125,   190,    57,   184,   -85,   203,   198,   -85,   188,
     -85,   -85,    96,   -85,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,     0,    12,    13,    14,     0,     0,     5,     0,
       0,     6,     4,     0,     1,     3,     8,     0,     7,    64,
       9,     0,    64,     0,    10,     0,     0,    15,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,    65,     0,
       0,     0,     0,    17,    16,    21,    20,    18,     0,     0,
       0,    25,     0,    66,     0,     0,     0,     0,     0,     0,
      70,    68,    69,    32,     0,     0,    29,    30,    31,     0,
       0,     0,    43,     0,     0,     0,    47,    68,    47,    54,
       0,     0,    40,    38,     0,    23,    22,    27,    33,    28,
       0,     0,     0,     0,     0,     0,    55,     0,    66,     0,
      59,     0,    46,    71,    49,    47,    47,    41,    39,     0,
       0,     0,    42,    56,     0,     0,     0,     0,    45,    67,
       0,     0,    48,    51,    53,    57,    61,     0,    58,    35,
      37,    67,     0,    34,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   205,   -85,   107,   -85,     5,   -85,    -7,   -36,   166,
     148,    78,   -85,   -85,   -85,   -85,   -52,   -85,   -85,   -85,
     -84,   -85,    -3,   -65,   -85
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    28,    11,    29,    63,    50,
      64,    65,    66,   133,    67,    68,    69,    90,    91,    92,
      99,    70,    20,    71,    72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    44,    76,    78,    79,    10,    25,    84,    85,   100,
      26,   114,    10,    23,    24,    52,    86,    53,    31,    12,
      54,    96,    42,   -26,   117,    35,    55,   118,   105,   106,
     100,   126,    45,    46,    47,    56,    57,    33,    58,    34,
      59,   112,   113,    60,    61,    62,    13,    49,    -2,     1,
     100,    14,   128,    49,    26,    19,    74,   122,   123,   124,
      75,     2,     3,     4,     5,    21,    27,   -62,   -24,    40,
     102,   -24,   -64,   -24,   -24,   -47,   -50,   -24,    26,     3,
       4,     5,   -50,   -52,   129,   130,   -24,   -24,    22,   -24,
      97,   -24,    98,   -60,   -24,   -24,   -24,    52,   104,    53,
      30,    82,    54,    53,    42,    83,    54,    32,    55,    36,
     -50,   -52,    55,    97,    38,    98,   -60,    56,    57,   -60,
      58,    56,    59,    37,    39,    60,    61,    62,    41,    60,
      61,    62,    52,    42,    53,    73,    52,    54,    53,   125,
      94,    54,   117,    55,   -44,    95,   -44,    55,    80,    48,
      88,    81,    56,    93,    89,    48,    56,   -44,   -44,   -44,
      60,    61,    62,     1,    60,    77,    62,   -47,   -50,   -52,
     107,   120,   103,   101,   108,     2,     3,     4,     5,    27,
     110,   109,   116,   -50,   -52,   -19,   121,   -47,   -50,   -52,
     111,   115,     3,     4,     5,    98,   119,    16,   -50,   -52,
      17,    18,   -47,   -50,   -52,   127,   -63,   117,   -47,   131,
     134,   132,    15,    87,    51
};

static const yytype_uint8 yycheck[] =
{
      36,    37,    54,    55,    56,     0,     6,    59,     1,    74,
      10,    95,     7,    16,    17,     1,     9,     3,    25,    34,
       6,    73,     8,     9,     4,    28,    12,     7,    80,    81,
      95,   115,    39,    40,    41,    21,    22,     1,    24,     3,
      26,    93,    94,    29,    30,    31,     3,    42,     0,     1,
     115,     0,   117,    48,    10,     3,     6,   109,   110,   111,
      10,    13,    14,    15,    16,     6,     1,    17,     3,     1,
       7,     6,     4,     8,     9,    18,    19,    12,    10,    14,
      15,    16,    19,    20,   120,   121,    21,    22,     3,    24,
       1,    26,     3,     4,    29,    30,    31,     1,     7,     3,
      34,     1,     6,     3,     8,     5,     6,    30,    12,     7,
      19,    20,    12,     1,    11,     3,     4,    21,    22,     7,
      24,    21,    26,     7,     4,    29,    30,    31,     4,    29,
      30,    31,     1,     8,     3,    17,     1,     6,     3,     1,
       1,     6,     4,    12,     5,     6,     7,    12,     6,    42,
       1,     6,    21,    17,     5,    48,    21,    18,    19,    20,
      29,    30,    31,     1,    29,    30,    31,    18,    19,    20,
       1,     7,     7,    30,     5,    13,    14,    15,    16,     1,
      19,    18,    10,    19,    20,     7,     7,    18,    19,    20,
      20,     4,    14,    15,    16,     3,    11,     1,    19,    20,
       4,     5,    18,    19,    20,    30,    17,     4,    18,    11,
     132,    23,     7,    65,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    13,    14,    15,    16,    36,    37,    38,    39,
      40,    41,    34,     3,     0,    36,     1,     4,     5,     3,
      57,     6,     3,    57,    57,     6,    10,     1,    40,    42,
      34,    42,    30,     1,     3,    57,     7,     7,    11,     4,
       1,     4,     8,    43,    43,    42,    42,    42,    38,    40,
      44,    44,     1,     3,     6,    12,    21,    22,    24,    26,
      29,    30,    31,    43,    45,    46,    47,    49,    50,    51,
      56,    58,    59,    17,     6,    10,    51,    30,    51,    51,
       6,     6,     1,     5,    51,     1,     9,    45,     1,     5,
      52,    53,    54,    17,     1,     6,    51,     1,     3,    55,
      58,    30,     7,     7,     7,    51,    51,     1,     5,    18,
      19,    20,    51,    51,    55,     4,    10,     4,     7,    11,
       7,     7,    51,    51,    51,     1,    55,    30,    58,    43,
      43,    11,    23,    48,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    36,    37,    37,    38,    38,    39,
      39,    39,    40,    40,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    47,    48,    48,    49,    50,    50,
      50,    50,    51,    51,    51,    51,    51,    52,    51,    51,
      53,    51,    54,    51,    51,    51,    51,    51,    55,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     2,     2,     2,
       3,     4,     1,     1,     1,     1,     6,     6,     4,     0,
       4,     4,     4,     4,     0,     2,     0,     2,     2,     1,
       1,     1,     1,     2,     6,     0,     2,     5,     2,     3,
       2,     3,     3,     1,     1,     4,     3,     0,     4,     3,
       0,     4,     0,     4,     2,     3,     3,     4,     3,     1,
       0,     3,     1,     4,     1,     4,     1,     4,     1,     1,
       1,     3
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
#line 319 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1618 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 320 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1624 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 321 "mad_parser.y" /* yacc.c:1646  */
    { pretty_print_error("Compilation terminating with errors"); root = NULL;}
#line 1630 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 324 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1636 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 325 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el);}
#line 1642 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 328 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("SEMI", TERMINAL);}
#line 1648 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 329 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error); }
#line 1654 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 332 "mad_parser.y" /* yacc.c:1646  */
    {cout<<"dtype var_decl"<<endl; (yyval.node_el) = as_tree_n("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el);}
#line 1660 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 333 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = as_tree_n("COMMA", TERMINAL); }
#line 1666 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 334 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error("Missing comma in definitions list"); }
#line 1672 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 337 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_INT", TERMINAL); /*$$->child = $1;*/}
#line 1678 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 338 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
#line 1684 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 339 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_CHAR", TERMINAL); /*$$->child = $1;*/}
#line 1690 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 340 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(type_error); }
#line 1696 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 343 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-5].node_el); node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyvsp[-5].node_el)->sibling = id; node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = (yyvsp[-2].node_el); node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen; closeparen->sibling = (yyvsp[0].node_el); }
#line 1702 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 344 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("VOID", TERMINAL);
		node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyval.node_el)->child->sibling = id;
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen;
		openparen->sibling = (yyvsp[-2].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[0].node_el);
	}
#line 1716 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 355 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("argument_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-3].node_el);
		/* $1->sibling = $2; //node* id = as_tree_n("ID", VALUE); id->info = $2;
		node* comma= as_tree_n("COMMA", TERMINAL); $2->sibling = comma; comma->sibling = $4; } |dtype ID {$$ = as_tree_n("argument_list", NONTERMINAL); $$->child = $1; node* id = as_tree_n("ID", VALUE); id->info = $2; $1->sibling = id;} */
  }
#line 1726 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 360 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1732 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 361 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(comma_error); }
#line 1738 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 362 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(identifier_error); }
#line 1744 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 365 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("statement_block", NONTERMINAL); (yyval.node_el)->child = as_tree_n("OPENCURLY", TERMINAL); (yyval.node_el)->child->sibling = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("CLOSECURLY", TERMINAL); }
#line 1750 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 366 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error("Possible missing semicolon in statement block"); }
#line 1756 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 369 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1762 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 370 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("variable_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); }
#line 1768 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 373 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("statement_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1774 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 374 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("statement_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el);}
#line 1780 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 377 "mad_parser.y" /* yacc.c:1646  */
    {cout<<(yyvsp[-1].attr_el)->code<<endl; (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL);}
#line 1786 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 378 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1792 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 379 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1798 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 380 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1804 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 381 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1810 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 382 "mad_parser.y" /* yacc.c:1646  */
    { pretty_print_error("Possible missing semicolon with alr_subexpression"); (yyval.node_el) = as_tree_n("error", TERMINAL); }
#line 1816 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 385 "mad_parser.y" /* yacc.c:1646  */
    { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		(yyval.node_el) = as_tree_n("if_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("IF", TERMINAL);
		/*node* openparen = as_tree_n("OPENPAREN", TERMINAL); $$->child->sibling = openparen;
		openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;
		closeparen->sibling = $5;
		$5->sibling = $6;*/
	}
#line 1830 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 396 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("else_statement", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1836 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 397 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("else_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("ELSE", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[0].node_el);
	}
#line 1846 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 404 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("while_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("WHILE", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		/*openparen->sibling = $3;
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $3->sibling = closeparen;*/
	}
#line 1858 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 413 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("return_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("RETURN", TERMINAL);
		node* semi = as_tree_n("SEMI", TERMINAL); (yyval.node_el)->child->sibling = semi;
	}
#line 1868 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 418 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("return_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("RETURN", TERMINAL);
		/*$$->child->sibling = $2;
		node* semi = as_tree_n("SEMI", TERMINAL); $2->sibling = semi;*/
	}
#line 1879 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 424 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL);pretty_print_error(semicolon_error_return); }
#line 1885 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 425 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error_return); }
#line 1891 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 428 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
        //Semantic
        if ( cast((yyvsp[-2].attr_el)->type, (yyvsp[0].attr_el)->type, 0) <  0)
        {
          (yyval.attr_el)->type = ERR;
	        (yyval.attr_el)->ival = -1;
	        pretty_print_error("Semantic Error: Incompatible types in equality assignment");
	        has_error = true;
        }


        //Code Generation
        if (!has_error)
        {
            var_record *lhsRecord = get_record((yyvsp[-2].attr_el)->code);
            (yyval.attr_el) -> code = (yyvsp[0].attr_el)->code;
            cout << (yyvsp[-2].attr_el) ->type << "\t" << (yyvsp[0].attr_el)->type <<"\t" << cast((yyvsp[-2].attr_el)->type,(yyvsp[0].attr_el)->type,0) << endl;
            if ( cast((yyvsp[-2].attr_el)->type, (yyvsp[0].attr_el)->type, 0) == 2)
            {
                //CodeGen - no other casting test needed because only allowed downcast is from int to bool
                (yyval.attr_el)->code += "#Casting of RHS";
                (yyval.attr_el)->code += intToBool();
            }
            else{
              if ((yyvsp[-2].attr_el)->ival == -1 && (yyvsp[-2].attr_el)->type != ERR ){
                  //ID

                  (yyval.attr_el)->code += store_mips_id(lhsRecord);

              }
              else if ((yyvsp[-2].attr_el)->type != ERR){
                  //ID[const]
                  (yyval.attr_el)->code += store_mips_array(lhsRecord,(yyvsp[-2].attr_el)->ival);
              }
            }


        }

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* openparen = as_tree_n("EQ", TERMINAL); $$->child->sibling = openparen;
// 		openparen->sibling = $3;
	}
#line 1942 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 474 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
	   //Semantic analyses - Nothing to check
	   (yyval.attr_el) = (yyvsp[0].attr_el);

	   //CodeGen - Nothing to do

	   // Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
#line 1957 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 484 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();

	   //Semantic analyses - Nothing to check
	   (yyval.attr_el) = (yyvsp[0].attr_el);

	   //CodeGen - Nothing to do

	   //Tree stuff
	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL); $$->child = $1;
	}
#line 1973 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 495 "mad_parser.y" /* yacc.c:1646  */
    { //Function call

          (yyval.attr_el)= new attr();
        //Semantic analyses
        if ( func_table.count((yyvsp[-3].node_con)) == 0 )
        {
            (yyval.attr_el)->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Function not declared");
        }
        else if ( func_table[(yyvsp[-3].node_con)].param_list.size() != (yyvsp[-1].attr_el)->types.size() )
        {
            (yyval.attr_el)->type = ERR;
            has_error = true;
            pretty_print_error("Semantic error: Parameter list length mismatch");
        }
        else
        {
            for ( int i = 0; i < (yyvsp[-1].attr_el)->types.size(); i++ )
            {
                if ( (yyvsp[-1].attr_el)->types[i] != func_table[(yyvsp[-3].node_con)].param_list[i].type )
                {
                    has_error = true;
                    (yyval.attr_el)->type = ERR;
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
#line 2019 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 536 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
		//Semantic Analyses - no checks needed
		//CodeGen
		(yyval.attr_el) = (yyvsp[-1].attr_el);

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("OPENPAREN", TERMINAL);
// 		$$->child->sibling = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;

	}
#line 2037 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 550 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
	    //Code Generation
      (yyval.attr_el) = new attr();
	        if (!has_error){
	            (yyval.attr_el)->code = ((yyvsp[-1].attr_el))->code;
    	        (yyval.attr_el)->code += "sw $t0 0($s0) \n";
    	        (yyval.attr_el)->code += "addiu $sp $sp -4\n";
	        }
	    }
#line 2052 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 561 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
	    //Semantic Analyses
	    if (cast((yyvsp[-3].attr_el)->type, (yyvsp[0].attr_el)->type, 1) < 0)
	    {
	        has_error = 1;
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error ("Semantic error: Arithmetic operation on incompatible types");
	    }

	    //Code Generation
	    if (!has_error){
	        (yyval.attr_el)->code = (yyvsp[-2].attr_el)->code;
	        (yyval.attr_el)->code += (yyvsp[0].attr_el)->code;
            (yyval.attr_el)->code += "lw $t1 4($sp)\n";
            (yyval.attr_el)->code += "addiu $sp $sp 4\n";
	        if ((yyvsp[-1].node_con) == "+"){
	            (yyval.attr_el)->code += "add $t0 $t0 $t1\n";
	        }
	        else if ((yyvsp[-1].node_con) == "-"){
	            (yyval.attr_el)->code += "sub $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == "*"){
	            (yyval.attr_el)->code += "mul $t0 $t0 $t1\n";
	        }
	        else if ((yyvsp[-1].node_con) == "/"){
	            (yyval.attr_el)->code += "div $t0 $t1 $t0\n";
	        }
	    }

	   // $$ = as_tree_n("alr_subexpression", NONTERMINAL);
	   // $$->child = $1; $1->sibling= as_tree_n("ARITH", VALUE);
	   // $1->sibling->info = $2;
	   // $1->sibling->sibling = $3;
	}
#line 2092 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 596 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el)= new attr();
		//Semantic analyses - no checks
		(yyval.attr_el) = (yyvsp[-1].attr_el);
		//Code gen
		if(!has_error){
		    (yyval.attr_el)->code += "neg $t0 $t0 \n";
		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("OPENNEGATE", TERMINAL);
// 		$$->child->sibling = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); $2->sibling = closeparen;

	}
#line 2113 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 613 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses - no checks
	    //Code Generation
      (yyval.attr_el) = new attr();
	        if (!has_error){
	            (yyval.attr_el)->code = ((yyvsp[-1].attr_el))->code;
    	        (yyval.attr_el)->code += "sw $t0 0($s0) \n";
    	        (yyval.attr_el)->code += "addiu $sp $sp -4\n";
	        }
	    }
#line 2128 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 624 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
	    //Semantic Analyses
	    if ( !are_comparable((yyvsp[-3].attr_el)->type, (yyvsp[0].attr_el)->type) )
	    {
	        has_error = true;
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error ("Semantic error: Relational operator between incompatible types");
	    }

		//Code Generation
		if (!has_error){
		    (yyval.attr_el)->type = BOOL;
		    (yyval.attr_el)->code = (yyvsp[-2].attr_el)->code;
	        (yyval.attr_el)->code += (yyvsp[0].attr_el)->code;
            (yyval.attr_el)->code += "lw $t1 4($sp)\n";
            (yyval.attr_el)->code += "addiu $sp $sp 4\n";
	        if ((yyvsp[-1].node_con) == "=="){
	            (yyval.attr_el)->code += "seq $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == "<"){
	            (yyval.attr_el)->code += "slt $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == "<="){
	            (yyval.attr_el)->code += "sle $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == ">"){
	            (yyval.attr_el)->code += "sgt $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == ">="){
	            (yyval.attr_el)->code += "sge $t0 $t1 $t0\n";
	        }
	        else if ((yyvsp[-1].node_con) == "!="){
	            (yyval.attr_el)->code += "seq $t0 $t1 $t0\n";
	            (yyval.attr_el)->code += "xori $t0 $t0 0x1\n";
	        }

		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* reln = as_tree_n("RELN", VALUE); reln->info = $2;$1->sibling = reln;
// 		reln->sibling = $3;
	}
#line 2178 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 671 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
	    //Semantic Analyses - no checks
	    if ((yyval.attr_el)->type == CHAR){
	        has_error = true;
	    }
	    //Code Generation

	        if (!has_error){
	            (yyval.attr_el)->code = ((yyvsp[-1].attr_el))->code;
	            if ((yyval.attr_el)->type == INT){
	                (yyval.attr_el)->code += intToBool();
	            }
    	        (yyval.attr_el)->code += "sw $t0 0($s0) \n";
    	        (yyval.attr_el)->code += "addiu $sp $sp -4\n";
	        }
	    }
#line 2200 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 688 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
        //Semantic Analyses
        if ( ((yyvsp[-3].attr_el)->type == CHAR || (yyvsp[0].attr_el)->type == CHAR) )
        {
            has_error = true;
            (yyval.attr_el)->type = ERR;
            pretty_print_error ("Semantic Error: Logical comparison with a CHAR type");
        }


        //Code Generation
        if (!has_error){
            (yyval.attr_el)->type = BOOL;
            (yyval.attr_el)->code = (yyvsp[-2].attr_el)->code;
	        (yyval.attr_el)->code += (yyvsp[0].attr_el)->code;
	        if ((yyvsp[0].attr_el)->type == INT){
	            (yyval.attr_el)->code += intToBool();
	        }
            (yyval.attr_el)->code += "lw $t1 4($sp)\n";
            (yyval.attr_el)->code += "addiu $sp $sp 4\n";

            if ((yyvsp[-1].node_con) == "&&"){
                (yyval.attr_el)->code += "and $t0 $t0 $t1\n";
            }
            else if ((yyvsp[-1].node_con) == "||"){
                (yyval.attr_el)->code += "or $t0 $t0 $t1\n";
            }

        }

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = $1;
// 		node* reln = as_tree_n("LOGICAL", VALUE);reln->info=$2; $1->sibling = reln;
// 		reln->sibling = $3;
	}
#line 2242 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 725 "mad_parser.y" /* yacc.c:1646  */
    {
    (yyval.attr_el)  = new attr();
		if ((yyvsp[0].attr_el)->type == CHAR)
		{
		    has_error = true;
		    (yyval.attr_el)->type = ERR;
            pretty_print_error ("Semantic Error: Logical NOT on CHAR type");
		}

		//Code Generation
		if (!has_error){
		    (yyval.attr_el)->code = (yyvsp[0].attr_el)->code;
		    if ((yyvsp[0].attr_el)->type == INT){
		        (yyval.attr_el)->code+= intToBool();
		    }
		    (yyval.attr_el)->code += "xori $t0 $t0 0x1\n";
		}

//      Tree stuff
// 		$$ = as_tree_n("alr_subexpression", NONTERMINAL);
// 		$$->child = as_tree_n("LOGICALNOT", VALUE); $$->child->info = "!";
// 		$$->child->sibling = $2;

	}
#line 2271 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 750 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error("Missing identifier name"); }
#line 2277 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 751 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error("Possible missing equalty sign"); }
#line 2283 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 752 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.attr_el) = new attr(); (yyval.attr_el)->type = ERR; pretty_print_error("Possible missing closing parenthesis"); }
#line 2289 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 755 "mad_parser.y" /* yacc.c:1646  */
    {
	   //Semantic Analyses
     (yyval.attr_el) = new attr();
	   (yyval.attr_el) = (yyvsp[-2].attr_el);
	   (yyval.attr_el)->types.push_back((yyvsp[0].attr_el)->type);

	   //CodeGen

	   //Tree stuff
	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1; node *comma = as_tree_n("COMMA", TERMINAL); $$->child->sibling = comma; comma->sibling = $3;
	}
#line 2305 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 766 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic Analyses
	   (yyval.attr_el) = (yyvsp[0].attr_el);
	   (yyval.attr_el)->types.push_back((yyvsp[0].attr_el)->type);

	   //CodeGen

	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = $1;
	}
#line 2320 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 776 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic Analyses  - no checks needed
	   //CodeGen - nothing to do

	   // $$ = as_tree_n("id_list", NONTERMINAL); $$->child = as_tree_n("EPSILON", TERMINAL);
	}
#line 2332 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 784 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	    (yyval.attr_el)->type = ERR; pretty_print_error("Missing identifier name");
	}
#line 2341 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 790 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    var_record* id_rec = get_record((yyvsp[0].node_con));
	    if ( id_rec == NULL )
	    {
	        (yyval.attr_el)->type = ERR;
	        (yyval.attr_el)->ival = -1;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: Array accessed as scalar.");
	        has_error = true;
	    }
	    else
	    {
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->code = (yyvsp[0].node_con);
	        (yyval.attr_el)->ival = -1;
	    }
	    //CodeGen
	    //No codegen

	    //Tree-related stuff
	    // $$ = as_tree_n("use_ID", NONTERMINAL); $$->info = "use_ID";
	}
#line 2375 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 819 "mad_parser.y" /* yacc.c:1646  */
    {
        (yyval.attr_el) = new attr();
        //Semantic Analyses
        var_record* id_rec = get_record((yyvsp[-3].node_con));
        if ( id_rec == NULL )
        {
            (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: Scalar accessed as array.");
	        has_error = true;
	    }
	    else
	    {
	        int iconst = atoi((yyvsp[-1].node_con));
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            (yyval.attr_el)->type - ERR;
	            pretty_print_error("Semantic Error: Array dimensions violated.");
	            has_error = true;
	        }
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->ival = iconst;
	        (yyval.attr_el)->code = (yyvsp[-3].node_con);
	    }

        //CodeGen
        //No code generated in this production

        //Tree-related stuff
	    // $$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";
	}
#line 2416 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 857 "mad_parser.y" /* yacc.c:1646  */
    {
	   // Semantic
    (yyval.attr_el) = new attr();
     if( sym_table.count(scope) > 0 && sym_table[scope].count((yyvsp[0].node_con)) != 0 )
	   {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: ID redeclaration in same scope.");
	        has_error = true;
	   }
	   else
	   {
            var_record id_rec;
            id_rec.var_type = SIMPLE;
            id_rec.name = (yyvsp[0].node_con);
            id_rec.scope = scope;
            id_rec.dim = 0;
            id_rec.type = (yyval.attr_el)->type;
            if (!sym_table.count(scope))
            {
              map <string,var_record> temp;
              temp[(yyvsp[0].node_con)] = id_rec;
              sym_table[scope] = temp;
            }
            else{
              sym_table[scope][(yyvsp[0].node_con)] = id_rec;
            }
            // cout << $1 << " inserted." << endl;
	   }

	   //CodeGen
	   mips_name.insert(get_mips_name(&sym_table[scope][(yyvsp[0].node_con)])); //For adding to data declarations

       //Tree stuff
	   // $$ = as_tree_n("decl_ID", NONTERMINAL); $$->info = "decl_ID";
	}
#line 2456 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 892 "mad_parser.y" /* yacc.c:1646  */
    {
      (yyval.attr_el) = new attr();
	   //Semantic
	   if( sym_table.count(scope) > 0 && sym_table[scope].count((yyvsp[-3].node_con)) != 0 )
	   {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: ID redeclaration in same scope.");
	        has_error = true;
	   }
	   else
	   {
            var_record id_rec;
            id_rec.var_type = ARRAY;
            id_rec.name = (yyvsp[-3].node_con);
            id_rec.scope = scope;
            id_rec.dim = atoi((yyvsp[-1].node_con));
            id_rec.type = (yyval.attr_el)->type;
            sym_table[scope][(yyvsp[-3].node_con)] = id_rec;
	   }

       //CodeGen
	   mips_name.insert(get_mips_name(&sym_table[scope][(yyvsp[-3].node_con)])); //For adding to data declarations

	   //Tree stuff
	   // $$ = as_tree_n("decl_ID[arr]", NONTERMINAL); $$->info = "decl_ID[arr]";
	}
#line 2487 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 920 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    var_record* id_rec = get_record((yyvsp[0].node_con));
	    if ( id_rec == NULL )
	    {
	        (yyval.attr_el)->type = ERR;
	        (yyval.attr_el)->ival = -1;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
	    }
	    else if ( id_rec->var_type != SIMPLE )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: Array accessed as scalar.");
	        has_error = true;
	    }
	    else
	    {
        cout << (yyvsp[0].node_con) << id_rec->type <<endl;
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->ival = -1;
	    }

	    //CodeGen
	    if (!has_error){
	        (yyval.attr_el)->code = load_mips_id( get_record((yyvsp[0].node_con)) );
	    }


	    //Tree-related stuff
	    // $$ = as_tree_n("use_ID", NONTERMINAL); $$->info = "use_ID";
	}
#line 2525 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 953 "mad_parser.y" /* yacc.c:1646  */
    {

        //Semantic Analyses
        (yyval.attr_el) = new attr();
        var_record* id_rec = get_record((yyvsp[-3].node_con));
        if ( id_rec == NULL )
        {
            (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: ID not declared before use");
	        has_error = true;
        }
        else if ( id_rec->var_type != ARRAY )
	    {
	        (yyval.attr_el)->type = ERR;
	        pretty_print_error("Semantic Error: Scalar accessed as array.");
	        has_error = true;
	    }
	    else
	    {
	        int iconst = atoi((yyvsp[-1].node_con));
	        if(iconst < 0 || iconst >= id_rec->dim)
	        {
	            (yyval.attr_el)->type - ERR;
	            pretty_print_error("Semantic Error: Array dimensions violated.");
	            has_error = true;
	        }
	        (yyval.attr_el)->type = id_rec->type;
	        (yyval.attr_el)->ival = iconst;


	    }

        //CodeGen
        if (!has_error){
            (yyval.attr_el)->code = load_mips_array( get_record((yyvsp[-3].node_con)),atoi((yyvsp[-1].node_con)));
        }

        //Tree-related stuff
	    // $$ = as_tree_n("use_ID[arr]", NONTERMINAL); $$->info = "use_ID[arr]";
	}
#line 2570 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 995 "mad_parser.y" /* yacc.c:1646  */
    {

	    //Semantic Analyses
        (yyval.attr_el) = new attr();
        (yyval.attr_el)->ival =  atoi((yyvsp[0].node_con));
        (yyval.attr_el)->type = INT;

	    //CodeGen
	    //No codegen assoc with this production
    }
#line 2585 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1005 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
        (yyval.attr_el) = new attr();
        (yyval.attr_el)->cval =  *((yyvsp[0].node_con));
        (yyval.attr_el)->type = CHAR;
	    //CodeGen

	    //No codegen assoc with this production

	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("INTCONST", VALUE); $$->child->info = $1;
	}
#line 2602 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1017 "mad_parser.y" /* yacc.c:1646  */
    {
	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    if( !strcmp((yyvsp[0].node_con), "true") )
	        (yyval.attr_el)->bval = 1;
	    else
	        (yyval.attr_el)->bval = 0;
	    (yyval.attr_el)->type = BOOL;

        //Semantic Analyses
	    //CodeGen
	    //No codegen assoc with this production

	    //Tree-related stuff
	    // $$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("BOOLCONST", VALUE); $$->child->info = $1;
	}
#line 2623 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1033 "mad_parser.y" /* yacc.c:1646  */
    {

	    //Semantic Analyses
      (yyval.attr_el) = new attr();
	    (yyval.attr_el)->ival = atoi((yyvsp[-1].node_con));
	    (yyval.attr_el)->ival = -((yyval.attr_el)->ival);
	    (yyval.attr_el)->type = INT;

	    //CodeGen
	    //No codegen assoc with this production

		//Tree-related stuff
// 		$$ = as_tree_n("supported_constant", NONTERMINAL); $$->child = as_tree_n("OPENNEGATE", TERMINAL);
// 		node* intconst = as_tree_n("INTCONST", VALUE); $$->child->sibling = intconst;intconst->info = $2;
// 		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}
#line 2644 "mad_parser.tab.c" /* yacc.c:1646  */
    break;


#line 2648 "mad_parser.tab.c" /* yacc.c:1646  */
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
#line 1049 "mad_parser.y" /* yacc.c:1906  */

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
