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
#line 1 "./gpp_interpreter.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gpp_interpreter.tab.h"

extern FILE* yyin;  // Input file for the lexer
extern FILE* yyout; // Output file for the lexer
extern int yyparse(); // Bison's parse function

void yyerror(const char *msg) {
    fprintf(yyout, "Error: %s\n", msg);
}

void error(const char* msg) {
    fprintf(yyout, "Error: %s\n", msg);
}


// Struct for identifiers
typedef struct Identifier {
    char name[20];
    float values[20];  // Array to hold list elements (up to 20 values)
    int list_size;     // Number of elements in the list
} Identifier;

// Initialize an instance of Identifier with list_size = 0
Identifier identifierTable[200] = { { .list_size = 0 } }; // All identifiers initialized with list_size = 0
int identifier_count = 0;

// Function to find an identifier by name
int find_identifier(const char* name) {
    for (int i = 0; i < identifier_count; i++) {
        if (strcmp(identifierTable[i].name, name) == 0) {
            return i; // Found, return the index
        }
    }
    return -1; // Not found
}

void set_identifier(const char* name, float value, int is_list) {
    int index = find_identifier(name);
    if (index != -1) {
        if (is_list) {
            // If it is a list, append the value to the list
            if (identifierTable[index].list_size < 20) {
                identifierTable[index].values[identifierTable[index].list_size++] = value;
            } else {
                error("List size overflow");
            }
        } else {
            // If it's a single value, just set the first index
            identifierTable[index].values[0] = value;
        }
    } else if (identifier_count < 100) {
        // Add new identifier
        strncpy(identifierTable[identifier_count].name, name, sizeof(identifierTable[identifier_count].name) - 1);
        if (is_list) {
            // Initialize as a list
            identifierTable[identifier_count].values[0] = value;
            identifierTable[identifier_count].list_size = 1; // One element in the list
        } else {
            // Set a single value
            identifierTable[identifier_count].values[0] = value;
            identifierTable[identifier_count].list_size = 0;
        }
        identifier_count++;
    } else {
        error("Identifier table overflow");
    }
}

// Function to get the value of an identifier (handles single values and lists)
float get_identifier_value(const char* name) {
    int index = find_identifier(name);
    if (index != -1) {
        return identifierTable[index].values[0]; // Return first value for single-valued identifiers
    } else {
        error("Undefined identifier");
        return -1; // Return a default value
    }
}

// Function to concatenate two lists
void concat_lists(int idx1, int idx2) {
    if (identifierTable[idx1].list_size + identifierTable[idx2].list_size <= 20) {
        for (int i = 0; i < identifierTable[idx2].list_size; i++) {
            identifierTable[idx1].values[identifierTable[idx1].list_size++] = identifierTable[idx2].values[i];
        }
    } else {
        error("Concatenation exceeds list size limit");
    }
}

// Function to append a value to a list
void append_to_list(int idx, float value) {
    if (identifierTable[idx].list_size < 20) {
        identifierTable[idx].values[identifierTable[idx].list_size++] = value;
    } else {
        error("List size overflow");
    }
}

// Function to create a list from given values
void create_list(int idx, float values[], int count) {
    if (count <= 20) {
        for (int i = 0; i < count; i++) {
            identifierTable[idx].values[i] = values[i];
        }
        identifierTable[idx].list_size = count;
    } else {
        error("List size exceeds maximum size");
    }
}

int yylex();
int isList = 0;


#line 192 "gpp_interpreter.tab.c"

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

#include "gpp_interpreter.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VALUEF = 3,                     /* VALUEF  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_KW_AND = 5,                     /* KW_AND  */
  YYSYMBOL_KW_OR = 6,                      /* KW_OR  */
  YYSYMBOL_KW_NOT = 7,                     /* KW_NOT  */
  YYSYMBOL_KW_EQUAL = 8,                   /* KW_EQUAL  */
  YYSYMBOL_KW_LESS = 9,                    /* KW_LESS  */
  YYSYMBOL_KW_NIL = 10,                    /* KW_NIL  */
  YYSYMBOL_KW_LIST = 11,                   /* KW_LIST  */
  YYSYMBOL_KW_APPEND = 12,                 /* KW_APPEND  */
  YYSYMBOL_KW_CONCAT = 13,                 /* KW_CONCAT  */
  YYSYMBOL_KW_SET = 14,                    /* KW_SET  */
  YYSYMBOL_KW_DEFFUN = 15,                 /* KW_DEFFUN  */
  YYSYMBOL_KW_DEFVAR = 16,                 /* KW_DEFVAR  */
  YYSYMBOL_KW_FOR = 17,                    /* KW_FOR  */
  YYSYMBOL_KW_WHILE = 18,                  /* KW_WHILE  */
  YYSYMBOL_KW_IF = 19,                     /* KW_IF  */
  YYSYMBOL_KW_EXIT = 20,                   /* KW_EXIT  */
  YYSYMBOL_KW_LOAD = 21,                   /* KW_LOAD  */
  YYSYMBOL_KW_DISP = 22,                   /* KW_DISP  */
  YYSYMBOL_KW_TRUE = 23,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 24,                  /* KW_FALSE  */
  YYSYMBOL_OP_PLUS = 25,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 26,                  /* OP_MINUS  */
  YYSYMBOL_OP_DIV = 27,                    /* OP_DIV  */
  YYSYMBOL_OP_MULT = 28,                   /* OP_MULT  */
  YYSYMBOL_OP_LIST = 29,                   /* OP_LIST  */
  YYSYMBOL_OP_OP = 30,                     /* OP_OP  */
  YYSYMBOL_OP_CP = 31,                     /* OP_CP  */
  YYSYMBOL_OP_COMMA = 32,                  /* OP_COMMA  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_START = 34,                     /* START  */
  YYSYMBOL_INPUT = 35,                     /* INPUT  */
  YYSYMBOL_EXPI = 36,                      /* EXPI  */
  YYSYMBOL_EXPB = 37,                      /* EXPB  */
  YYSYMBOL_EXPLIST = 38,                   /* EXPLIST  */
  YYSYMBOL_VALUES = 39,                    /* VALUES  */
  YYSYMBOL_STATEMENT = 40,                 /* STATEMENT  */
  YYSYMBOL_EXPILIST = 41,                  /* EXPILIST  */
  YYSYMBOL_FDEF = 42                       /* FDEF  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   149,   149,   150,   151,   152,   156,   183,   189,   208,
     209,   210,   211,   219,   220,   221,   222,   223,   224,   225,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   244,   254,   259,   262,   268,   272,   281,   286,
     296,   299,   305
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VALUEF", "IDENTIFIER",
  "KW_AND", "KW_OR", "KW_NOT", "KW_EQUAL", "KW_LESS", "KW_NIL", "KW_LIST",
  "KW_APPEND", "KW_CONCAT", "KW_SET", "KW_DEFFUN", "KW_DEFVAR", "KW_FOR",
  "KW_WHILE", "KW_IF", "KW_EXIT", "KW_LOAD", "KW_DISP", "KW_TRUE",
  "KW_FALSE", "OP_PLUS", "OP_MINUS", "OP_DIV", "OP_MULT", "OP_LIST",
  "OP_OP", "OP_CP", "OP_COMMA", "$accept", "START", "INPUT", "EXPI",
  "EXPB", "EXPLIST", "VALUES", "STATEMENT", "EXPILIST", "FDEF", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      75,   -76,   -76,   -76,   -76,   -76,   -24,   147,    51,   -76,
     -76,   -76,   -76,   -76,    16,    84,    84,    84,    92,    92,
      16,     1,    29,    21,    23,    84,     1,     1,     1,     1,
       1,   -76,   123,   -76,   -76,   -76,    37,   -76,   -76,     9,
      84,    84,    -2,   171,     1,    84,     1,    84,    40,   -76,
     -76,   204,    29,    36,    29,     1,    97,     1,     2,     1,
       1,     1,     1,    31,    22,   -76,    57,    42,    45,   -76,
      46,    66,    72,    78,   -76,    79,    80,    81,   189,    82,
      86,   -76,    53,   -76,    87,    88,    89,    90,     1,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,    59,   -76,   -76,   -76,   -76,    62,
     -76,   -76,   -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,    13,    29,    27,    28,     0,     0,     0,     3,
       6,     7,     8,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     2,     4,    37,     0,    30,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,    22,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,    40,     0,    18,     0,     0,     0,     0,     0,     5,
      36,    20,    21,    25,    23,    26,    24,    33,    32,    17,
      15,    16,    38,    40,     0,     9,    10,    12,    11,     0,
      39,    41,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,    32,   -18,     5,   -20,    47,   -76,   -75,   -76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    36,    13,    82,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    46,    54,    52,    49,    50,    14,   104,    58,    59,
      60,    61,    62,   109,    15,    16,    17,    18,    19,    35,
      40,    41,    42,    45,    47,    55,    70,    56,    72,    69,
      57,    51,    75,    83,    76,    88,    80,    77,    79,    81,
      33,    84,    85,    86,    87,    67,    68,    20,    21,    22,
      71,    31,    73,    89,     1,     2,    49,    50,     6,    53,
      90,     3,    49,    50,   103,    49,    50,    48,    65,    66,
      81,    74,    66,    91,     4,     5,    92,    93,     1,     2,
       6,    32,     0,    51,   102,     3,   111,    37,    38,    51,
     110,   111,    51,   112,     3,     1,     2,    94,     4,     5,
      49,    50,     3,    95,     6,     7,     0,     4,     5,    96,
      97,    98,    99,   100,    39,     4,     5,   101,   105,   106,
     107,   108,    43,     0,     0,     0,     6,    78,    15,    16,
      17,    18,    19,     0,    20,    21,    22,    23,    63,    24,
       0,     0,    25,    64,     0,    26,     0,     0,    27,    28,
      29,    30,    15,    16,    17,    18,    19,     0,    20,    21,
      22,    23,     0,    24,     0,     0,    25,     0,     0,    26,
       0,     0,    27,    28,    29,    30,    15,    16,    17,    18,
      19,     0,     0,     0,     0,    23,     0,    24,     0,     0,
      25,     0,     0,    26,     0,     0,    27,    28,    29,    30,
      20,    21,    22,    23,     0,    24,     0,     0,    25,     0,
       0,    26,     0,     0,    27,    28,    29,    30,    23,     0,
      24,     0,     0,    25,     0,     0,    26,     0,     0,    27,
      28,    29,    30
};

static const yytype_int8 yycheck[] =
{
      18,    19,    22,    21,     3,     4,    30,    82,    26,    27,
      28,    29,    30,    88,     5,     6,     7,     8,     9,     3,
      15,    16,    17,    18,    19,     4,    44,     4,    46,    31,
      25,    30,    52,    31,    54,     4,    56,    55,    56,    57,
       8,    59,    60,    61,    62,    40,    41,    11,    12,    13,
      45,     0,    47,    31,     3,     4,     3,     4,    29,    30,
       3,    10,     3,     4,    82,     3,     4,    20,    31,    32,
      88,    31,    32,    31,    23,    24,    31,    31,     3,     4,
      29,    30,    -1,    30,    31,    10,   104,     3,     4,    30,
      31,   109,    30,    31,    10,     3,     4,    31,    23,    24,
       3,     4,    10,    31,    29,    30,    -1,    23,    24,    31,
      31,    31,    31,    31,    30,    23,    24,    31,    31,    31,
      31,    31,    30,    -1,    -1,    -1,    29,    30,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    25,    26,
      27,    28,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    -1,    16,    -1,    -1,    19,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,
      19,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      11,    12,    13,    14,    -1,    16,    -1,    -1,    19,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    14,    -1,
      16,    -1,    -1,    19,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    10,    23,    24,    29,    30,    34,    35,
      36,    37,    38,    40,    30,     5,     6,     7,     8,     9,
      11,    12,    13,    14,    16,    19,    22,    25,    26,    27,
      28,     0,    30,    35,    42,     3,    39,     3,     4,    30,
      37,    37,    37,    30,    36,    37,    36,    37,    39,     3,
       4,    30,    36,    30,    38,     4,     4,    37,    36,    36,
      36,    36,    36,    15,    20,    31,    32,    37,    37,    31,
      36,    37,    36,    37,    31,    38,    38,    36,    30,    36,
      38,    36,    41,    31,    36,    36,    36,    36,     4,    31,
       3,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    36,    41,    31,    31,    31,    31,    41,
      31,    36,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    34,    34,    35,    35,    35,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    38,    38,    38,    38,    39,    39,    40,    40,
      41,    41,    42
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     4,     1,     1,     1,     5,
       5,     5,     5,     1,     1,     5,     5,     5,     4,     1,
       5,     5,     4,     5,     5,     5,     5,     1,     1,     1,
       1,     1,     5,     5,     4,     4,     3,     1,     5,     6,
       1,     2,     5
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
  case 5: /* START: START OP_OP KW_EXIT OP_CP  */
#line 152 "./gpp_interpreter.y"
                                {fprintf(yyout, "Exiting...\n"); exit(0); }
#line 1306 "gpp_interpreter.tab.c"
    break;

  case 6: /* INPUT: EXPI  */
#line 156 "./gpp_interpreter.y"
           { 
        if(isList == 0){
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.5f", (yyval.value));  // Convert float to string with 5 digits precision
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == '.') {
                    buffer[i] = 'f';  // Replace '.' with 'f'
                }
            }
            fprintf(yyout, "Result: %s\n", buffer); 
        }else{
            int idx = (yyvsp[0].value);
            fprintf(yyout, "Result: (");
            for (int i = 0; i < identifierTable[idx].list_size; i++) {
                char buffer[50];
                snprintf(buffer, sizeof(buffer), "%.5f", identifierTable[idx].values[i]);
                for (int j = 0; buffer[j] != '\0'; j++) {
                    if (buffer[j] == '.') {
                        buffer[j] = 'f';  // Replace '.' with 'f'
                    }
                }
                fprintf(yyout, "%s ", buffer);
            }
            fprintf(yyout, ")\n");
            isList = 0;
        }
    }
#line 1338 "gpp_interpreter.tab.c"
    break;

  case 7: /* INPUT: EXPB  */
#line 183 "./gpp_interpreter.y"
           { 
        if ((yyvsp[0].value) == 1.0f) 
            fprintf(yyout, "Result: TRUE\n"); 
        else 
            fprintf(yyout, "Result: False\n"); 
    }
#line 1349 "gpp_interpreter.tab.c"
    break;

  case 8: /* INPUT: EXPLIST  */
#line 189 "./gpp_interpreter.y"
              {
        int idx = (yyvsp[0].index);
        fprintf(yyout, "Result: (");
        for (int i = 0; i < identifierTable[idx].list_size; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.5f", identifierTable[idx].values[i]);
            for (int j = 0; buffer[j] != '\0'; j++) {
                if (buffer[j] == '.') {
                    buffer[j] = 'f';  // Replace '.' with 'f'
                }
            }
            fprintf(yyout, "%s ", buffer);
        }
        fprintf(yyout, ")\n");
    }
#line 1369 "gpp_interpreter.tab.c"
    break;

  case 9: /* EXPI: OP_OP OP_PLUS EXPI EXPI OP_CP  */
#line 208 "./gpp_interpreter.y"
                                    { (yyval.value) = (yyvsp[-2].value) + (yyvsp[-1].value); }
#line 1375 "gpp_interpreter.tab.c"
    break;

  case 10: /* EXPI: OP_OP OP_MINUS EXPI EXPI OP_CP  */
#line 209 "./gpp_interpreter.y"
                                     { (yyval.value) = (yyvsp[-2].value) - (yyvsp[-1].value); }
#line 1381 "gpp_interpreter.tab.c"
    break;

  case 11: /* EXPI: OP_OP OP_MULT EXPI EXPI OP_CP  */
#line 210 "./gpp_interpreter.y"
                                    { (yyval.value) = (yyvsp[-2].value) * (yyvsp[-1].value); }
#line 1387 "gpp_interpreter.tab.c"
    break;

  case 12: /* EXPI: OP_OP OP_DIV EXPI EXPI OP_CP  */
#line 211 "./gpp_interpreter.y"
                                   {
        if ((yyvsp[-1].value) == 0) {
            error("Division by zero!");
            (yyval.value) = -1;
        } else {
            (yyval.value) = (yyvsp[-2].value) / (yyvsp[-1].value);
        }
    }
#line 1400 "gpp_interpreter.tab.c"
    break;

  case 13: /* EXPI: IDENTIFIER  */
#line 219 "./gpp_interpreter.y"
                 { (yyval.value) = get_identifier_value((yyvsp[0].string)); }
#line 1406 "gpp_interpreter.tab.c"
    break;

  case 14: /* EXPI: VALUEF  */
#line 220 "./gpp_interpreter.y"
             { (yyval.value) = (yyvsp[0].value); }
#line 1412 "gpp_interpreter.tab.c"
    break;

  case 15: /* EXPI: OP_OP KW_DEFVAR IDENTIFIER EXPI OP_CP  */
#line 221 "./gpp_interpreter.y"
                                            { set_identifier((yyvsp[-2].string), (yyvsp[-1].value), 0); (yyval.value) = (yyvsp[-1].value); }
#line 1418 "gpp_interpreter.tab.c"
    break;

  case 16: /* EXPI: OP_OP KW_DEFVAR IDENTIFIER EXPLIST OP_CP  */
#line 222 "./gpp_interpreter.y"
                                               { set_identifier((yyvsp[-2].string), (yyvsp[-1].index), 0); (yyval.value) = (yyvsp[-1].index); isList = 1; }
#line 1424 "gpp_interpreter.tab.c"
    break;

  case 17: /* EXPI: OP_OP KW_SET IDENTIFIER EXPI OP_CP  */
#line 223 "./gpp_interpreter.y"
                                         { set_identifier((yyvsp[-2].string), (yyvsp[-1].value), 0); (yyval.value) = (yyvsp[-1].value); }
#line 1430 "gpp_interpreter.tab.c"
    break;

  case 18: /* EXPI: OP_OP KW_DISP EXPI OP_CP  */
#line 224 "./gpp_interpreter.y"
                               { (yyval.value) = (yyvsp[-1].value); }
#line 1436 "gpp_interpreter.tab.c"
    break;

  case 19: /* EXPI: STATEMENT  */
#line 225 "./gpp_interpreter.y"
                { (yyval.value) = (yyvsp[0].value); }
#line 1442 "gpp_interpreter.tab.c"
    break;

  case 20: /* EXPB: OP_OP KW_AND EXPB EXPB OP_CP  */
#line 229 "./gpp_interpreter.y"
                                      { (yyval.value) = (yyvsp[-2].value) && (yyvsp[-1].value); }
#line 1448 "gpp_interpreter.tab.c"
    break;

  case 21: /* EXPB: OP_OP KW_OR EXPB EXPB OP_CP  */
#line 230 "./gpp_interpreter.y"
                                      { (yyval.value) = (yyvsp[-2].value) || (yyvsp[-1].value); }
#line 1454 "gpp_interpreter.tab.c"
    break;

  case 22: /* EXPB: OP_OP KW_NOT EXPB OP_CP  */
#line 231 "./gpp_interpreter.y"
                                      { (yyval.value) = ((yyvsp[-1].value) == 0) ? 1.0f : 0.0f; }
#line 1460 "gpp_interpreter.tab.c"
    break;

  case 23: /* EXPB: OP_OP KW_EQUAL EXPB EXPB OP_CP  */
#line 232 "./gpp_interpreter.y"
                                      { if ((yyvsp[-2].value) == (yyvsp[-1].value)) (yyval.value) = 1.0f; else (yyval.value) = 0.0f; }
#line 1466 "gpp_interpreter.tab.c"
    break;

  case 24: /* EXPB: OP_OP KW_LESS EXPB EXPB OP_CP  */
#line 233 "./gpp_interpreter.y"
                                      { if ((yyvsp[-2].value) < (yyvsp[-1].value)) (yyval.value) = 1.0f; else (yyval.value) = 0.0f; }
#line 1472 "gpp_interpreter.tab.c"
    break;

  case 25: /* EXPB: OP_OP KW_EQUAL EXPI EXPI OP_CP  */
#line 234 "./gpp_interpreter.y"
                                      { if ((yyvsp[-2].value) == (yyvsp[-1].value)) (yyval.value) = 1.0f; else (yyval.value) = 0.0f; }
#line 1478 "gpp_interpreter.tab.c"
    break;

  case 26: /* EXPB: OP_OP KW_LESS EXPI EXPI OP_CP  */
#line 235 "./gpp_interpreter.y"
                                      { if ((yyvsp[-2].value) < (yyvsp[-1].value)) (yyval.value) = 1.0f; else (yyval.value) = 0.0f; }
#line 1484 "gpp_interpreter.tab.c"
    break;

  case 27: /* EXPB: KW_TRUE  */
#line 236 "./gpp_interpreter.y"
              { (yyval.value) = 1.0f; }
#line 1490 "gpp_interpreter.tab.c"
    break;

  case 28: /* EXPB: KW_FALSE  */
#line 237 "./gpp_interpreter.y"
               { (yyval.value) = 0.0f; }
#line 1496 "gpp_interpreter.tab.c"
    break;

  case 29: /* EXPB: KW_NIL  */
#line 238 "./gpp_interpreter.y"
             { (yyval.value) = 0.0f; }
#line 1502 "gpp_interpreter.tab.c"
    break;

  case 30: /* EXPB: VALUEF  */
#line 239 "./gpp_interpreter.y"
             { (yyval.value) = ((yyvsp[0].value) != 0.0f) ? 1.0f : 0.0f; }
#line 1508 "gpp_interpreter.tab.c"
    break;

  case 31: /* EXPB: IDENTIFIER  */
#line 240 "./gpp_interpreter.y"
                 { (yyval.value) = get_identifier_value((yyvsp[0].string)) != 0.0f ? 1.0f : 0.0f; }
#line 1514 "gpp_interpreter.tab.c"
    break;

  case 32: /* EXPLIST: OP_OP KW_CONCAT EXPLIST EXPLIST OP_CP  */
#line 244 "./gpp_interpreter.y"
                                            {
        int idx1 = (yyvsp[-2].index);
        int idx2 = (yyvsp[-1].index);
        if (idx1 < 0 || idx1 >= identifier_count || idx2 < 0 || idx2 >= identifier_count) {
            error("Invalid list index in CONCAT operation");
            (yyval.index) = -1; // Set $$ to an invalid value
        }
        concat_lists(idx1, idx2);  // Concatenate the lists
        (yyval.index) = idx1;  // Propagate the index of the resulting list
      }
#line 1529 "gpp_interpreter.tab.c"
    break;

  case 33: /* EXPLIST: OP_OP KW_APPEND EXPI EXPLIST OP_CP  */
#line 254 "./gpp_interpreter.y"
                                         {
        int idx = (yyvsp[-1].index);
        append_to_list(idx, (yyvsp[-2].value));  // Append a single value to the list
        (yyval.index) = idx;  // Propagate the index of the updated list
      }
#line 1539 "gpp_interpreter.tab.c"
    break;

  case 34: /* EXPLIST: OP_OP KW_LIST VALUES OP_CP  */
#line 259 "./gpp_interpreter.y"
                                 {
        (yyval.index) = (yyvsp[-1].index);
    }
#line 1547 "gpp_interpreter.tab.c"
    break;

  case 35: /* EXPLIST: OP_LIST OP_OP VALUES OP_CP  */
#line 262 "./gpp_interpreter.y"
                                 {
        (yyval.index) = (yyvsp[-1].index);
    }
#line 1555 "gpp_interpreter.tab.c"
    break;

  case 36: /* VALUES: VALUES OP_COMMA VALUEF  */
#line 268 "./gpp_interpreter.y"
                             {
        (yyval.index) = (yyvsp[-2].index);
        append_to_list((yyval.index), (yyvsp[0].value));
    }
#line 1564 "gpp_interpreter.tab.c"
    break;

  case 37: /* VALUES: VALUEF  */
#line 272 "./gpp_interpreter.y"
             {
        (yyval.index) = identifier_count;
        identifier_count++;
        float value = (yyvsp[0].value);
        create_list((yyval.index), &value, 1);  // Create a list with a single value
    }
#line 1575 "gpp_interpreter.tab.c"
    break;

  case 38: /* STATEMENT: OP_OP KW_IF EXPB EXPILIST OP_CP  */
#line 281 "./gpp_interpreter.y"
                                      {
        if ((yyvsp[-2].value) == 1.0f) { // Condition evaluates to true
            (yyval.value) = (yyvsp[-1].value); // Execute the block
        }
    }
#line 1585 "gpp_interpreter.tab.c"
    break;

  case 39: /* STATEMENT: OP_OP KW_IF EXPB EXPILIST EXPILIST OP_CP  */
#line 286 "./gpp_interpreter.y"
                                               {
        if ((yyvsp[-3].value) == 1.0f) {
            (yyval.value) = (yyvsp[-2].value); // Execute the first block
        } else {
            (yyval.value) = (yyvsp[-1].value); // Execute the second block
        }
    }
#line 1597 "gpp_interpreter.tab.c"
    break;

  case 40: /* EXPILIST: EXPI  */
#line 296 "./gpp_interpreter.y"
           { 
        (yyval.value) = (yyvsp[0].value); 
    }
#line 1605 "gpp_interpreter.tab.c"
    break;

  case 41: /* EXPILIST: EXPILIST EXPI  */
#line 299 "./gpp_interpreter.y"
                    { 
        (yyval.value) = (yyvsp[0].value); 
    }
#line 1613 "gpp_interpreter.tab.c"
    break;

  case 42: /* FDEF: OP_OP KW_DEFFUN IDENTIFIER EXPILIST OP_CP  */
#line 305 "./gpp_interpreter.y"
                                                {
        fprintf(yyout, "Result: %s\n", (yyvsp[-2].string));
    }
#line 1621 "gpp_interpreter.tab.c"
    break;


#line 1625 "gpp_interpreter.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 310 "./gpp_interpreter.y"



int main() {
    yyin = fopen("input.txt", "r");  // Open the input file
    yyout = fopen("output.txt", "w");  // Open the output file for writing
    if (yyin == NULL || yyout == NULL) {
        perror("Error opening files");
        exit(1);
    }
    yyparse();  // Start parsing

    fclose(yyin);
    fclose(yyout);
    return 0;
}

