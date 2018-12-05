// Tokens
%token
INT
PLUS
MINUS
MULT
DIV
MOD
EQUAL
DIFF
LESS
GREATER //nao ha no opcode
LESSEQ
GREATEREQ


// Operator associativity & precedence
%left PLUS MINUS
%left DIV MULT
%left MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
int intValue;
Expr* exprValue;
BoolExpr* boolValue;

}

%type <intValue> INT
//%type <exprValue> expr
%type <boolValue> bool


// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
BoolExpr* root;
}

%%
program: bool { root=$1; }


//expr:
//INT {
//$$ = ast_integer($1);
//}
//;
//|
//expr PLUS expr {
//$$ = ast_operation(PLUS, $1, $3);
//}
//;
//|
//expr MINUS expr {
//$$ = ast_operation(MINUS, $1, $3);
//}
//;
//|
//expr MULT expr {
//$$ = ast_operation(MULT, $1, $3);
//}
//;
//|
//expr DIV expr{
//$$ = ast_operation(DIV, $1, $3);
//}
//;
//|
//expr MOD expr {
//$$ = ast_operation(MOD, $1, $3);
//}
//;

bool:
INT {
$$ = ast_boolean($1);
}
;
|
bool EQUAL bool {
$$ = ast_booleanop(EQUAL,$1, $3);
}
;
|
bool DIFF bool {
$$ = ast_booleanop(DIFF,$1, $3);
}
;
|
bool LESS bool {
$$ = ast_booleanop(LESS,$1, $3);
}
;
|
bool GREATER bool {
$$ = ast_booleanop(GREATER,$1, $3);
}
;
|
bool LESSEQ bool {
$$ = ast_booleanop(LESSEQ,$1, $3);
}
;
|
bool GREATEREQ bool {
$$ = ast_booleanop(GREATEREQ,$1,$3);
}
;

%%

void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
