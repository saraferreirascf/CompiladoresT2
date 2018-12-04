#include <stdlib.h> // for malloc
#include <stdio.h>
#include "stack.h"
#include "ast.h"
#include "parser.h"
Instr* mkInstr(IKind kind, int n){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind=kind;
  node->arg=n;

  return node;
}

lista_Instr* mkList(Instr* code,  lista_Instr* l1){
  lista_Instr* node = (lista_Instr*) malloc(sizeof(lista_Instr));
  node->head=code;
  node->tail=l1;

  return node;
}

Instr*  head(lista_Instr* l1){
  return l1->head;
}
lista_Instr* tail(lista_Instr* l1){
  return l1->tail;
}

lista_Instr* append(lista_Instr* l1, lista_Instr* l2){
  if(l1==NULL)
  return l2;
  else{
    return mkList(head(l1),append(tail(l1),l2));
  }
}

void printInstr(Instr* inst){
  switch(inst->kind){
    case LDC:
    printf("LDC");
    break;
    case ADI:
    printf("ADI");
    break;
    case SBI:
    printf("SBI");
    break;
    case MPI:
    printf("MPI");
    break;
    default: printf("Não existe\n");
  }

  printf("%d\n", inst->arg);

}

void printListIntrs(lista_Instr* l1){
  if(l1==NULL)
  return;
  else{
    printInstr(head(l1));
    printListIntrs(tail(l1));
  }
}

lista_Instr* compileExpr(Expr* e){
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));

  switch(e->kind){
    case E_INTEGER:
    l1 = mkList(mkInstr(LDC,e->attr.value), NULL);
    break;
    case E_OPERATION:
    l1 = compileExpr(e->attr.op.left);
    l1 = append(l1, compileExpr(e->attr.op.right));
    switch(e->attr.op.operator){
      case PLUS:
      l1 = append(l1, mkList(mkInstr(ADI, 0), NULL));
      break;
      case MINUS:
      l1 = append(l1, mkList(mkInstr(SBI, 0), NULL));
      break;
      case MULT:
      l1 = append(l1, mkList(mkInstr(MPI, 0), NULL));
      break;
      case DIV:
      l1 = append(l1, mkList(mkInstr(DVI, 0), NULL));
      break;
    }
  }

  return l1;
}

lista_Instr* compileBool(BoolExpr* b){
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  switch(e->kind){
    case E_INTEGER:
    l1 = mkList(mkInstr(LDC,e->attr.value), NULL);
    break;
    case E_OPERATION:
    l1 = compileBool(e->attr.op.left);
    l1 = append(l1, compileBool(e->attr.op.right));
    switch(e->attr.op.operator){
      case PLUS:
      l1 = append(l1, mkList(mkInstr(ADI, 0), NULL));
      break;
      case MINUS:
      l1 = append(l1, mkList(mkInstr(SBI, 0), NULL));
      break;
      case MULT:
      l1 = append(l1, mkList(mkInstr(MPI, 0), NULL));
      break;
      case DIV:
      l1 = append(l1, mkList(mkInstr(DVI, 0), NULL));
      break;
    }
  }

  return l1;
}
/*
lista_Instr* compileCmd(Cmd* c){

}
lista_Instr* compile(lcmd* l){

}*/

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
    lista_Instr* l=compileExpr(root);
    printListIntrs(l); //numa proxima fase este print vai gerar mips
  }


  return 0;
}
