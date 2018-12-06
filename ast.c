// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <string.h>
#define _SVID_SOURCE

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr* ast_boolean(int v){
  BoolExpr* node=(BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind= VALOR;
  node->attr.value=v;
  return node;
}
BoolExpr* ast_booleanop(int operator,Expr* left, Expr* right){
  BoolExpr* node=(BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind= COMPARA;
  node->attr.comp.operator= operator;
  node->attr.comp.left=left;
  node->attr.comp.right=right;
  return node;
}


Cmd* ast_c_atrib(atributo* a){
  Cmd* node=(Cmd*) malloc(sizeof(Cmd));
  node->kind=E_ATTR;
  node->attr.a=a;
  return node;
}


Cmd* ast_c_decl(decl* d){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_DECL;
  node->attr.d=d;
  return node;
}

Cmd* ast_c_se(se* se){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_IF;
  node->attr.se=se;

  return node;
}

Cmd* ast_c_ciclo(ciclo* c){
  Cmd* node=(Cmd*) malloc (sizeof(Cmd));
  node->kind=E_CICLO;
  node->attr.c=c;

  return node;
}

Cmd* ast_c_scan(scan* s){
  Cmd* node=(Cmd *) malloc (sizeof(Cmd));
  node->kind=E_SCAN;
  node->attr.s=s;

  return node;
}

Cmd* ast_c_print(print* p){
  Cmd* node=(Cmd *) malloc (sizeof(Cmd));
  node->kind=E_PRINT;
  node->attr.p=p;

  return node;
}


atributo* ast_atrib(char* var, Expr* value){
  atributo* node=(atributo*) malloc(sizeof(atributo));
  node->var=strdup(var);
  node->value=value;
  return node;
}

decl* ast_decl(lvar_d* list){
  decl* node=(decl*) malloc(sizeof(decl));
  node->list=list;

  return node;
}

se* ast_se_s(BoolExpr* cond, Cmd* comandos){
  se* node=(se*) malloc(sizeof(se));
  node->cond=cond;
  node->comandos=lista_comandos(comandos,NULL);
  node->ncomandos=NULL;
  return node;
}

se* ast_se_bs(BoolExpr* cond, lcmd* comandos, Cmd* ncomandos){
  se* node=(se*) malloc(sizeof(se));
  node->cond=cond;
  node->comandos=comandos;
  node->ncomandos=lista_comandos(ncomandos,NULL);

  return node;
}

se* ast_se_bb(BoolExpr* cond, lcmd* comandos, lcmd* ncomandos){
  se* node=(se*) malloc(sizeof(se));
  node->cond=cond;
  node->comandos=comandos;
  node->ncomandos=ncomandos;

  return node;
}

print* ast_print(char* str, lvar_print* list){
  print* node=(print*) malloc(sizeof(print));
  node->str=strdup(str);
  node->list=list;

  return node;
}

scan* ast_scan(char* str, lvar_print* list){
  scan* node=(scan*) malloc(sizeof(scan));
  node->str=strdup(str);
  node->list=list;

  return node;
}

ciclo* ast_ciclo_s(BoolExpr* cond, Cmd* comando){
  ciclo* node=(ciclo*) malloc(sizeof(ciclo));
  node->cond=cond;
  node->list=lista_comandos(comando,NULL);

  return node;
}

ciclo* ast_ciclo_b(BoolExpr* cond, lcmd* list){
  ciclo* node=(ciclo*) malloc(sizeof(ciclo));
  node->cond=cond;
  node->list=list;

  return node;
}
lcmd* lista_comandos(Cmd* comando, lcmd* next){
  lcmd* node= (lcmd*) malloc (sizeof(lcmd));
  node->comando=comando;
  node->next=next;
  return node;
}

lvar_d* ast_lvd_a(atributo* atr, lvar_d* next){
  lvar_d* node=(lvar_d*) malloc(sizeof(lvar_d));
  node->kind=ATRI;
  node->attr.atri=atr;
  node->next=next;

  return node;
}

lvar_d* ast_lvd_v(char* str, lvar_d* next){
  lvar_d* node=(lvar_d*) malloc(sizeof(lvar_d));
  node->kind=VARI;
  node->attr.var=strdup(str);
  node->next=next;

  return node;
}

lvar_print* ast_lvprint(char* str, lvar_print* next){
  lvar_print* node=(lvar_print*) malloc(sizeof(lvar_print));
  node->var=strdup(str);
  node->next=next;

  return node;
}
