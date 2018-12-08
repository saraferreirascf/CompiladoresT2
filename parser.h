/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 87 "parser.bison" /* yacc.c:1909  */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
lcmd* root;

#line 57 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    STR = 259,
    VAR = 260,
    PLUS = 261,
    MINUS = 262,
    MULT = 263,
    DIV = 264,
    MOD = 265,
    EQUAL = 266,
    DIFF = 267,
    LESS = 268,
    GREATER = 269,
    LESSEQ = 270,
    GREATEREQ = 271,
    CICLO = 272,
    FAZ = 273,
    IGUAL = 274,
    SE = 275,
    ELSE = 276,
    PV = 277,
    CHESQ = 278,
    CHDIR = 279,
    PESQ = 280,
    PDIR = 281,
    SCANF = 282,
    PRINTF = 283,
    INTEIRO = 284,
    MAIN = 285,
    VIRGULA = 286,
    TRUE = 287,
    FALSE = 288,
    RETURN = 289,
    WHILE = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 47 "parser.bison" /* yacc.c:1909  */

int intValue;
Expr* exprValue;
BoolExpr* boolValue;
Cmd* commandValue;
char* textValue;
lcmd* lcmdValue;
lvar_d* lvarValue;
lvar_print* lvarprintValue;
decl* declValue;
atributo* atrValue;
se* ifValue;
ciclo* cicloValue;
print* printValue;
scan* scanValue;

#line 122 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
