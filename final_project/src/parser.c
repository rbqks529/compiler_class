/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern int yylineno;
void yyerror(const char *s);

Node *root = NULL;

#line 84 "src/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_FUN = 6,                        /* FUN  */
  YYSYMBOL_VAL = 7,                        /* VAL  */
  YYSYMBOL_VAR = 8,                        /* VAR  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHEN = 11,                      /* WHEN  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_IN = 14,                        /* IN  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_PRINTLN = 16,                   /* PRINTLN  */
  YYSYMBOL_TYPE_INT = 17,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_STRING = 18,               /* TYPE_STRING  */
  YYSYMBOL_TYPE_BOOL = 19,                 /* TYPE_BOOL  */
  YYSYMBOL_TRUE = 20,                      /* TRUE  */
  YYSYMBOL_FALSE = 21,                     /* FALSE  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_DOTDOT = 28,                    /* DOTDOT  */
  YYSYMBOL_ARROW = 29,                     /* ARROW  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_UMINUS = 38,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 39,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '='  */
  YYSYMBOL_42_ = 42,                       /* ':'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* '{'  */
  YYSYMBOL_47_ = 47,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_stmt_list = 50,                 /* stmt_list  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_val_decl = 52,                  /* val_decl  */
  YYSYMBOL_var_decl = 53,                  /* var_decl  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_func_def = 55,                  /* func_def  */
  YYSYMBOL_param_list_opt = 56,            /* param_list_opt  */
  YYSYMBOL_param_list = 57,                /* param_list  */
  YYSYMBOL_param = 58,                     /* param  */
  YYSYMBOL_block = 59,                     /* block  */
  YYSYMBOL_assignment = 60,                /* assignment  */
  YYSYMBOL_if_stmt = 61,                   /* if_stmt  */
  YYSYMBOL_when_stmt = 62,                 /* when_stmt  */
  YYSYMBOL_when_branches = 63,             /* when_branches  */
  YYSYMBOL_when_branch = 64,               /* when_branch  */
  YYSYMBOL_while_stmt = 65,                /* while_stmt  */
  YYSYMBOL_for_stmt = 66,                  /* for_stmt  */
  YYSYMBOL_range = 67,                     /* range  */
  YYSYMBOL_return_stmt = 68,               /* return_stmt  */
  YYSYMBOL_print_stmt = 69,                /* print_stmt  */
  YYSYMBOL_expr_stmt = 70,                 /* expr_stmt  */
  YYSYMBOL_expr = 71,                      /* expr  */
  YYSYMBOL_logical_or = 72,                /* logical_or  */
  YYSYMBOL_logical_and = 73,               /* logical_and  */
  YYSYMBOL_equality = 74,                  /* equality  */
  YYSYMBOL_relational = 75,                /* relational  */
  YYSYMBOL_additive = 76,                  /* additive  */
  YYSYMBOL_multiplicative = 77,            /* multiplicative  */
  YYSYMBOL_unary = 78,                     /* unary  */
  YYSYMBOL_primary = 79,                   /* primary  */
  YYSYMBOL_func_call = 80,                 /* func_call  */
  YYSYMBOL_arg_list_opt = 81,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 82,                  /* arg_list  */
  YYSYMBOL_if_expr = 83                    /* if_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,     2,     2,
      43,    44,    34,    32,    45,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    40,
      30,    41,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    45,    45,    51,    52,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    78,    80,    85,
      87,    92,    93,    94,    98,   100,   106,   107,   111,   113,
     124,   129,   134,   139,   141,   143,   148,   153,   155,   166,
     168,   173,   178,   183,   188,   190,   195,   200,   205,   209,
     210,   215,   216,   221,   222,   224,   229,   230,   232,   234,
     236,   241,   242,   244,   249,   250,   252,   254,   259,   260,
     262,   267,   268,   269,   270,   271,   272,   273,   274,   279,
     285,   286,   290,   292,   303
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "INTEGER",
  "STRING", "FUN", "VAL", "VAR", "IF", "ELSE", "WHEN", "WHILE", "FOR",
  "IN", "RETURN", "PRINTLN", "TYPE_INT", "TYPE_STRING", "TYPE_BOOL",
  "TRUE", "FALSE", "EQ", "NE", "LE", "GE", "AND", "OR", "DOTDOT", "ARROW",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "UMINUS",
  "LOWER_THAN_ELSE", "';'", "'='", "':'", "'('", "')'", "','", "'{'",
  "'}'", "$accept", "program", "stmt_list", "statement", "val_decl",
  "var_decl", "type", "func_def", "param_list_opt", "param_list", "param",
  "block", "assignment", "if_stmt", "when_stmt", "when_branches",
  "when_branch", "while_stmt", "for_stmt", "range", "return_stmt",
  "print_stmt", "expr_stmt", "expr", "logical_or", "logical_and",
  "equality", "relational", "additive", "multiplicative", "unary",
  "primary", "func_call", "arg_list_opt", "arg_list", "if_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -111,     3,   162,  -111,   -27,  -111,  -111,     5,    17,    19,
      -7,     2,     7,    13,   189,    15,  -111,  -111,   189,   189,
     189,  -111,  -111,  -111,  -111,  -111,  -111,    23,  -111,  -111,
    -111,  -111,    27,    32,    34,  -111,    55,    28,    30,    45,
      48,   -24,  -111,  -111,  -111,  -111,   189,   189,    47,    36,
      57,   189,   189,   189,    91,    65,    71,  -111,   189,  -111,
    -111,    72,    80,  -111,  -111,  -111,  -111,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
    -111,  -111,    74,    70,   116,   189,    11,   189,    11,    77,
      84,    86,   110,   189,    87,  -111,  -111,    28,    30,    45,
      45,    48,    48,    48,    48,   -24,   -24,  -111,  -111,  -111,
    -111,   189,    90,    89,    93,  -111,    94,  -111,  -111,  -111,
      95,   100,   101,    22,    98,    99,   189,    97,  -111,  -111,
      11,   -37,   116,  -111,   189,  -111,   189,   125,   139,    14,
    -111,   106,   127,   189,  -111,    11,  -111,  -111,   117,   119,
      -5,   189,   131,   143,  -111,   132,    99,   189,    99,  -111,
    -111,   113,  -111,  -111,  -111,   189,  -111,  -111,   189,  -111,
    -111,  -111,   189,  -111,  -111,   118,    99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    75,    71,    72,     0,     0,     0,
       0,     0,     0,     0,    44,     0,    73,    74,     0,     0,
       0,     3,     4,     5,     6,     7,    16,     0,     9,    10,
      11,    12,     0,     0,     0,    47,    48,    49,    51,    53,
      56,    61,    64,    68,    76,    77,     0,    80,     0,     0,
       0,     0,     0,     0,     0,    75,     0,    45,     0,    70,
      69,     0,     0,     8,    13,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    82,     0,    81,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,    31,    50,    52,    54,
      55,    59,    60,    57,    58,    62,    63,    65,    66,    67,
      79,     0,     0,     0,    27,    28,     0,    21,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    83,
       0,     0,     0,    17,     0,    19,     0,    33,     0,     0,
      41,     0,     0,     0,    30,     0,    24,    29,     0,     0,
       0,     0,     0,     0,    37,     0,     0,     0,     0,    18,
      20,     0,    34,    35,    84,     0,    36,    38,     0,    42,
      43,    25,     0,    40,    39,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,   151,  -111,  -111,  -111,   -81,  -111,  -111,  -111,
      49,  -110,  -111,    29,  -111,  -111,    38,  -111,  -111,  -111,
    -111,  -111,  -111,   -14,  -111,   120,   121,    37,    31,    35,
     -17,  -111,  -111,  -111,  -111,  -111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    22,    23,    24,   120,    25,   113,   114,
     115,    26,    27,    28,    29,   153,   154,    30,    31,   141,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    82,    83,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    59,    60,     3,   161,   145,    61,   122,    48,    21,
      77,    78,    79,   137,    46,   140,    47,    55,     5,     6,
      49,   146,    50,    56,   152,    55,     5,     6,   117,   118,
     119,    56,    80,    81,    16,    17,    51,    89,    90,    91,
     162,    21,    16,    17,    94,    52,   169,    18,   171,   144,
      53,    19,    69,    70,    68,    18,    54,    20,    58,    19,
     107,   108,   109,    63,   158,    20,   137,    64,    21,    71,
      72,   116,    65,   121,    66,    73,    74,    85,    86,   127,
      75,    76,    67,     4,     5,     6,     7,     8,     9,    10,
      84,    11,    12,    13,    92,    14,    15,   129,    87,    88,
      16,    17,   101,   102,   103,   104,    99,   100,    47,   138,
     105,   106,   142,    18,    93,   111,    95,    19,   110,   112,
     148,   123,   149,    20,   126,   155,    21,    96,   124,   138,
     125,   128,   130,   131,   133,   150,   134,   164,   132,   155,
     135,   143,   136,   170,   139,    21,    55,     5,     6,   151,
     156,   173,    56,   152,   174,   157,   172,   159,   175,   160,
     165,   168,   176,    16,    17,     4,     5,     6,     7,     8,
       9,    10,    62,    11,    12,    13,    18,    14,    15,   163,
      19,   147,    16,    17,     0,     0,    20,    97,     0,    98,
     166,   167,    55,     5,     6,    18,     0,     0,    56,    19,
       0,     0,     0,     0,     0,    20,     0,     0,    21,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,    19,     0,     0,     0,
       0,     0,    20
};

static const yytype_int16 yycheck[] =
{
      14,    18,    19,     0,     9,    42,    20,    88,     3,    46,
      34,    35,    36,   123,    41,   125,    43,     3,     4,     5,
       3,   131,     3,     9,    10,     3,     4,     5,    17,    18,
      19,     9,    46,    47,    20,    21,    43,    51,    52,    53,
     150,    46,    20,    21,    58,    43,   156,    33,   158,   130,
      43,    37,    22,    23,    26,    33,    43,    43,    43,    37,
      77,    78,    79,    40,   145,    43,   176,    40,    46,    24,
      25,    85,    40,    87,    40,    30,    31,    41,    42,    93,
      32,    33,    27,     3,     4,     5,     6,     7,     8,     9,
      43,    11,    12,    13,     3,    15,    16,   111,    41,    42,
      20,    21,    71,    72,    73,    74,    69,    70,    43,   123,
      75,    76,   126,    33,    43,    45,    44,    37,    44,     3,
     134,    44,   136,    43,    14,   139,    46,    47,    44,   143,
      44,    44,    42,    44,    40,    10,    41,   151,    45,   153,
      40,    44,    41,   157,    46,    46,     3,     4,     5,    10,
      44,   165,     9,    10,   168,    28,    43,    40,   172,    40,
      29,    29,    44,    20,    21,     3,     4,     5,     6,     7,
       8,     9,    21,    11,    12,    13,    33,    15,    16,   150,
      37,   132,    20,    21,    -1,    -1,    43,    67,    -1,    68,
      47,   153,     3,     4,     5,    33,    -1,    -1,     9,    37,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,    50,     0,     3,     4,     5,     6,     7,     8,
       9,    11,    12,    13,    15,    16,    20,    21,    33,    37,
      43,    46,    51,    52,    53,    55,    59,    60,    61,    62,
      65,    66,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    83,    41,    43,     3,     3,
       3,    43,    43,    43,    43,     3,     9,    71,    43,    78,
      78,    71,    50,    40,    40,    40,    40,    27,    26,    22,
      23,    24,    25,    30,    31,    32,    33,    34,    35,    36,
      71,    71,    81,    82,    43,    41,    42,    41,    42,    71,
      71,    71,     3,    43,    71,    44,    47,    73,    74,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    78,
      44,    45,     3,    56,    57,    58,    71,    17,    18,    19,
      54,    71,    54,    44,    44,    44,    14,    71,    44,    71,
      42,    44,    45,    40,    41,    40,    41,    59,    71,    46,
      59,    67,    71,    44,    54,    42,    59,    58,    71,    71,
      10,    10,    10,    63,    64,    71,    44,    28,    54,    40,
      40,     9,    59,    61,    71,    29,    47,    64,    29,    59,
      71,    59,    43,    71,    71,    71,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    57,    57,
      58,    59,    60,    61,    61,    61,    62,    63,    63,    64,
      64,    65,    66,    67,    68,    68,    69,    70,    71,    72,
      72,    73,    73,    74,    74,    74,    75,    75,    75,    75,
      75,    76,    76,    76,    77,    77,    77,    77,    78,    78,
      78,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      81,    81,    82,    82,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     2,     2,     1,     5,     7,     5,
       7,     1,     1,     1,     6,     8,     0,     1,     1,     3,
       3,     3,     3,     5,     7,     7,     7,     1,     2,     3,
       3,     5,     7,     3,     1,     2,     4,     1,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       0,     1,     1,     3,     7
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: stmt_list  */
#line 46 "src/parser.y"
    { yyval = node(NK_PROGRAM, yylineno, NULL, 1, yyvsp[0]); root = yyval; }
#line 1551 "src/parser.c"
    break;

  case 3: /* stmt_list: %empty  */
#line 51 "src/parser.y"
    { yyval = node(NK_STMT_LIST, yylineno, NULL, 0); }
#line 1557 "src/parser.c"
    break;

  case 4: /* stmt_list: stmt_list statement  */
#line 53 "src/parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-1]->nchild + 1, sizeof(Node*));
      for (int i = 0; i < yyvsp[-1]->nchild; i++) arr[i] = yyvsp[-1]->child[i];
      arr[yyvsp[-1]->nchild] = yyvsp[0];
      yyval = nodev(NK_STMT_LIST, yylineno, NULL, yyvsp[-1]->nchild + 1, arr);
      free(yyvsp[-1]->child); yyvsp[-1]->child = NULL; yyvsp[-1]->nchild = 0; free(yyvsp[-1]);
    }
#line 1569 "src/parser.c"
    break;

  case 17: /* val_decl: VAL IDENT '=' expr ';'  */
#line 79 "src/parser.y"
    { yyval = node(NK_VAL_DECL, yylineno, yyvsp[-3]->op, 1, yyvsp[-1]); free_ast(yyvsp[-3]); }
#line 1575 "src/parser.c"
    break;

  case 18: /* val_decl: VAL IDENT ':' type '=' expr ';'  */
#line 81 "src/parser.y"
    { yyval = node(NK_VAL_DECL, yylineno, yyvsp[-5]->op, 2, yyvsp[-3], yyvsp[-1]); free_ast(yyvsp[-5]); }
#line 1581 "src/parser.c"
    break;

  case 19: /* var_decl: VAR IDENT '=' expr ';'  */
#line 86 "src/parser.y"
    { yyval = node(NK_VAR_DECL, yylineno, yyvsp[-3]->op, 1, yyvsp[-1]); yyval->is_mutable = 1; free_ast(yyvsp[-3]); }
#line 1587 "src/parser.c"
    break;

  case 20: /* var_decl: VAR IDENT ':' type '=' expr ';'  */
#line 88 "src/parser.y"
    { yyval = node(NK_VAR_DECL, yylineno, yyvsp[-5]->op, 2, yyvsp[-3], yyvsp[-1]); yyval->is_mutable = 1; free_ast(yyvsp[-5]); }
#line 1593 "src/parser.c"
    break;

  case 24: /* func_def: FUN IDENT '(' param_list_opt ')' block  */
#line 99 "src/parser.y"
    { yyval = node(NK_FUNC_DEF, yylineno, yyvsp[-4]->op, 2, yyvsp[-2], yyvsp[0]); free_ast(yyvsp[-4]); }
#line 1599 "src/parser.c"
    break;

  case 25: /* func_def: FUN IDENT '(' param_list_opt ')' ':' type block  */
#line 101 "src/parser.y"
    { yyval = node(NK_FUNC_DEF, yylineno, yyvsp[-6]->op, 3, yyvsp[-4], yyvsp[-1], yyvsp[0]); free_ast(yyvsp[-6]); }
#line 1605 "src/parser.c"
    break;

  case 26: /* param_list_opt: %empty  */
#line 106 "src/parser.y"
    { yyval = node(NK_PARAM_LIST, yylineno, NULL, 0); }
#line 1611 "src/parser.c"
    break;

  case 28: /* param_list: param  */
#line 112 "src/parser.y"
    { yyval = node(NK_PARAM_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1617 "src/parser.c"
    break;

  case 29: /* param_list: param_list ',' param  */
#line 114 "src/parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-2]->nchild + 1, sizeof(Node*));
      for (int i = 0; i < yyvsp[-2]->nchild; i++) arr[i] = yyvsp[-2]->child[i];
      arr[yyvsp[-2]->nchild] = yyvsp[0];
      yyval = nodev(NK_PARAM_LIST, yylineno, NULL, yyvsp[-2]->nchild + 1, arr);
      free(yyvsp[-2]->child); yyvsp[-2]->child = NULL; yyvsp[-2]->nchild = 0; free(yyvsp[-2]);
    }
#line 1629 "src/parser.c"
    break;

  case 30: /* param: IDENT ':' type  */
#line 125 "src/parser.y"
    { yyval = node(NK_PARAM, yylineno, yyvsp[-2]->op, 1, yyvsp[0]); free_ast(yyvsp[-2]); }
#line 1635 "src/parser.c"
    break;

  case 31: /* block: '{' stmt_list '}'  */
#line 130 "src/parser.y"
    { yyval = node(NK_BLOCK, yylineno, NULL, 1, yyvsp[-1]); }
#line 1641 "src/parser.c"
    break;

  case 32: /* assignment: IDENT '=' expr  */
#line 135 "src/parser.y"
    { yyval = node(NK_ASSIGN, yylineno, yyvsp[-2]->op, 1, yyvsp[0]); free_ast(yyvsp[-2]); }
#line 1647 "src/parser.c"
    break;

  case 33: /* if_stmt: IF '(' expr ')' block  */
#line 140 "src/parser.y"
    { yyval = node(NK_IF, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1653 "src/parser.c"
    break;

  case 34: /* if_stmt: IF '(' expr ')' block ELSE block  */
#line 142 "src/parser.y"
    { yyval = node(NK_IF, yylineno, "else", 3, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 1659 "src/parser.c"
    break;

  case 35: /* if_stmt: IF '(' expr ')' block ELSE if_stmt  */
#line 144 "src/parser.y"
    { yyval = node(NK_IF, yylineno, "else", 3, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 1665 "src/parser.c"
    break;

  case 36: /* when_stmt: WHEN '(' expr ')' '{' when_branches '}'  */
#line 149 "src/parser.y"
    { yyval = node(NK_WHEN, yylineno, NULL, 2, yyvsp[-4], yyvsp[-1]); }
#line 1671 "src/parser.c"
    break;

  case 37: /* when_branches: when_branch  */
#line 154 "src/parser.y"
    { yyval = node(NK_STMT_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1677 "src/parser.c"
    break;

  case 38: /* when_branches: when_branches when_branch  */
#line 156 "src/parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-1]->nchild + 1, sizeof(Node*));
      for (int i = 0; i < yyvsp[-1]->nchild; i++) arr[i] = yyvsp[-1]->child[i];
      arr[yyvsp[-1]->nchild] = yyvsp[0];
      yyval = nodev(NK_STMT_LIST, yylineno, NULL, yyvsp[-1]->nchild + 1, arr);
      free(yyvsp[-1]->child); yyvsp[-1]->child = NULL; yyvsp[-1]->nchild = 0; free(yyvsp[-1]);
    }
#line 1689 "src/parser.c"
    break;

  case 39: /* when_branch: expr ARROW expr  */
#line 167 "src/parser.y"
    { yyval = node(NK_WHEN_BRANCH, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1695 "src/parser.c"
    break;

  case 40: /* when_branch: ELSE ARROW expr  */
#line 169 "src/parser.y"
    { yyval = node(NK_WHEN_BRANCH, yylineno, "else", 1, yyvsp[0]); }
#line 1701 "src/parser.c"
    break;

  case 41: /* while_stmt: WHILE '(' expr ')' block  */
#line 174 "src/parser.y"
    { yyval = node(NK_WHILE, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1707 "src/parser.c"
    break;

  case 42: /* for_stmt: FOR '(' IDENT IN range ')' block  */
#line 179 "src/parser.y"
    { yyval = node(NK_FOR, yylineno, yyvsp[-4]->op, 2, yyvsp[-2], yyvsp[0]); free_ast(yyvsp[-4]); }
#line 1713 "src/parser.c"
    break;

  case 43: /* range: expr DOTDOT expr  */
#line 184 "src/parser.y"
    { yyval = node(NK_RANGE, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1719 "src/parser.c"
    break;

  case 44: /* return_stmt: RETURN  */
#line 189 "src/parser.y"
    { yyval = node(NK_RETURN, yylineno, NULL, 0); }
#line 1725 "src/parser.c"
    break;

  case 45: /* return_stmt: RETURN expr  */
#line 191 "src/parser.y"
    { yyval = node(NK_RETURN, yylineno, NULL, 1, yyvsp[0]); }
#line 1731 "src/parser.c"
    break;

  case 46: /* print_stmt: PRINTLN '(' expr ')'  */
#line 196 "src/parser.y"
    { yyval = node(NK_PRINT, yylineno, NULL, 1, yyvsp[-1]); }
#line 1737 "src/parser.c"
    break;

  case 47: /* expr_stmt: expr  */
#line 201 "src/parser.y"
    { yyval = node(NK_EXPR_STMT, yylineno, NULL, 1, yyvsp[0]); }
#line 1743 "src/parser.c"
    break;

  case 50: /* logical_or: logical_or OR logical_and  */
#line 211 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "||", 2, yyvsp[-2], yyvsp[0]); }
#line 1749 "src/parser.c"
    break;

  case 52: /* logical_and: logical_and AND equality  */
#line 217 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "&&", 2, yyvsp[-2], yyvsp[0]); }
#line 1755 "src/parser.c"
    break;

  case 54: /* equality: equality EQ relational  */
#line 223 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "==", 2, yyvsp[-2], yyvsp[0]); }
#line 1761 "src/parser.c"
    break;

  case 55: /* equality: equality NE relational  */
#line 225 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "!=", 2, yyvsp[-2], yyvsp[0]); }
#line 1767 "src/parser.c"
    break;

  case 57: /* relational: relational '<' additive  */
#line 231 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "<", 2, yyvsp[-2], yyvsp[0]); }
#line 1773 "src/parser.c"
    break;

  case 58: /* relational: relational '>' additive  */
#line 233 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, ">", 2, yyvsp[-2], yyvsp[0]); }
#line 1779 "src/parser.c"
    break;

  case 59: /* relational: relational LE additive  */
#line 235 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "<=", 2, yyvsp[-2], yyvsp[0]); }
#line 1785 "src/parser.c"
    break;

  case 60: /* relational: relational GE additive  */
#line 237 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, ">=", 2, yyvsp[-2], yyvsp[0]); }
#line 1791 "src/parser.c"
    break;

  case 62: /* additive: additive '+' multiplicative  */
#line 243 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "+", 2, yyvsp[-2], yyvsp[0]); }
#line 1797 "src/parser.c"
    break;

  case 63: /* additive: additive '-' multiplicative  */
#line 245 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "-", 2, yyvsp[-2], yyvsp[0]); }
#line 1803 "src/parser.c"
    break;

  case 65: /* multiplicative: multiplicative '*' unary  */
#line 251 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "*", 2, yyvsp[-2], yyvsp[0]); }
#line 1809 "src/parser.c"
    break;

  case 66: /* multiplicative: multiplicative '/' unary  */
#line 253 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "/", 2, yyvsp[-2], yyvsp[0]); }
#line 1815 "src/parser.c"
    break;

  case 67: /* multiplicative: multiplicative '%' unary  */
#line 255 "src/parser.y"
    { yyval = node(NK_BINOP, yylineno, "%", 2, yyvsp[-2], yyvsp[0]); }
#line 1821 "src/parser.c"
    break;

  case 69: /* unary: '!' unary  */
#line 261 "src/parser.y"
    { yyval = node(NK_UNOP, yylineno, "!", 1, yyvsp[0]); }
#line 1827 "src/parser.c"
    break;

  case 70: /* unary: '-' unary  */
#line 263 "src/parser.y"
    { yyval = node(NK_UNOP, yylineno, "-", 1, yyvsp[0]); }
#line 1833 "src/parser.c"
    break;

  case 78: /* primary: '(' expr ')'  */
#line 275 "src/parser.y"
    { yyval = yyvsp[-1]; }
#line 1839 "src/parser.c"
    break;

  case 79: /* func_call: IDENT '(' arg_list_opt ')'  */
#line 280 "src/parser.y"
    { yyval = node(NK_CALL, yylineno, yyvsp[-3]->op, 1, yyvsp[-1]); free_ast(yyvsp[-3]); }
#line 1845 "src/parser.c"
    break;

  case 80: /* arg_list_opt: %empty  */
#line 285 "src/parser.y"
    { yyval = node(NK_ARG_LIST, yylineno, NULL, 0); }
#line 1851 "src/parser.c"
    break;

  case 82: /* arg_list: expr  */
#line 291 "src/parser.y"
    { yyval = node(NK_ARG_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1857 "src/parser.c"
    break;

  case 83: /* arg_list: arg_list ',' expr  */
#line 293 "src/parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-2]->nchild + 1, sizeof(Node*));
      for (int i = 0; i < yyvsp[-2]->nchild; i++) arr[i] = yyvsp[-2]->child[i];
      arr[yyvsp[-2]->nchild] = yyvsp[0];
      yyval = nodev(NK_ARG_LIST, yylineno, NULL, yyvsp[-2]->nchild + 1, arr);
      free(yyvsp[-2]->child); yyvsp[-2]->child = NULL; yyvsp[-2]->nchild = 0; free(yyvsp[-2]);
    }
#line 1869 "src/parser.c"
    break;

  case 84: /* if_expr: IF '(' expr ')' expr ELSE expr  */
#line 304 "src/parser.y"
    { yyval = node(NK_IF_EXPR, yylineno, NULL, 3, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 1875 "src/parser.c"
    break;


#line 1879 "src/parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 307 "src/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
