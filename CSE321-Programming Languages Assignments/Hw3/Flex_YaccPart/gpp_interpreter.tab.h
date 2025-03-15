/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GPP_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_GPP_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VALUEF = 258,                  /* VALUEF  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    KW_AND = 260,                  /* KW_AND  */
    KW_OR = 261,                   /* KW_OR  */
    KW_NOT = 262,                  /* KW_NOT  */
    KW_EQUAL = 263,                /* KW_EQUAL  */
    KW_LESS = 264,                 /* KW_LESS  */
    KW_NIL = 265,                  /* KW_NIL  */
    KW_LIST = 266,                 /* KW_LIST  */
    KW_APPEND = 267,               /* KW_APPEND  */
    KW_CONCAT = 268,               /* KW_CONCAT  */
    KW_SET = 269,                  /* KW_SET  */
    KW_DEFFUN = 270,               /* KW_DEFFUN  */
    KW_DEFVAR = 271,               /* KW_DEFVAR  */
    KW_FOR = 272,                  /* KW_FOR  */
    KW_WHILE = 273,                /* KW_WHILE  */
    KW_IF = 274,                   /* KW_IF  */
    KW_EXIT = 275,                 /* KW_EXIT  */
    KW_LOAD = 276,                 /* KW_LOAD  */
    KW_DISP = 277,                 /* KW_DISP  */
    KW_TRUE = 278,                 /* KW_TRUE  */
    KW_FALSE = 279,                /* KW_FALSE  */
    OP_PLUS = 280,                 /* OP_PLUS  */
    OP_MINUS = 281,                /* OP_MINUS  */
    OP_DIV = 282,                  /* OP_DIV  */
    OP_MULT = 283,                 /* OP_MULT  */
    OP_LIST = 284,                 /* OP_LIST  */
    OP_OP = 285,                   /* OP_OP  */
    OP_CP = 286,                   /* OP_CP  */
    OP_COMMA = 287                 /* OP_COMMA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 122 "./gpp_interpreter.y"

    float value;
    char string[20];
    int index;

#line 102 "gpp_interpreter.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GPP_INTERPRETER_TAB_H_INCLUDED  */
