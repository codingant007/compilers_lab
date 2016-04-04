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


#line 102 "mad_parser.tab.c" /* yacc.c:339  */

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
    OPENNEGATE = 265,
    VOID = 266,
    DTYPE_INT = 267,
    DTYPE_BOOL = 268,
    EQ = 269,
    ARITH = 270,
    RELN = 271,
    LOGICAL = 272,
    LOGICALNOT = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    FOR = 277,
    RETURN = 278,
    PRINT = 279,
    READ = 280,
    BOOLCONST = 281,
    INTCONST = 282,
    TERMINAL = 1,
    VALUE = 2
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 37 "mad_parser.y" /* yacc.c:355  */

	int dtype_int;
	bool dtype_bool;
	int opertype_int;
	node* node_el;
	char* node_con;

#line 181 "mad_parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAD_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "mad_parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,    28,    29,     2,     2,     2,     2,     2,     2,     2,
      30,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    84,    84,    85,    86,    89,    90,    93,    94,    97,
      98,    99,   102,   103,   104,   107,   108,   119,   125,   126,
     127,   128,   131,   132,   135,   136,   139,   140,   143,   144,
     145,   146,   147,   148,   149,   150,   153,   164,   165,   172,
     181,   193,   194,   195,   198,   203,   209,   210,   213,   221,
     222,   223,   226,   232,   233,   234,   241,   247,   248,   254,
     260,   266,   271,   277,   278,   279,   280,   281,   284,   285,
     286,   287,   290,   291,   292
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "NONTERMINAL", "error", "$undefined", "ID", "COMMA", "SEMI",
  "OPENPAREN", "CLOSEPAREN", "OPENCURLY", "CLOSECURLY", "OPENNEGATE",
  "VOID", "DTYPE_INT", "DTYPE_BOOL", "EQ", "ARITH", "RELN", "LOGICAL",
  "LOGICALNOT", "IF", "ELSE", "WHILE", "FOR", "RETURN", "PRINT", "READ",
  "BOOLCONST", "INTCONST", "TERMINAL", "VALUE", "'\\n'", "$accept",
  "mad_program", "supported_declarations", "variable_declarations",
  "variable_definitions", "dtype", "function_declarations",
  "argument_list", "statement_block", "variable_list", "statement_list",
  "supported_statement", "if_statement", "else_statement",
  "while_statement", "for_statement", "return_statement",
  "print_statement", "alr_subexpression", "id_list", "supported_constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,     1,     2,
      10
};
# endif

#define YYPACT_NINF -47

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-47)))

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   -14,    22,   -47,   -47,    36,    52,   -47,   242,    31,
     -47,   -47,    49,   -47,   -47,    56,    77,   -47,    84,   142,
      62,   -47,   142,   -47,     4,    91,   -47,   118,   130,   241,
     128,   128,   142,   142,   142,    48,   -47,   -47,   -47,   -47,
     -47,    48,   137,    78,   -47,   -47,   131,     5,   138,   165,
     138,   141,   147,   161,   132,   106,   108,   -47,   -47,   -47,
      34,    78,   -47,   -47,   -47,   -47,   -47,    12,   -47,   138,
     138,    82,   138,   188,   144,   199,   183,   138,   138,   138,
     131,   -47,   169,   138,   138,   171,    38,   -47,   -47,   -47,
     -47,   -47,   138,   138,   138,   183,   183,   168,   178,    61,
     183,   -47,   -47,   -47,   206,   210,   172,   -47,   -47,   213,
     145,   -47,   -47,   -47,   183,   183,   183,    82,    82,   -47,
     -47,   128,   -47,   138,   138,   189,   196,    13,   -47,   -47,
     156,   164,   192,   -47,   -47,   -47,   -47,   105,   -47,   138,
     138,   138,   -47,   217,   224,   195,   128,   128,   128,   128,
     -47,   -47,   -47,   -47
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    14,     0,    12,    13,     0,     0,     5,     0,     0,
       6,     4,     0,     1,     3,     8,     0,     7,     9,     0,
       0,    10,     0,    14,     0,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    15,    21,    20,
      17,     0,     0,     0,    25,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    72,    34,
       0,     0,    29,    30,    31,    32,    33,     0,    53,     0,
       0,     0,     0,     0,    72,     0,    61,     0,     0,     0,
      46,    44,     0,     0,     0,     0,     0,    23,    22,    27,
      35,    28,     0,     0,     0,    63,    64,     0,    69,     0,
      52,    56,    74,    58,     0,     0,     0,    47,    45,     0,
       0,    67,    66,    62,    57,    59,    60,     0,     0,    65,
      55,     0,    39,     0,     0,     0,     0,     0,    71,    68,
      37,     0,     0,    49,    50,    51,    48,     0,    36,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
      41,    42,    43,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -47,   229,   -47,    41,   -47,     9,   -47,    88,   -30,   197,
     175,   100,   -47,   -47,   -47,   -47,   -47,   -47,   -46,   101,
     -47
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    24,    10,    25,    59,    43,
      60,    61,    62,   138,    63,    64,    65,    66,    67,    99,
      68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    37,    73,    75,    76,    28,    70,    29,    82,     9,
     -54,    71,   -54,    90,   135,     9,    11,    91,   136,    72,
     -54,   -54,   -54,    95,    96,    12,   100,    92,    93,    94,
       1,   104,   105,   106,    18,    87,    13,   109,   110,   112,
       2,     3,     4,    88,    42,   113,   114,   115,   116,    23,
      42,   -24,    -2,     1,   -24,    19,   -24,   -24,   -24,    20,
       3,     4,   119,     2,     3,     4,   -24,   -24,   120,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,    41,   131,   132,    46,
      21,    47,    41,    97,    48,    98,    35,   -26,    49,   -70,
      22,   130,    26,   143,   144,   145,    50,    51,    30,    52,
      53,    54,    55,    56,    57,    58,    46,    83,    47,    85,
      27,    48,    84,    35,    86,    49,   150,   151,   152,   153,
      38,    39,    40,    50,    51,    31,    52,    53,    54,    55,
      56,    57,    58,    80,    32,    47,    35,    81,    48,    46,
      45,    47,    49,    23,    48,    69,   126,    77,    49,   -19,
      50,   102,   127,    78,     3,     4,    50,    56,    57,    58,
      92,    93,    94,    56,    57,    58,    46,    79,    47,   139,
     107,    48,   117,   123,   108,    49,   137,   124,   111,    92,
      93,    94,   118,    50,    92,    93,    94,    92,    93,    94,
      56,    57,    74,   140,   133,   101,   148,   141,    92,    93,
      94,   134,   149,    92,    93,    94,   103,    92,    93,    94,
      92,    93,    94,   121,    92,    93,    94,   122,   128,   129,
     125,    92,    93,    94,   146,    92,    93,    94,    92,    93,
      94,   147,    92,    93,    94,    14,    89,   142,    44,    92,
      93,    94,    33,    15,     0,    34,    16,    17,   -18
};

static const yytype_int16 yycheck[] =
{
      30,    31,    48,    49,    50,     1,     1,     3,    54,     0,
       5,     6,     7,     1,     1,     6,    30,     5,     5,    14,
      15,    16,    17,    69,    70,     3,    72,    15,    16,    17,
       1,    77,    78,    79,     3,     1,     0,    83,    84,     1,
      11,    12,    13,     9,    35,     7,    92,    93,    94,     1,
      41,     3,     0,     1,     6,     6,     8,     9,    10,     3,
      12,    13,     1,    11,    12,    13,    18,    19,     7,    21,
      22,    23,    24,    25,    26,    27,    35,   123,   124,     1,
       3,     3,    41,     1,     6,     3,     8,     9,    10,     7,
       6,   121,    30,   139,   140,   141,    18,    19,     7,    21,
      22,    23,    24,    25,    26,    27,     1,     1,     3,     1,
      22,     6,     6,     8,     6,    10,   146,   147,   148,   149,
      32,    33,    34,    18,    19,     7,    21,    22,    23,    24,
      25,    26,    27,     1,     4,     3,     8,     5,     6,     1,
       3,     3,    10,     1,     6,    14,     1,     6,    10,     7,
      18,     7,     7,     6,    12,    13,    18,    25,    26,    27,
      15,    16,    17,    25,    26,    27,     1,     6,     3,     5,
       1,     6,     4,     1,     5,    10,    20,     5,     7,    15,
      16,    17,     4,    18,    15,    16,    17,    15,    16,    17,
      25,    26,    27,     1,     5,     7,     1,     5,    15,    16,
      17,     5,     7,    15,    16,    17,     7,    15,    16,    17,
      15,    16,    17,     7,    15,    16,    17,     7,   117,   118,
       7,    15,    16,    17,     7,    15,    16,    17,    15,    16,
      17,     7,    15,    16,    17,     6,    61,   137,    41,    15,
      16,    17,     1,     1,    -1,     4,     4,     5,     7
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    11,    12,    13,    32,    33,    34,    35,    36,
      37,    30,     3,     0,    32,     1,     4,     5,     3,     6,
       3,     3,     6,     1,    36,    38,    30,    38,     1,     3,
       7,     7,     4,     1,     4,     8,    39,    39,    38,    38,
      38,    34,    36,    40,    40,     3,     1,     3,     6,    10,
      18,    19,    21,    22,    23,    24,    25,    26,    27,    39,
      41,    42,    43,    45,    46,    47,    48,    49,    51,    14,
       1,     6,    14,    49,    27,    49,    49,     6,     6,     6,
       1,     5,    49,     1,     6,     1,     6,     1,     9,    41,
       1,     5,    15,    16,    17,    49,    49,     1,     3,    50,
      49,     7,     7,     7,    49,    49,    49,     1,     5,    49,
      49,     7,     1,     7,    49,    49,    49,     4,     4,     1,
       7,     7,     7,     1,     5,     7,     1,     7,    50,    50,
      39,    49,    49,     5,     5,     1,     5,    20,    44,     5,
       1,     5,    42,    49,    49,    49,     7,     7,     1,     7,
      39,    39,    39,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    32,    32,    33,    33,    34,    34,    35,
      35,    35,    36,    36,    36,    37,    37,    38,    38,    38,
      38,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    42,    42,    42,    42,    43,    44,    44,    45,
      46,    46,    46,    46,    47,    47,    47,    47,    48,    48,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    50,    50,
      50,    50,    51,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     2,     2,     2,
       3,     4,     1,     1,     1,     6,     6,     4,     2,     0,
       4,     4,     4,     4,     0,     2,     0,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     6,     0,     2,     4,
       9,     9,     9,     9,     2,     3,     2,     3,     5,     5,
       5,     5,     3,     1,     1,     4,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     4,     3,     3,     3,     1,
       0,     3,     1,     1,     3
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
#line 84 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1394 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 85 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("mad_program", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); root = (yyval.node_el);}
#line 1400 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 86 "mad_parser.y" /* yacc.c:1646  */
    { yyerror("Compilation terminating with errors"); root = NULL;}
#line 1406 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1412 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 90 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("supported_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el);}
#line 1418 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("variable_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = new node("SEMI", TERMINAL);}
#line 1424 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 94 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Possible missing semicolon in variable declaration list"); }
#line 1430 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 97 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = new node("ID", VALUE); (yyvsp[-1].node_el)->sibling->info = (yyvsp[0].node_con);}
#line 1436 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 98 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("variable_definitions", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = new node("COMMA", TERMINAL); (yyvsp[-2].node_el)->sibling->sibling = new node("ID", VALUE); (yyvsp[-2].node_el)->sibling->sibling->info = (yyvsp[0].node_con); }
#line 1442 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 99 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Missing comma in definitions list"); }
#line 1448 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 102 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("DTYPE_INT", TERMINAL); /*$$->child = $1;*/}
#line 1454 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 103 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("DTYPE_BOOL", TERMINAL); /*$$->child = $1;*/}
#line 1460 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 104 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("error", TERMINAL); yyerror("Unknown type declaration"); }
#line 1466 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 107 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("function_declarations", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-5].node_el); node* id = new node("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyvsp[-5].node_el)->sibling = id; node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen; openparen->sibling = (yyvsp[-2].node_el); node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen; closeparen->sibling = (yyvsp[0].node_el); }
#line 1472 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 108 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("function_declarations", NONTERMINAL);
		(yyval.node_el)->child = new node("VOID", TERMINAL);
		node* id = new node("ID", VALUE); id->info = (yyvsp[-4].node_con); (yyval.node_el)->child->sibling = id;
		node* openparen = new node("OPENPAREN", TERMINAL); id->sibling = openparen;
		openparen->sibling = (yyvsp[-2].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[0].node_el);
	}
#line 1486 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 119 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("argument_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-3].node_el);
		node* id = new node("ID", VALUE); id->info = (yyvsp[-2].node_con); (yyvsp[-3].node_el)->sibling = id;
		node* comma= new node("COMMA", TERMINAL); id->sibling = comma;
		comma->sibling = (yyvsp[0].node_el);
	}
#line 1497 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 125 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("argument_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); node* id = new node("ID", VALUE); id->info = (yyvsp[0].node_con); (yyvsp[-1].node_el)->sibling = id;}
#line 1503 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("function_declarations", NONTERMINAL); (yyval.node_el)->child = new node("EPSILON", TERMINAL); }
#line 1509 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 127 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Missing comma in argument list"); }
#line 1515 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 128 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Missing identifier in argument list"); }
#line 1521 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 131 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("statement_block", NONTERMINAL); (yyval.node_el)->child = new node("OPENCURLY", TERMINAL); (yyval.node_el)->child->sibling = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = new node("CLOSECURLY", TERMINAL); }
#line 1527 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 132 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Possible missing semicolon in statement block"); }
#line 1533 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 135 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("variable_list", NONTERMINAL); (yyval.node_el)->child = new node("EPSILON", TERMINAL); }
#line 1539 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 136 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("variable_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el); }
#line 1545 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 139 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("statement_list", NONTERMINAL); (yyval.node_el)->child = new node("EPSILON", TERMINAL); }
#line 1551 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 140 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("statement_list", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el);}
#line 1557 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 143 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-1].node_el); (yyvsp[-1].node_el)->sibling = new node("SEMI", TERMINAL);}
#line 1563 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 144 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1569 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1575 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1581 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 147 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1587 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 148 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1593 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 149 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("supported_statement", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el); }
#line 1599 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 150 "mad_parser.y" /* yacc.c:1646  */
    { yyerror("Possible missing semicolon with alr_subexpression"); (yyval.node_el) = new node("error", TERMINAL); }
#line 1605 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 153 "mad_parser.y" /* yacc.c:1646  */
    { //CHANGED IF EXPRESSION INTERNAL TO STATEMENT BLOCK
		(yyval.node_el) = new node("if_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("IF", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-3].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-3].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[-1].node_el);
		(yyvsp[-1].node_el)->sibling = (yyvsp[0].node_el);
	}
#line 1619 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 164 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("else_statement", NONTERMINAL); (yyval.node_el)->child = new node("EPSILON", TERMINAL); }
#line 1625 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 165 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("else_statement", NONTERMINAL); 
		(yyval.node_el)->child = new node("ELSE", TERMINAL); 
		(yyval.node_el)->child->sibling = (yyvsp[0].node_el);
	}
#line 1635 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 172 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("while_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("WHILE", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-1].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1647 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 181 "mad_parser.y" /* yacc.c:1646  */
    { //CHANGED FOR EXPRESSION INTERNAL TO STATEMENT BLOCK
		(yyval.node_el) = new node("for_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("FOR", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-6].node_el);
		(yyvsp[-6].node_el)->sibling = new node("SEMI", TERMINAL);
		(yyvsp[-6].node_el)->sibling->sibling = (yyvsp[-4].node_el);
		(yyvsp[-4].node_el)->sibling = new node("SEMI", TERMINAL);
		(yyvsp[-4].node_el)->sibling->sibling = (yyvsp[-2].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen;
		closeparen->sibling = (yyvsp[0].node_el);		
	}
#line 1664 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 193 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing semicolon in for"); }
#line 1670 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing semicolon in for"); }
#line 1676 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 195 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Possible missing closing parenthesis in for"); }
#line 1682 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 198 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("return_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("RETURN", TERMINAL);
		node* semi = new node("SEMI", TERMINAL); (yyval.node_el)->child->sibling = semi;
	}
#line 1692 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 203 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("return_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("RETURN", TERMINAL);		
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* semi = new node("SEMI", TERMINAL); (yyvsp[-1].node_el)->sibling = semi;
	}
#line 1703 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Missing semicolon with return"); }
#line 1709 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("error", TERMINAL); yyerror("Missing semicolon with return"); }
#line 1715 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 213 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("print_statement", NONTERMINAL);
		(yyval.node_el)->child = new node("PRINT", TERMINAL);
		node* openparen = new node("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-2].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-2].node_el)->sibling = closeparen;
		closeparen->sibling = new node("SEMI", TERMINAL);;
	}
#line 1728 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possile missing open parenthesis"); }
#line 1734 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 222 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
#line 1740 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 223 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Missing semicolon with print"); }
#line 1746 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 226 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = new node("ID", VALUE); (yyval.node_el)->child->info = (yyvsp[-2].node_con);
		node* openparen = new node("EQ", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[0].node_el);
	}
#line 1757 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 232 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = (yyvsp[0].node_el);}
#line 1763 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 233 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = new node("ID", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1769 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 234 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = new node("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[-3].node_con);
		node* openparen = new node("OPENPAREN", TERMINAL); (yyval.node_el)->child->sibling = openparen;
		openparen->sibling = (yyvsp[-1].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1781 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 241 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = new node("OPENPAREN", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1792 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 247 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("alr_subexpression", NONTERMINAL); (yyval.node_el)->child = (yyvsp[-2].node_el); (yyvsp[-2].node_el)->sibling= new node("ARITH", VALUE); (yyvsp[-2].node_el)->sibling->info = (yyvsp[-1].node_con); (yyvsp[-2].node_el)->sibling->sibling = (yyvsp[0].node_el);}
#line 1798 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 248 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = new node("OPENNEGATE", TERMINAL);
		(yyval.node_el)->child->sibling = (yyvsp[-1].node_el);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); (yyvsp[-1].node_el)->sibling = closeparen;
	}
#line 1809 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 254 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = (yyvsp[-2].node_el);
		node* reln = new node("RELN", VALUE); reln->info = (yyvsp[-1].node_con);(yyvsp[-2].node_el)->sibling = reln;
		reln->sibling = (yyvsp[0].node_el);
	}
#line 1820 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 260 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = (yyvsp[-2].node_el);
		node* reln = new node("LOGICAL", VALUE);reln->info=(yyvsp[-1].node_con); (yyvsp[-2].node_el)->sibling = reln;
		reln->sibling = (yyvsp[0].node_el);
	}
#line 1831 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 266 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL);
		(yyval.node_el)->child = new node("LOGICALNOT", VALUE); (yyval.node_el)->child->info = "!";
		(yyval.node_el)->child->sibling = (yyvsp[0].node_el);
	}
#line 1841 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 271 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("alr_subexpression", NONTERMINAL); 
		(yyval.node_el)->child = new node("READ", TERMINAL);
		node* intconst = new node("OPENPAREN", VALUE); (yyval.node_el)->child->sibling = intconst;
		node* closeparen = new node("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}
#line 1852 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 277 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Missing identifier name"); }
#line 1858 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 278 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing equalty sign"); }
#line 1864 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 279 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
#line 1870 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 280 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing closing parenthesis"); }
#line 1876 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 281 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL);yyerror("Possible missing opening parenthesis"); }
#line 1882 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 284 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("id_list", NONTERMINAL); (yyval.node_el)->child = new node("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[-2].node_con); node *comma = new node("COMMA", TERMINAL); (yyval.node_el)->child->sibling = comma; comma->sibling = (yyvsp[0].node_el); }
#line 1888 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 285 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("id_list", NONTERMINAL); (yyval.node_el)->child = new node("ID", VALUE);(yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1894 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 286 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("id_list", NONTERMINAL); (yyval.node_el)->child = new node("EPSILON", TERMINAL); }
#line 1900 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 287 "mad_parser.y" /* yacc.c:1646  */
    { (yyval.node_el) = new node("error", TERMINAL); yyerror("Missing identifier name"); }
#line 1906 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 290 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("supported_constant", NONTERMINAL); (yyval.node_el)->child = new node("INTCONST", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1912 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 291 "mad_parser.y" /* yacc.c:1646  */
    {(yyval.node_el) = new node("supported_constant", NONTERMINAL); (yyval.node_el)->child = new node("BOOLCONST", VALUE); (yyval.node_el)->child->info = (yyvsp[0].node_con);}
#line 1918 "mad_parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 292 "mad_parser.y" /* yacc.c:1646  */
    {
		(yyval.node_el) = new node("supported_constant", NONTERMINAL); (yyval.node_el)->child = new node("OPENNEGATE", TERMINAL);
		node* intconst = new node("INTCONST", VALUE); (yyval.node_el)->child->sibling = intconst;intconst->info = (yyvsp[-1].node_con);
		node* closeparen = new node("CLOSEPAREN", TERMINAL); intconst->sibling = closeparen;
	}
#line 1928 "mad_parser.tab.c" /* yacc.c:1646  */
    break;


#line 1932 "mad_parser.tab.c" /* yacc.c:1646  */
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
#line 298 "mad_parser.y" /* yacc.c:1906  */

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
