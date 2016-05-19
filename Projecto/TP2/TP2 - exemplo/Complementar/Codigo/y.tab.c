/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     VAR = 259,
     OPINCDEC = 260,
     OPASS = 261,
     OPLOG = 262,
     OPREL = 263,
     OPRELEQ = 264,
     OPADD = 265,
     OPMUL = 266,
     STRING = 267,
     VARS = 268,
     START = 269,
     END = 270,
     SCAN = 271,
     PRINT = 272,
     IF = 273,
     ELSE = 274,
     WHILE = 275,
     NOT = 276,
     ERRO = 277
   };
#endif
/* Tokens.  */
#define INT 258
#define VAR 259
#define OPINCDEC 260
#define OPASS 261
#define OPLOG 262
#define OPREL 263
#define OPRELEQ 264
#define OPADD 265
#define OPMUL 266
#define STRING 267
#define VARS 268
#define START 269
#define END 270
#define SCAN 271
#define PRINT 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define NOT 276
#define ERRO 277




/* Copy the first part of user declarations.  */
#line 2 "virtual.y"

	#include "estrutura.c"

	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;	
	extern char *yytext;
	extern void yyerror(char *s); 

	int gp = 0;
	int iAddr = 0;
	int whileAddr = 0;
	int erros = 0;
	char *filename;

	struct variavel *listaVariaveis = NULL, *auxVariavel = NULL;
	struct instrucao *listaInstrucoes = NULL;
	struct ifAddr *pilhaIfAddr = NULL;
	struct whileAddr *pilhaWhileAddr = NULL;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 24 "virtual.y"
{ 
	int inteiro; 
	char op;
	char *var; 
	char *string; 
}
/* Line 193 of yacc.c.  */
#line 168 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 181 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNRULES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    15,    18,    24,
      25,    29,    32,    34,    36,    38,    40,    42,    44,    46,
      51,    52,    61,    65,    66,    74,    75,    81,    85,    86,
      94,    98,   102,   103,   104,   115,   116,   122,   123,   124,
     125,   126,   137,   140,   144,   148,   152,   156,   160,   162,
     163,   169,   171,   174
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    36,    -1,    -1,    13,    34,    -1,
      34,    35,    -1,    35,    -1,     4,    23,    -1,     4,    24,
       3,    25,    23,    -1,    -1,    14,    37,    15,    -1,    37,
      38,    -1,    38,    -1,    39,    -1,    45,    -1,    43,    -1,
      46,    -1,    51,    -1,    23,    -1,     4,    26,    55,    23,
      -1,    -1,     4,    40,    24,    55,    25,    26,    55,    23,
      -1,     4,     5,    23,    -1,    -1,     4,    41,    24,    55,
      25,     5,    23,    -1,    -1,     4,    42,     6,    55,    23,
      -1,    16,     4,    23,    -1,    -1,    16,     4,    44,    24,
      55,    25,    23,    -1,    17,    55,    23,    -1,    17,    12,
      23,    -1,    -1,    -1,    18,    27,    55,    28,    47,    29,
      37,    30,    48,    49,    -1,    -1,    19,    50,    29,    37,
      30,    -1,    -1,    -1,    -1,    -1,    20,    27,    52,    55,
      28,    53,    29,    37,    54,    30,    -1,    21,    55,    -1,
      55,     8,    55,    -1,    55,     9,    55,    -1,    55,     7,
      55,    -1,    55,    10,    55,    -1,    55,    11,    55,    -1,
       4,    -1,    -1,     4,    56,    24,    55,    25,    -1,     3,
      -1,    10,    55,    -1,    27,    55,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    46,    46,    50,    51,    54,    55,    58,    78,   103,
     104,   107,   108,   111,   112,   113,   114,   115,   116,   120,
     144,   143,   169,   204,   203,   242,   241,   287,   314,   313,
     346,   351,   363,   368,   362,   376,   375,   385,   391,   395,
     400,   390,   412,   417,   425,   440,   448,   456,   466,   492,
     491,   520,   527,   538
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VAR", "OPINCDEC", "OPASS",
  "OPLOG", "OPREL", "OPRELEQ", "OPADD", "OPMUL", "STRING", "VARS", "START",
  "END", "SCAN", "PRINT", "IF", "ELSE", "WHILE", "NOT", "ERRO", "';'",
  "'['", "']'", "'='", "'('", "')'", "'{'", "'}'", "$accept", "Fonte",
  "Cabeca", "Declaracoes", "Declaracao", "Corpo", "Instrucoes",
  "Instrucao", "Atribuicao", "@1", "@2", "@3", "Leitura", "@4", "Escrita",
  "Condicional", "@5", "@6", "Else", "@7", "Ciclo", "@8", "@9", "@10",
  "Exp", "@11", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    59,    91,    93,    61,    40,    41,   123,
     125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    37,    38,    38,    38,    38,    38,    38,    39,
      40,    39,    39,    41,    39,    42,    39,    43,    44,    43,
      45,    45,    47,    48,    46,    50,    49,    49,    52,    53,
      54,    51,    55,    55,    55,    55,    55,    55,    55,    56,
      55,    55,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     1,     2,     5,     0,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       0,     8,     3,     0,     7,     0,     5,     3,     0,     7,
       3,     3,     0,     0,    10,     0,     5,     0,     0,     0,
       0,    10,     2,     3,     3,     3,     3,     3,     1,     0,
       5,     1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     9,     0,     4,     6,     1,     0,     2,
       7,     0,     5,    20,     0,     0,     0,     0,    18,     0,
      12,    13,    15,    14,    16,    17,     0,     0,     0,     0,
       0,     0,    28,    51,    48,     0,     0,     0,     0,     0,
       0,    38,    10,    11,     0,    22,     0,     0,     0,     0,
      27,     0,     0,    52,    31,    42,     0,     0,     0,     0,
       0,     0,    30,     0,     0,     8,    19,     0,     0,     0,
       0,     0,    53,    45,    43,    44,    46,    47,    32,     0,
       0,     0,    26,     0,     0,     0,    39,     0,     0,     0,
      50,     0,     0,     0,    24,    29,     0,     0,    21,    33,
      40,    37,     0,    35,    34,    41,     0,     0,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     5,     6,     9,    19,    20,    21,    29,
      30,    31,    22,    51,    23,    24,    85,   101,   104,   106,
      25,    64,    92,   102,    39,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int16 yypact[] =
{
     -11,     3,     9,    11,     4,     3,   -28,   -28,    96,   -28,
     -28,    38,   -28,    -2,    42,     2,    23,    26,   -28,    81,
     -28,   -28,   -28,   -28,   -28,   -28,    34,    51,    52,    54,
      58,    69,    53,   -28,    59,    52,    57,    52,    52,   127,
      52,   -28,   -28,   -28,    64,   -28,   144,    52,    52,    52,
     -28,    71,    78,    92,   -28,    47,     8,    52,    52,    52,
      52,    52,   -28,    56,    52,   -28,   -28,    61,    98,   149,
      52,    52,   -28,   135,    47,    47,    92,   -28,   -28,    83,
      62,   105,   -28,   117,   122,    86,   -28,    52,    94,    95,
     -28,    96,    91,   154,   -28,   -28,    22,    96,   -28,   -28,
      96,   102,   109,   -28,   -28,   -28,    93,    96,    31,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   -28,   136,   -28,    77,   -19,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -27,   -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -50
static const yytype_int8 yytable[] =
{
      43,    46,     1,    27,   -25,    33,    34,     4,    53,     7,
      55,    56,    35,    63,    36,    57,    58,    59,    60,    61,
      67,    68,    69,    37,    28,     8,    13,    10,    11,    38,
      73,    74,    75,    76,    77,    13,    72,    79,    14,    15,
      16,    26,    17,    83,    84,    18,    32,    14,    15,    16,
      40,    17,    99,    41,    18,    33,    34,    60,    61,    44,
      93,   109,    35,    57,    58,    59,    60,    61,    57,    58,
      59,    60,    61,    37,    45,    49,    50,    43,    47,    38,
      54,    43,    48,   -49,    78,    13,    80,    65,    87,    43,
      57,    58,    59,    60,    61,    70,    42,    14,    15,    16,
      13,    17,    71,    61,    18,    57,    58,    59,    60,    61,
      88,    86,    14,    15,    16,    91,    17,    94,    95,    18,
      97,   103,   107,    81,    57,    58,    59,    60,    61,    57,
      58,    59,    60,    61,    57,    58,    59,    60,    61,   105,
       0,    12,    89,    58,    59,    60,    61,    90,     0,     0,
      62,    57,    58,    59,    60,    61,    57,    58,    59,    60,
      61,    57,    58,    59,    60,    61,     0,    66,    96,     0,
       0,     0,    82,     0,   100,     0,     0,    98,     0,     0,
       0,     0,     0,     0,   108
};

static const yytype_int8 yycheck[] =
{
      19,    28,    13,     5,     6,     3,     4,     4,    35,     0,
      37,    38,    10,    40,    12,     7,     8,     9,    10,    11,
      47,    48,    49,    21,    26,    14,     4,    23,    24,    27,
      57,    58,    59,    60,    61,     4,    28,    64,    16,    17,
      18,     3,    20,    70,    71,    23,     4,    16,    17,    18,
      27,    20,    30,    27,    23,     3,     4,    10,    11,    25,
      87,    30,    10,     7,     8,     9,    10,    11,     7,     8,
       9,    10,    11,    21,    23,     6,    23,    96,    24,    27,
      23,   100,    24,    24,    28,     4,    25,    23,    26,   108,
       7,     8,     9,    10,    11,    24,    15,    16,    17,    18,
       4,    20,    24,    11,    23,     7,     8,     9,    10,    11,
       5,    28,    16,    17,    18,    29,    20,    23,    23,    23,
      29,    19,    29,    25,     7,     8,     9,    10,    11,     7,
       8,     9,    10,    11,     7,     8,     9,    10,    11,    30,
      -1,     5,    25,     8,     9,    10,    11,    25,    -1,    -1,
      23,     7,     8,     9,    10,    11,     7,     8,     9,    10,
      11,     7,     8,     9,    10,    11,    -1,    23,    91,    -1,
      -1,    -1,    23,    -1,    97,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    32,    33,     4,    34,    35,     0,    14,    36,
      23,    24,    35,     4,    16,    17,    18,    20,    23,    37,
      38,    39,    43,    45,    46,    51,     3,     5,    26,    40,
      41,    42,     4,     3,     4,    10,    12,    21,    27,    55,
      27,    27,    15,    38,    25,    23,    55,    24,    24,     6,
      23,    44,    56,    55,    23,    55,    55,     7,     8,     9,
      10,    11,    23,    55,    52,    23,    23,    55,    55,    55,
      24,    24,    28,    55,    55,    55,    55,    55,    28,    55,
      25,    25,    23,    55,    55,    47,    28,    26,     5,    25,
      25,    29,    53,    55,    23,    23,    37,    29,    23,    30,
      37,    48,    54,    19,    49,    30,    50,    29,    37,    30
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 51 "virtual.y"
    { listaInstrucoes = insertInstrucao(iAddr++,"START",listaInstrucoes); }
    break;

  case 7:
#line 59 "virtual.y"
    { 
					auxVariavel = malloc(sizeof(struct variavel));
		   			auxVariavel->nome = strdup((yyvsp[(1) - (2)].var));						
		   			auxVariavel->tipo = strdup("inteiro");
		   			auxVariavel->endereco = gp;
		   			auxVariavel->inicializado = 0;

					if(!existeVariavel(auxVariavel->nome,listaVariaveis))
					{
						listaVariaveis = insertVariavel(auxVariavel,listaVariaveis);
						listaInstrucoes = insertInstrucao(iAddr++,"PUSHI 0",listaInstrucoes);
						gp++;
					}
					else 
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' já declarada\n",yylineno,(yyvsp[(1) - (2)].var));
					}
				}
    break;

  case 8:
#line 79 "virtual.y"
    {
		   			auxVariavel = malloc(sizeof(struct variavel));
		   			auxVariavel->nome = strdup((yyvsp[(1) - (5)].var));	
		   			auxVariavel->tipo = strdup("array");
		   			auxVariavel->endereco = gp;
		   			auxVariavel->inicializado = 0;			
		   			
					if(!existeVariavel(auxVariavel->nome,listaVariaveis))
					{
						listaVariaveis = insertVariavel(auxVariavel,listaVariaveis); 
						char buf[20];
						sprintf(buf,"PUSHN %d",(yyvsp[(3) - (5)].inteiro)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
						gp += (yyvsp[(3) - (5)].inteiro);
					}
					else 
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' já declarada\n",yylineno,(yyvsp[(1) - (5)].var));
					}
		   		}
    break;

  case 10:
#line 104 "virtual.y"
    { listaInstrucoes = insertInstrucao(iAddr++,"STOP",listaInstrucoes); }
    break;

  case 18:
#line 116 "virtual.y"
    { listaInstrucoes = insertInstrucao(iAddr++,"NOP",listaInstrucoes);	 }
    break;

  case 19:
#line 121 "virtual.y"
    { 
					if(!existeVariavel((yyvsp[(1) - (4)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (4)].var));
					}
					else if(strcmp(tipoVariavel((yyvsp[(1) - (4)].var),listaVariaveis),"inteiro") != 0)
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não é um escalar\n",yylineno,(yyvsp[(1) - (4)].var));
					}
					else
					{
						inicializaVariavel((yyvsp[(1) - (4)].var),listaVariaveis);

						char buf[20];
						sprintf(buf,"STOREG %d",enderecoVariavel((yyvsp[(1) - (4)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
					}
					
				}
    break;

  case 20:
#line 144 "virtual.y"
    {
		   			if(!existeVariavel((yyvsp[(1) - (1)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else if(strcmp(tipoVariavel((yyvsp[(1) - (1)].var),listaVariaveis),"array") != 0)
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não é um vector\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else
					{
						inicializaVariavel((yyvsp[(1) - (1)].var),listaVariaveis);

	   					char buf[20];
						sprintf(buf,"PUSHI %d",enderecoVariavel((yyvsp[(1) - (1)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes); 
					}
				}
    break;

  case 21:
#line 165 "virtual.y"
    { 
					listaInstrucoes = insertInstrucao(iAddr++,"STOREN",listaInstrucoes);
		   		}
    break;

  case 22:
#line 170 "virtual.y"
    {
		   			if(!existeVariavel((yyvsp[(1) - (3)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (3)].var));
					}
					else if(strcmp(tipoVariavel((yyvsp[(1) - (3)].var),listaVariaveis),"inteiro") != 0)
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não é um escalar\n",yylineno,(yyvsp[(1) - (3)].var));
					}
					else if(!variavelInicializada((yyvsp[(1) - (3)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não está inicializada\n",yylineno,(yyvsp[(1) - (3)].var));
					}
					else
					{
			   			char buf[20];
						sprintf(buf,"PUSHG %d",enderecoVariavel((yyvsp[(1) - (3)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);  
						listaInstrucoes = insertInstrucao(iAddr++,"PUSHI 1",listaInstrucoes); 

						if((yyvsp[(2) - (3)].op) == '+')  
							listaInstrucoes = insertInstrucao(iAddr++,"ADD",listaInstrucoes); 
						else if((yyvsp[(2) - (3)].op) == '-')
						  	listaInstrucoes = insertInstrucao(iAddr++,"SUB",listaInstrucoes);

						sprintf(buf,"STOREG %d",enderecoVariavel((yyvsp[(1) - (3)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
					}
		   		}
    break;

  case 23:
#line 204 "virtual.y"
    {
		   			if(!existeVariavel((yyvsp[(1) - (1)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else if(strcmp(tipoVariavel((yyvsp[(1) - (1)].var),listaVariaveis),"array") != 0)
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não é um vector\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else if(!variavelInicializada((yyvsp[(1) - (1)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não está inicializada\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else
					{
	   					char buf[20];
						sprintf(buf,"PUSHI %d",enderecoVariavel((yyvsp[(1) - (1)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes); 
					}
				}
    break;

  case 24:
#line 228 "virtual.y"
    {
					listaInstrucoes = insertInstrucao(iAddr++,"DUP 2",listaInstrucoes); 
					listaInstrucoes = insertInstrucao(iAddr++,"LOADN",listaInstrucoes); 
					listaInstrucoes = insertInstrucao(iAddr++,"PUSHI 1",listaInstrucoes); 

					if((yyvsp[(6) - (7)].op) == '+')  
						listaInstrucoes = insertInstrucao(iAddr++,"ADD",listaInstrucoes); 
					else if((yyvsp[(6) - (7)].op) == '-')
					  	listaInstrucoes = insertInstrucao(iAddr++,"SUB",listaInstrucoes);

					listaInstrucoes = insertInstrucao(iAddr++,"STOREN",listaInstrucoes);	
		   		}
    break;

  case 25:
#line 242 "virtual.y"
    {
		   			if(!existeVariavel((yyvsp[(1) - (1)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else if(strcmp(tipoVariavel((yyvsp[(1) - (1)].var),listaVariaveis),"inteiro") != 0)
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não é um escalar\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else if(!variavelInicializada((yyvsp[(1) - (1)].var),listaVariaveis))
					{
						erros = 1;
						fprintf(stderr,"l.%d erro: variável '%s' não está inicializada\n",yylineno,(yyvsp[(1) - (1)].var));
					}
					else 
					{
						inicializaVariavel((yyvsp[(1) - (1)].var),listaVariaveis);

		   				char buf[20];
		   				sprintf(buf,"PUSHG %d",enderecoVariavel((yyvsp[(1) - (1)].var),listaVariaveis)); 
						listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
					}
				}
    break;

  case 26:
#line 268 "virtual.y"
    {
		   			if((yyvsp[(3) - (5)].op) == '+')  
		   				listaInstrucoes = insertInstrucao(iAddr++,"ADD",listaInstrucoes); 
		   			else if((yyvsp[(3) - (5)].op) == '-') 
		   				listaInstrucoes = insertInstrucao(iAddr++,"SUB",listaInstrucoes); 
		   			else if((yyvsp[(3) - (5)].op) == '*') 
		   				listaInstrucoes = insertInstrucao(iAddr++,"MUL",listaInstrucoes); 
		   			else if((yyvsp[(3) - (5)].op) == '/') 
		   				listaInstrucoes = insertInstrucao(iAddr++,"DIV",listaInstrucoes); 
		   			else if((yyvsp[(3) - (5)].op) == '%') 
		   				listaInstrucoes = insertInstrucao(iAddr++,"MOD",listaInstrucoes); 

		   			char buf[20];	
		   			sprintf(buf,"STOREG %d",enderecoVariavel((yyvsp[(1) - (5)].var),listaVariaveis)); 
					listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
		   		}
    break;

  case 27:
#line 288 "virtual.y"
    {
				if(!existeVariavel((yyvsp[(2) - (3)].var),listaVariaveis))
				{
					erros = 1;
					fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(2) - (3)].var));
				}
				else if(strcmp(tipoVariavel((yyvsp[(2) - (3)].var),listaVariaveis),"inteiro") != 0)
				{
					erros = 1;
					fprintf(stderr,"l.%d erro: variável '%s' não é um escalar\n",yylineno,(yyvsp[(2) - (3)].var));
				}
				else 
				{	
					inicializaVariavel((yyvsp[(2) - (3)].var),listaVariaveis);

					char buf[1024];
					sprintf(buf,"READ"); 
					listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);	
					listaInstrucoes = insertInstrucao(iAddr++,"ATOI",listaInstrucoes);	

					sprintf(buf,"STOREG %d",enderecoVariavel((yyvsp[(2) - (3)].var),listaVariaveis)); 
					listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);	
				}
			}
    break;

  case 28:
#line 314 "virtual.y"
    {
				if(!existeVariavel((yyvsp[(2) - (2)].var),listaVariaveis))
				{
					erros = 1;
					fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(2) - (2)].var));
				}
				else if(strcmp(tipoVariavel((yyvsp[(2) - (2)].var),listaVariaveis),"array") != 0)
				{
					erros = 1;
					fprintf(stderr,"l.%d erro: variável '%s' não é um vector\n",yylineno,(yyvsp[(2) - (2)].var));
				}
				else 
				{
					inicializaVariavel((yyvsp[(2) - (2)].var),listaVariaveis);

	   				char buf[1024];
					sprintf(buf,"PUSHI %d",enderecoVariavel((yyvsp[(2) - (2)].var),listaVariaveis)); 
					listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
				}  
			}
    break;

  case 29:
#line 335 "virtual.y"
    {
				char buf[20];
				sprintf(buf,"READ"); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);	
				listaInstrucoes = insertInstrucao(iAddr++,"ATOI",listaInstrucoes);	
				listaInstrucoes = insertInstrucao(iAddr++,"STOREN",listaInstrucoes);
			}
    break;

  case 30:
#line 347 "virtual.y"
    { 
				listaInstrucoes = insertInstrucao(iAddr++,"WRITEI",listaInstrucoes); 
			}
    break;

  case 31:
#line 352 "virtual.y"
    { 				
				char buf[1024];
				sprintf(buf,"PUSHS \"%s\"",(yyvsp[(2) - (3)].string)); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);			
				listaInstrucoes = insertInstrucao(iAddr++,"WRITES",listaInstrucoes);
			}
    break;

  case 32:
#line 363 "virtual.y"
    { 
					pilhaIfAddr = pushIfAddr(iAddr,pilhaIfAddr); 
					listaInstrucoes = insertInstrucao(iAddr++,"if",listaInstrucoes); 
				}
    break;

  case 33:
#line 368 "virtual.y"
    { 
					ifJump(iAddr+1,pilhaIfAddr,listaInstrucoes); 
					pilhaIfAddr = popIfAddr(pilhaIfAddr);
				}
    break;

  case 35:
#line 376 "virtual.y"
    {  
			pilhaIfAddr = pushIfAddr(iAddr,pilhaIfAddr); 
			listaInstrucoes = insertInstrucao(iAddr++,"else",listaInstrucoes); 
		}
    break;

  case 36:
#line 381 "virtual.y"
    {
			elseJump(iAddr,pilhaIfAddr,listaInstrucoes); 
			pilhaIfAddr = popIfAddr(pilhaIfAddr);
		}
    break;

  case 38:
#line 391 "virtual.y"
    { 
				whileAddr = iAddr; 
			}
    break;

  case 39:
#line 395 "virtual.y"
    { 
				pilhaWhileAddr = pushWhileAddr(iAddr,whileAddr,pilhaWhileAddr); 
				listaInstrucoes = insertInstrucao(iAddr++,"while",listaInstrucoes); 
			}
    break;

  case 40:
#line 400 "virtual.y"
    { 
				int jump = whileJump(iAddr+1,pilhaWhileAddr,listaInstrucoes); 
				pilhaWhileAddr = popWhileAddr(pilhaWhileAddr);

				char buf[20]; 
				sprintf(buf,"JUMP %d",jump); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes); 
			}
    break;

  case 42:
#line 413 "virtual.y"
    { 
			listaInstrucoes = insertInstrucao(iAddr++,"NOT",listaInstrucoes);
		}
    break;

  case 43:
#line 418 "virtual.y"
    { 
			if((yyvsp[(2) - (3)].op) == '>')
				listaInstrucoes = insertInstrucao(iAddr++,"SUP",listaInstrucoes);
			else if((yyvsp[(2) - (3)].op) == '<')
				listaInstrucoes = insertInstrucao(iAddr++,"INF",listaInstrucoes);
		}
    break;

  case 44:
#line 426 "virtual.y"
    { 
			if((yyvsp[(2) - (3)].op) == '>') 
				listaInstrucoes = insertInstrucao(iAddr++,"SUPEQ",listaInstrucoes);
			if((yyvsp[(2) - (3)].op) == '<') 
				listaInstrucoes = insertInstrucao(iAddr++,"INFEQ",listaInstrucoes);
			else if((yyvsp[(2) - (3)].op) == '=')
				listaInstrucoes = insertInstrucao(iAddr++,"EQUAL",listaInstrucoes);
			else if((yyvsp[(2) - (3)].op) == '!')
			{
				listaInstrucoes = insertInstrucao(iAddr++,"EQUAL",listaInstrucoes);
				listaInstrucoes = insertInstrucao(iAddr++,"NOT",listaInstrucoes);
			}
		}
    break;

  case 45:
#line 441 "virtual.y"
    {
			if((yyvsp[(2) - (3)].op) == '&') 
				listaInstrucoes = insertInstrucao(iAddr++,"MUL",listaInstrucoes);
			if((yyvsp[(2) - (3)].op) == '|') 
				listaInstrucoes = insertInstrucao(iAddr++,"ADD",listaInstrucoes);
		}
    break;

  case 46:
#line 449 "virtual.y"
    {
			if((yyvsp[(2) - (3)].op) == '+') 
				listaInstrucoes = insertInstrucao(iAddr++,"ADD",listaInstrucoes); 
			if((yyvsp[(2) - (3)].op) == '-') 
				listaInstrucoes = insertInstrucao(iAddr++,"SUB",listaInstrucoes); 	
		}
    break;

  case 47:
#line 457 "virtual.y"
    {
			if((yyvsp[(2) - (3)].op) == '*') 
				listaInstrucoes = insertInstrucao(iAddr++,"MUL",listaInstrucoes); 
			if((yyvsp[(2) - (3)].op) == '/') 
				listaInstrucoes = insertInstrucao(iAddr++,"DIV",listaInstrucoes);  
			if((yyvsp[(2) - (3)].op) == '%') 
				listaInstrucoes = insertInstrucao(iAddr++,"MOD",listaInstrucoes);  
		}
    break;

  case 48:
#line 467 "virtual.y"
    { 
			if(!existeVariavel((yyvsp[(1) - (1)].var),listaVariaveis))
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else if(strcmp(tipoVariavel((yyvsp[(1) - (1)].var),listaVariaveis),"inteiro") != 0)
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não é um escalar\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else if(!variavelInicializada((yyvsp[(1) - (1)].var),listaVariaveis))
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não está inicializada\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else 
			{
				char buf[20];
				sprintf(buf,"PUSHG %d",enderecoVariavel((yyvsp[(1) - (1)].var),listaVariaveis)); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);  
			}
		}
    break;

  case 49:
#line 492 "virtual.y"
    {	
			if(!existeVariavel((yyvsp[(1) - (1)].var),listaVariaveis))
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não declarada\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else if(strcmp(tipoVariavel((yyvsp[(1) - (1)].var),listaVariaveis),"array") != 0)
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não é um vector\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else if(!variavelInicializada((yyvsp[(1) - (1)].var),listaVariaveis))
			{
				erros = 1;
				fprintf(stderr,"l.%d erro: variável '%s' não está inicializada\n",yylineno,(yyvsp[(1) - (1)].var));
			}
			else 
			{
   				char buf[20];
				sprintf(buf,"PUSHI %d",enderecoVariavel((yyvsp[(1) - (1)].var),listaVariaveis)); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);	
			}
		}
    break;

  case 50:
#line 516 "virtual.y"
    {
			listaInstrucoes = insertInstrucao(iAddr++,"LOADN",listaInstrucoes);
		}
    break;

  case 51:
#line 521 "virtual.y"
    { 
			char buf[20];
			sprintf(buf,"PUSHI %d",(yyvsp[(1) - (1)].inteiro)); 
			listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
		}
    break;

  case 52:
#line 528 "virtual.y"
    { 
			if((yyvsp[(1) - (2)].op) == '-')
			{
				char buf[20];
				sprintf(buf,"PUSHI -1"); 
				listaInstrucoes = insertInstrucao(iAddr++,buf,listaInstrucoes);
				listaInstrucoes = insertInstrucao(iAddr++,"MUL",listaInstrucoes);
			}
		}
    break;


/* Line 1267 of yacc.c.  */
#line 2013 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 542 "virtual.y"


void yyerror(char* s)
{
   fprintf(stderr,"erro: %d: %s: %s\n",yylineno,s,yytext);
   erros = 1;
}

int main(int argc, char *argv[])
{
	if(argc < 2) 
	{ 
		printf("Introduzir ficheiro para compilação como argumento!\n"); 
		exit(0); 
	}

	listaVariaveis = malloc(sizeof(struct variavel));
	listaInstrucoes = malloc(sizeof(struct instrucao));
	pilhaIfAddr = malloc(sizeof(struct ifAddr));
	pilhaWhileAddr = malloc(sizeof(struct whileAddr));

	//--- PARSE ---//
	yyin = fopen(argv[1],"r");
   	if(yyin == NULL)
   	{
   		printf("Ficheiro não encontrado!\n"); 
		exit(0); 
   	}

   	yyparse();

   	//--- IMPRIMR OUTPUT ---//
   	filename = strdup(argv[1]);
	filename[strrchr(filename,'.')-filename] = '\0';
	FILE* f = fopen(filename,"w");

	if(!erros)
	{
		while(listaInstrucoes)
		{
			if(listaInstrucoes->instrucao)
			{
				fprintf(f,"_%06d: %s\n",listaInstrucoes->endereco,listaInstrucoes->instrucao);
				printf("_%06d: %s\n",listaInstrucoes->endereco,listaInstrucoes->instrucao);
			}
			listaInstrucoes = listaInstrucoes->next;
		}
	}
	else 
	{
		fprintf(f,"Houve erros durante a compilação\n");
	}

   	return 0;
}

