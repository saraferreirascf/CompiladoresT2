#include <stdlib.h> // for malloc
#include <stdio.h>
#include "stack.h"
#include "ast.h"
#include "parser.h"

int label; //Variavel global por causa dos ciclos

lista_Instr* compile_lcmd(lcmd* l);
lista_Instr* compileBool(BoolExpr* expr);
lista_Instr* compileCmd(Cmd* c);
lista_Instr* compileExpr(Expr* expr);
lista_Instr* compile_attr(atributo* a);
lista_Instr* compile_ciclo(ciclo* c);
lista_Instr* compile_decl(decl* dl);
lista_Instr* compile_print(print* p);
lista_Instr* compile_scan(scan* s);
lista_Instr* compile_se(se* se);

Instr* mkInstr(IKind kind, int n){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind=kind;
  node->args.arg=n;
  return node;
}

Instr* _mkInstr(IKind kind, char* c){
  Instr* node = (Instr*) malloc(sizeof(Instr));
  node->kind=kind;
  node->args.var=c;
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
  return mkList(head(l1),append(tail(l1),l2));
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
    case MODP:
    printf("MODP");
    break;
    case EQU:
    printf("EQU");
    break;
    case DIF:
    printf("DIF");
    break;
    case LES:
    printf("LES");
    break;
    case LEQ:
    printf("LEQ");
    break;
    case GEQ:
    printf("GEQ");
    break;
    case GRT:
    printf("GRT");
    break;
    case STO:
    printf("STO");
    break;
    case FJP:
    printf("FJP");
    break;
    case UJP:
    printf("UJP");
    break;
    case WRI:
    printf("WRI");
    break;
    case RDI:
    printf("RDI");
    break;
    case LDA:
    printf("LDA");
    break;
    case LOD:
    printf("LOD");
    break;

    default: printf("Não existe\n");
  }
  printf(" %d\n", inst->args.arg);

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
      case MOD:
      l1 = append(l1, mkList(mkInstr(MODP, 0), NULL));
      break;
    }
  }
  return l1;
}

lista_Instr* compileBool(BoolExpr* b){
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  switch(b->kind){
    case E_INTEGER:
    l1 = mkList(mkInstr(LDC,b->attr.value), NULL);
    break;
    case E_OPERATION:
    l1 = compileExpr(b->attr.comp.left);
    l1 = append(l1, compileExpr(b->attr.comp.right));
    switch(b->attr.comp.operator){
      case EQUAL:
      l1 = append(l1, mkList(mkInstr(EQU, 0), NULL));
      break;
      case DIFF:
      l1 = append(l1, mkList(mkInstr(DIF, 0), NULL));
      break;
      case LESS:
      l1 = append(l1, mkList(mkInstr(LES, 0), NULL));
      break;
      case LESSEQ:
      l1 = append(l1, mkList(mkInstr(LEQ, 0), NULL));
      break;
      case GREATER:
      l1 = append(l1, mkList(mkInstr(GRT, 0), NULL));
      break;
      case GREATEREQ:
      l1 = append(l1, mkList(mkInstr(GEQ, 0), NULL));
      break;
    }
  }
  return l1;
}

lista_Instr* compile_attr(atributo* a) {
  lista_Instr* l1 = NULL;
  compileExpr(a->value);
  l1 = append(l1, mkList(mkInstr(STO, 0), NULL));
  return l1;
}

lista_Instr* compile_se(se* se) {
  int label_temp = label;
  lista_Instr* l1 = NULL;
  compileBool(se->cond);
  l1 = append(l1, mkList(mkInstr(FJP, 1), NULL));
  compile_lcmd(se->comandos);
  l1 = append(l1, mkList(mkInstr(UJP, 2), NULL));
  label_temp = 1;
  compile_lcmd(se->ncomandos);
  label_temp+= 1;
  label+= 2;

  return l1;
}

lista_Instr* compile_lcmd(lcmd* l){
  //criar uma lista nova e fazer append cm a lista q da no compile cmd e retornar
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  l1 = compileCmd(l->comando);

  while(l!=NULL){
    l1 = append(l1, compileCmd(l->comando));
    l=l->next;
  }
  return l1;
}

lista_Instr* compile_ciclo(ciclo* c) {
  int label_temp = label;
  lista_Instr* l1 = NULL;
  label_temp = 1;
  compileBool(c->cond);
  l1 = append(l1, mkList(mkInstr(FJP, 2), NULL));
  compile_lcmd(c->list);
  l1 = append(l1, mkList(mkInstr(UJP, 1), NULL));
  label_temp+= 1;
  label+= 2;
}

lista_Instr* compile_print(print* p) {
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  lista_Instr* l2 = (lista_Instr*) malloc(sizeof(lista_Instr));
  l1 = append(l1, mkList(_mkInstr(LOD, p->str), NULL));
  l2 = append(l1, mkList(mkInstr(WRI, 0), NULL));
  l1 = append(l1,l2);

  return l1;
}

lista_Instr* compile_scan(scan* s) {
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  lista_Instr* l2 = (lista_Instr*) malloc(sizeof(lista_Instr));
  l1 = append(l1, mkList(_mkInstr(LDA, s->str), NULL));
  l2 = append(l2, mkList(mkInstr(RDI, 0), NULL));
  l1 = append(l1,l2);
  return l1;
}

/*lista_Instr* compile_decl(decl* dl) {
  if (dl == 0) {
    yyerror("Null Decleration!!\n");
    return ;
  }
  printf("int ");
  print_lvar_d(dl->list);

  return;
}*/

lista_Instr* compileCmd(Cmd* c){
  lista_Instr* l1 = (lista_Instr*) malloc(sizeof(lista_Instr));
  switch(c->kind){
    case E_ATTR:
    l1 = compile_attr(c->attr.a);
    break;
    /*case E_DECL:
    l1 = compile_decl(c->attr.d);
    break;*/
    case E_IF:
    l1 = compile_se(c->attr.se);
    break;
    case E_PRINT:
    l1 = compile_print(c->attr.p);
    break;
    case E_SCAN:
    l1 = compile_scan(c->attr.s);
    break;
    case E_CICLO:
    l1 = compile_ciclo(c->attr.c);
    break;
    default: yyerror("Unknown command!\n");
  }
  printf("\n");
  return l1;
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
    lista_Instr* l=compile_lcmd(root);
    printListIntrs(l); //numa proxima fase este print vai gerar mips
    //FAzer print do syscall

  }


  return 0;
}
