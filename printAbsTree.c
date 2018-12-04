#include <stdio.h>
#include "parser.h"
#include "ast.h"

void printExpr(Expr* expr);
void printBool(BoolExpr* expr);
void print_atr(atributo* a);
void print_cmd(Cmd* c);
void print_decl(decl* dl);
void print_ciclo(ciclo* c);
void print_se(se* se);
void print_print(print* p);
void print_scan(scan* s);
void print_lcmd(lcmd* l);
void print_lvar_d(lvar_d* list);
void print_lvar_print(lvar_print* l);


void printExpr(Expr* expr) {
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    printf("%d",expr->attr.value);
  }
  else if (expr->kind == E_OPERATION) {
    printExpr(expr->attr.op.left);
    switch (expr->attr.op.operator) {
      case PLUS:
      printf("+");
      break;
      case MINUS:
      printf("-");
      break;
      case MULT:
      printf("*");
      break;
      case DIV:
      printf("/");
      break;
      case MOD:
      printf("%c",37);
      break;
      case PESQ:
      printf("(");
      printExpr(expr->attr.op.left);
      printf(");\n");
      return;
      default: yyerror("Unknown operator!");
    }

    printExpr(expr->attr.op.right);
  }
  return;
}

void printBool(BoolExpr* b){
  if (b == 0) {
    yyerror("Null expression!!");
  }

  else if (b->kind == VALOR) {

    printf("%d",b->attr.value);
  }
  else if (b->kind == COMPARA) {
    printExpr(b->attr.comp.left);
    switch (b->attr.comp.operator) {
      case EQUAL:
      printf("==");
      break;
      case DIFF:
      printf("!=");
      break;
      case GREATER:
      printf(">");
      break;
      case LESS:
      printf("<");
      break;
      case GREATEREQ:
      printf(">=");
      break;
      case LESSEQ:
      printf("<=");
      break;
      default: yyerror("Unknown operator!");
    }

    printExpr(b->attr.comp.right);

  }
  return;
}

void print_atr(atributo* a){
  printf("%s=", a->var);
  printExpr(a->value);
  printf(";");

  return;
}

void printCmd(Cmd* c){
  switch(c->kind){
    case E_ATTR:
    print_atr(c->attr.a);
    break;
    case E_DECL:
    print_decl(c->attr.d);
    break;
    case E_IF:
    print_se(c->attr.se);
    break;
    case E_PRINT:
    print_print(c->attr.p);
    break;
    case E_SCAN:
    print_scan(c->attr.s);
    break;
    case E_CICLO:
    print_ciclo(c->attr.c);
    break;
    default: yyerror("Unknown command!\n");
  }
  printf("\n");
  return;
}

void print_decl(decl* dl){
  if (dl == 0)
  {
    yyerror("Null Decleration!!\n");
    return;
  }
  printf("int ");
  print_lvar_d(dl->list);

  return;
}

void print_se(se* se){
  if(se->ncomandos == NULL && se->comandos->next == NULL){
    printf("if(");
    printBool(se->cond);
    printf(") ");
    printCmd(se->comandos->comando);

  }
  else{
    printf("if(");
    printBool(se->cond);
    printf(") ");
    printf("{\n");
    print_lcmd(se->comandos);
    printf("}\n");
  }
  if(se->ncomandos == NULL)
  return;
  if(se->ncomandos->next == NULL){
    printf("else");
    printCmd(se->ncomandos->comando);
  }
  else{

    printf("else");

    printf("{\n");
    print_lcmd(se->ncomandos);
    printf("}\n");
  }
  return;
}

void print_print(print* p){
  printf("printf(");
  printf("%s",p->str);
  print_lvar_print(p->list);
  printf(");\n");
  return;
}
void print_scan(scan* s){
  printf("scanf(");
  printf("%s",s->str);
  print_lvar_print(s->list);
  printf(");\n");
  return;
}

void print_lcmd(lcmd* l){
  while(l!=NULL){
    printCmd(l->comando);
    l=l->next;
  }
  return;
}

void print_lvar_d(lvar_d* list){
  while(list!=NULL){
    if(list->kind==VARI){
      printf("%s ", list->attr.var);
    //  if(list->attr.var==NULL)
    //  printf(";");
      //else
      //printf(",");
    }
    else if(list->kind==ATRI){
      printf("%s=",list->attr.atri->var);
      printExpr(list->attr.atri->value);

    }
    list=list->next;
  }
  return;
}

void print_lvar_print(lvar_print* l){
  while(l!=NULL){
    printf("%s,",l->var);
    l=l->next;
  }
  return;
}

void print_ciclo(ciclo* c){
  printf("while(");
  printBool(c->cond);
  printf("){\n");
  if(c->list->next==NULL)
  printCmd(c->list->comando);
  else{
    print_lcmd(c->list);
  }
  printf("}\n");
  return;
}

int main(int argc, char** argv) {
  --argc;++argv;
  if(argc!=0) {
    yyin=fopen(*argv,"r");
    if(!yyin){
      printf("'%s':could not open file\n", *argv);
      return 1;
    }
  }
  if(yyparse()==0){
    printf("int main(){\n");
    print_lcmd(root);
    printf("return 0;\n}\n");
  }


  return 0;
}
