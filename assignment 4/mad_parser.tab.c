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


#line 113 "mad_parser.tab.c" /* yacc.c:339  */

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
    DTYPE_FLOAT = 271,
    DTYPE_CHAR = 272,
    EQ = 273,
    ARITH = 274,
    RELN = 275,
    LOGICAL = 276,
    LOGICALNOT = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    FOR = 281,
    RETURN = 282,
    PRINT = 283,
    READ = 284,
    BOOLCONST = 285,
    INTCONST = 286,
    TERMINAL = 1,
    VALUE = 2
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 48 "mad_parser.y" /* yacc.c:355  */

	int dtype_int;
	bool dtype_bool;
	int opertype_int;
	node* node_el;
	char* node_con;

#line 196 "mad_parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAD_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 211 "mad_parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

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
       0,    99,    99,   100,   101,   104,   105,   108,   109,   112,
     113,   114,   117,   118,   119,   120,   121,   124,   125,   136,
     139,   139,   140,   141,   144,   145,   148,   149,   152,   153,
     156,   157,   158,   159,   160,   161,   164,   175,   176,   183,
     192,   197,   203,   204,   207,   213,   214,   215,   222,   228,
     229,   235,   241,   247,   252,   253,   254,   257,   258,   259,
     260,   263,   264,   265
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
  "DTYPE_FLOAT", "DTYPE_CHAR", "EQ", "ARITH", "RELN", "LOGICAL",
  "LOGICALNOT", "IF", "ELSE", "WHILE", "FOR", "RETURN", "PRINT", "READ",
  "BOOLCONST", "INTCONST", "TERMINAL", "VALUE", "'\\n'", "$accept",
  "mad_program", "supported_declarations", "variable_declarations",
  "variable_definitions", "dtype", "function_declarations",
  "argument_list", "statement_block", "variable_list", "statement_list",
  "supported_statement", "if_statement", "else_statement",
  "while_statement", "return_statement", "alr_subexpression", "id_list",
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

#define YYPACT_NINF -45

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-45)))

#define YYTABLE_NINF -60

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     147,   -29,     9,   -45,   -45,   -45,   -45,    21,     3,   -45,
     180,    35,   -45,   -45,    18,   -45,   -45,    44,    51,   -45,
      58,   158,    16,   -45,   158,   -45,    32,    60,   -45,    65,
      76,    78,    81,    81,   158,   158,   158,    43,   -45,   -45,
     -45,   -45,   -45,    43,    83,    75,   -45,   -45,    85,     8,
     110,   122,   110,    88,    90,    31,   -45,   -45,   -45,    47,
      75,   -45,   -45,   -45,   126,   -45,   110,   110,   123,   110,
     100,    94,   130,   170,   110,   110,    85,   -45,   137,   -45,
     -45,   -45,   -45,   -45,   110,   110,   110,   170,   170,   104,
     111,    62,   170,   -45,   -45,   -45,   148,   159,   -45,   -45,
     170,   170,   170,   123,   123,   -45,   -45,    81,   -45,   -45,
     -45,    80,    87,   -45,   -45
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,     0,    12,    13,    14,    15,     0,     0,     5,
       0,     0,     6,     4,     0,     1,     3,     8,     0,     7,
       9,     0,     0,    10,     0,    16,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    17,
      23,    22,    19,     0,     0,     0,    27,     9,     0,     0,
       0,     0,     0,     0,     0,     0,    62,    61,    34,     0,
       0,    31,    32,    33,     0,    45,     0,     0,     0,     0,
       0,    61,     0,    53,     0,     0,    42,    40,     0,    25,
      24,    29,    35,    30,     0,     0,     0,    54,    55,     0,
      58,     0,    44,    48,    63,    50,     0,     0,    43,    41,
      49,    51,    52,     0,     0,    56,    47,     0,    39,    60,
      57,    37,     0,    36,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -45,   121,   -45,    34,   -45,     2,   -45,   152,   -32,    92,
      73,    24,   -45,   -45,   -45,   -45,   -44,   -12,   -45
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    26,    12,    27,    58,    45,
      59,    60,    61,   113,    62,    63,    64,    91,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      38,    39,    11,    -2,     1,    13,    70,    72,    73,    67,
      11,    78,    14,   -46,    68,   -46,     2,     3,     4,     5,
       6,    15,    87,    88,    21,    92,    69,   -46,   -46,   -46,
      96,    97,    76,    30,    49,    31,    77,    50,    20,    44,
     100,   101,   102,    51,    25,    44,   -26,    22,    79,   -26,
      28,   -26,   -26,    52,    23,   -26,    80,     3,     4,     5,
       6,    56,    57,   105,    24,   -26,   -26,    32,   -26,   106,
     -26,    43,    33,   -26,   -26,   111,    48,    43,    49,    35,
      34,    50,    36,    37,   -28,   -20,    47,    51,    48,    37,
      49,   109,   110,    50,    74,    37,    75,    52,    53,    51,
      54,    94,    55,    66,   112,    56,    57,    93,   103,    52,
      53,    48,    54,    49,    55,   104,    50,    56,    57,    84,
      85,    86,    51,    48,    89,    49,    90,    82,    50,    16,
     -59,    83,    52,    81,    51,    46,   114,    95,    98,     0,
      56,    57,    99,     0,    52,    84,    85,    86,     1,    84,
      85,    86,    56,    71,     0,   107,    84,    85,    86,    25,
       2,     3,     4,     5,     6,   -21,   108,    84,    85,    86,
       0,     0,     3,     4,     5,     6,    29,     0,    84,    85,
      86,    17,     0,     0,    18,    19,    40,    41,    42,    84,
      85,    86
};

static const yytype_int8 yycheck[] =
{
      32,    33,     0,     0,     1,    34,    50,    51,    52,     1,
       8,    55,     3,     5,     6,     7,    13,    14,    15,    16,
      17,     0,    66,    67,     6,    69,    18,    19,    20,    21,
      74,    75,     1,     1,     3,     3,     5,     6,     3,    37,
      84,    85,    86,    12,     1,    43,     3,     3,     1,     6,
      34,     8,     9,    22,     3,    12,     9,    14,    15,    16,
      17,    30,    31,     1,     6,    22,    23,     7,    25,     7,
      27,    37,     7,    30,    31,   107,     1,    43,     3,     1,
       4,     6,     4,     8,     9,     7,     3,    12,     1,     8,
       3,   103,   104,     6,     6,     8,     6,    22,    23,    12,
      25,     7,    27,    18,    24,    30,    31,     7,     4,    22,
      23,     1,    25,     3,    27,     4,     6,    30,    31,    19,
      20,    21,    12,     1,     1,     3,     3,     1,     6,     8,
       7,     5,    22,    60,    12,    43,   112,     7,     1,    -1,
      30,    31,     5,    -1,    22,    19,    20,    21,     1,    19,
      20,    21,    30,    31,    -1,     7,    19,    20,    21,     1,
      13,    14,    15,    16,    17,     7,     7,    19,    20,    21,
      -1,    -1,    14,    15,    16,    17,    24,    -1,    19,    20,
      21,     1,    -1,    -1,     4,     5,    34,    35,    36,    19,
      20,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    13,    14,    15,    16,    17,    36,    37,    38,
      39,    40,    41,    34,     3,     0,    36,     1,     4,     5,
       3,     6,     3,     3,     6,     1,    40,    42,    34,    42,
       1,     3,     7,     7,     4,     1,     4,     8,    43,    43,
      42,    42,    42,    38,    40,    44,    44,     3,     1,     3,
       6,    12,    22,    23,    25,    27,    30,    31,    43,    45,
      46,    47,    49,    50,    51,    53,    18,     1,     6,    18,
      51,    31,    51,    51,     6,     6,     1,     5,    51,     1,
       9,    45,     1,     5,    19,    20,    21,    51,    51,     1,
       3,    52,    51,     7,     7,     7,    51,    51,     1,     5,
      51,    51,    51,     4,     4,     1,     7,     7,     7,    52,
      52,    43,    24,    48,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    36,    37,    37,    38,    38,    39,
      39,    39,    40,    40,    40,    40,    40,    41,    41,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    47,    48,    48,    49,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    52,
      52,    53,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     2,     2,     2,
       3,     4,     1,     1,     1,     1,     1,     6,     6,     4,
       2,     0,     4,     4,     4,     4,     0,     2,     0,     2,
       2,     1,     1,     1,     1,     2,     6,     0,     2,     4,
       2,     3,     2,     3,     3,     1,     1,     4,     3,     3,
       3,     3,     3,     2,     3,     3,     4,     3,     1,     0,
       3,     1,     1,     3
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
#line 99 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1383 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 100 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1389 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 101 "mad_parser.y" /* yacc.c:1646  */
    { pretty_print_error("Compilation terminating with errors"); root = NULL;}
#line 1395 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 104 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1401 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 105 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el);}
#line 1407 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("SEMI", TERMINAL);}
#line 1413 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 109 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error); }
#line 1419 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 112 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("ID", VALUE); (yyvsp[-1].node_el)->sibling->info = (yyvsp[0].node_con);}
#line 1425 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 113 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = as_tree_n("COMMA", TERMINAL); (yyvsp[-2].node_el)->sibling->sibling = as_tree_n("ID", VALUE); (yyvsp[-2].node_el)->sibling->sibling->info = (yyvsp[0].node_con); }
#line 1431 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error("Missing comma in definitions list"); }
#line 1437 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 117 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_INT", TERMINAL); /*$$->child = $1;*/}
#line 1443 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 118 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
#line 1449 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 119 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_FLOAT", TERMINAL); /*$$->child = $1;*/}
#line 1455 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 120 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("DTYPE_CHAR", TERMINAL); /*$$->child = $1;*/}
#line 1461 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 121 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(type_error); }
#line 1467 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 124 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-5].node_el); node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyvsp[-5].node_el)->sibling = id; node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = (yyvsp[-2].node_el); node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen; closeparen->sibling = (yyvsp[0].node_el); }
#line 1473 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 125 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("VOID", TERMINAL);
		node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyval.node_el)->child->sibling = id;
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); id->sibling = openparen;
		openparen->sibling = (yyvsp[-2].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[0].node_el);
	}
#line 1487 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 136 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("argument_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-3].node_el);
		node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[-2].node_con); (yyvsp[-3].node_el)->sibling = id;
		node* comma= as_tree_n("COMMA", TERMINAL); id->sibling = comma; comma->sibling = (yyvsp[0].node_el); }
#line 1496 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 139 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("argument_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); node* id = as_tree_n("ID", VALUE); id->info = (yyvsp[0].node_con); (yyvsp[-1].node_el)->sibling = id;}
#line 1502 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("function_declarations", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1508 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 140 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(comma_error); }
#line 1514 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 141 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(identifier_error); }
#line 1520 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 144 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("statement_block", NONTERMINAL); (yyval.node_el)->child = as_tree_n("OPENCURLY", TERMINAL); (yyval.node_el)->child->sibling = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("CLOSECURLY", TERMINAL); }
#line 1526 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 145 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error("Possible missing semicolon in statement block"); }
#line 1532 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 148 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("variable_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1538 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 149 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("variable_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); }
#line 1544 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 152 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("statement_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1550 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 153 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("statement_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el);}
#line 1556 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 156 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = as_tree_n("SEMI", TERMINAL);}
#line 1562 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 157 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1568 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 158 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1574 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 159 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1580 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 160 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1586 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 161 "mad_parser.y" /* yacc.c:1646  */
    { pretty_print_error("Possible missing semicolon with alr_subexpression"); (yyval.node_el) = as_tree_n("error", TERMINAL); }
#line 1592 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 164 "mad_parser.y" /* yacc.c:1646  */
    { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		(yyval.node_el) = as_tree_n("if_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("IF", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-3].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-3].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[-1].node_el);
		(yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el);
	}
#line 1606 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 175 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("else_statement", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1612 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 176 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("else_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("ELSE", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[0].node_el);
	}
#line 1622 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 183 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("while_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("WHILE", TERMINAL);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-1].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1634 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 192 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("return_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("RETURN", TERMINAL);
		node* semi = as_tree_n("SEMI", TERMINAL); (yyval.node_el)->child->sibling = semi;
	}
#line 1644 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 197 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("return_statement", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("RETURN", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* semi = as_tree_n("SEMI", TERMINAL); (yyvsp[-1].node_el)->sibling = semi;
	}
#line 1655 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 203 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL);pretty_print_error(semicolon_error_return); }
#line 1661 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 204 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error(semicolon_error_return); }
#line 1667 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 207 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("ID", VALUE); (yyval.node_el)->child->info = (yyvsp[-2].node_con);
		node* openparen = as_tree_n("EQ", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[0].node_el);
	}
#line 1678 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 213 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el);}
#line 1684 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 214 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = as_tree_n("ID", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1690 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 215 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[-3].node_con);
		node* openparen = as_tree_n("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-1].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1702 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 222 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("OPENPAREN", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1713 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 228 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling= as_tree_n("ARITH", VALUE); (yyvsp[-2].node_el)->sibling->info = (yyvsp[-1].node_con); (yyvsp[-2].node_el)->sibling->sibling = (yyvsp[0].node_el);}
#line 1719 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 229 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("OPENNEGATE", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1730 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 235 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = (yyvsp[-2].node_el);
		node* reln = as_tree_n("RELN", VALUE); reln->info = (yyvsp[-1].node_con);(yyvsp[-2].node_el)->sibling = reln;
		reln->sibling = (yyvsp[0].node_el);
	}
#line 1741 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 241 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = (yyvsp[-2].node_el);
		node* reln = as_tree_n("LOGICAL", VALUE);reln->info=(yyvsp[-1].node_con); (yyvsp[-2].node_el)->sibling = reln;
		reln->sibling = (yyvsp[0].node_el);
	}
#line 1752 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 247 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = as_tree_n("LOGICALNOT", VALUE); (yyval.node_el)->child->info = "!";
		(yyval.node_el)->child->sibling = (yyvsp[0].node_el);
	}
#line 1762 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 252 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL);pretty_print_error("Missing identifier name"); }
#line 1768 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 253 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL);pretty_print_error("Possible missing equalty sign"); }
#line 1774 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 254 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL);pretty_print_error("Possible missing closing parenthesis"); }
#line 1780 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 257 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("id_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[-2].node_con); node *comma = as_tree_n("COMMA", TERMINAL); (yyval.node_el)->child->sibling = comma; comma->sibling = (yyvsp[0].node_el); }
#line 1786 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 258 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("id_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1792 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 259 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("id_list", NONTERMINAL); (yyval.node_el)->child = as_tree_n("EPSILON", TERMINAL); }
#line 1798 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 260 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = as_tree_n("error", TERMINAL); pretty_print_error("Missing identifier name"); }
#line 1804 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 263 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("supported_constant", NONTERMINAL); (yyval.node_el)->child = as_tree_n("INTCONST", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1810 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 264 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = as_tree_n("supported_constant", NONTERMINAL); (yyval.node_el)->child = as_tree_n("BOOLCONST", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1816 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 265 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = as_tree_n("supported_constant", NONTERMINAL); (yyval.node_el)->child = as_tree_n("OPENNEGATE", TERMINAL);
		node* intconst = as_tree_n("INTCONST", VALUE); (yyval.node_el)->child->sibling = intconst;intconst->info = (yyvsp[-1].node_con);
		node* closeparen = as_tree_n("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}
#line 1826 "mad_parser.tab.c" /* yacc.c:1646  */
    break;


#line 1830 "mad_parser.tab.c" /* yacc.c:1646  */
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
#line 271 "mad_parser.y" /* yacc.c:1906  */

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
