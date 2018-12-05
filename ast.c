// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

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
BoolExpr* ast_booleanop(int operator,BoolExpr* left, BoolExpr* right){
  BoolExpr* node=(BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind= COMPARA;
  node->attr.comp.operator= operator;
  node->attr.comp.left=left;
  node->attr.comp.right=right;
  return node;
}
