// Tokens
%token
INT
STR
VAR
PLUS
MINUS
MULT
DIV
MOD
EQUAL
DIFF
LESS
GREATER
LESSEQ
GREATEREQ
CICLO
FAZ
IGUAL
SE
ELSE
PV
CHESQ
CHDIR
PESQ
PDIR
SCANF
PRINTF
INTEIRO
MAIN
VIRGULA
TRUE
FALSE
RETURN
WHILE


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
Cmd* commandValue;
char* textValue;
lcmd* lcmdValue;
decl* declValue;
atributo* atrValue;
se* ifValue;
ciclo* cicloValue;
print* printValue;
scan* scanValue;
}

%type <intValue> INT;
%type <exprValue> expr;
%type <boolValue> boolexpr;
%type <commandValue> cmd;
%type <lcmdValue> lcmd;

%type <declValue> decl;
%type <atrValue> atr;
%type <ifValue> if_cmd;
%type <cicloValue> ciclo;
%type <printValue> print;
%type <scanValue> scan;
%type <textValue> VAR
%type <textValue> STR





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
lcmd* root;
}

%%
program: INTEIRO MAIN PESQ PDIR CHESQ lcmd RETURN PV CHDIR { root = $6; }


expr:
INT {
$$ = ast_integer($1);
}
|
expr PLUS expr {
$$ = ast_operation(PLUS, $1, $3);
}
;
|
expr MINUS expr {
$$ = ast_operation(MINUS, $1, $3);
}
;
|
expr MULT expr {
$$ = ast_operation(MULT, $1, $3);
}
;
|
expr DIV expr{
$$ = ast_operation(DIV, $1, $3);
}
;
|
expr MOD expr {
$$ = ast_operation(MOD, $1, $3);
}
;

boolexpr:
expr EQUAL expr {
$$ = ast_booleanop(EQUAL,$1, $3);
}
;
|
expr DIFF expr {
$$ = ast_booleanop(DIFF,$1, $3);
}
;
|
expr LESS expr {
$$ = ast_booleanop(LESS,$1, $3);
}
;
|
expr GREATER expr {
$$ = ast_booleanop(GREATER,$1, $3);
}
;
|
expr LESSEQ expr {
$$ = ast_booleanop(LESSEQ,$1, $3);
}
;
|
expr GREATEREQ expr {
$$ = ast_booleanop(GREATEREQ,$1,$3);
}
;


lcmd:
cmd {
$$= lista_comandos($1,NULL);
}
;
|
cmd lcmd {
$$=lista_comandos($1,$2);
}
;


cmd:
decl PV{
$$ = ast_c_decl($1);
}
|
atr PV{
$$ = ast_c_atrib($1);
}
|
if_cmd {
$$ = ast_c_se($1);
}
|
ciclo {
$$ = ast_c_ciclo($1);
}
|
print PV {
$$ = ast_c_print($1);
}
|
scan PV {
$$= ast_c_scan($1);
}
;

decl:
INTEIRO VAR{
$$= ast_decl($2);
}
;


atr:
VAR IGUAL expr{
$$=ast_atrib($1,$3);
}
;

if_cmd:
SE PESQ boolexpr PDIR cmd{
$$=ast_se_s($3,$5);
}
|
SE PESQ boolexpr PDIR CHESQ lcmd CHDIR ELSE CHESQ lcmd CHDIR {
$$=ast_se_bb($3,$6,$10);
}
|
SE PESQ boolexpr PDIR CHESQ lcmd CHDIR ELSE cmd{
$$=ast_se_bs($3,$6,$9);
}
|
SE PESQ boolexpr PDIR CHESQ lcmd CHDIR{
$$=ast_se_bb($3,$6,NULL);
}
;

ciclo:
CICLO PESQ boolexpr PDIR cmd {
$$ = ast_ciclo_s($3, $5);
}
|
CICLO PESQ boolexpr PDIR CHESQ lcmd CHDIR {
$$= ast_ciclo_b($3,$6);
}
;

print:
PRINTF PESQ VAR PDIR{
$$=ast_print($3);
}
|
PRINTF PESQ INT PDIR{
$$=ast_printi($3);
}
;

scan:
SCANF PESQ INT VIRGULA VAR PDIR{
$$=ast_scan($3,$5);
};


%%

void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
;
