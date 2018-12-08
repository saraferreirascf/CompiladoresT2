typedef enum {LDC,ADI,SBI,MPI,DVI,MODP,DIF,LES,LEQ,EQU,LOD,GEQ,STO,RDI,FJP,GRT,WRI,UJP,LABEL,NEQ, LDA} IKind;

typedef struct {
  IKind kind;
  union { //só tem um dos campos ativos, é preciso mudar as funções no stack.c para incluir o var, var preciso p scan
    char* var;
    int arg;
  } args;
} Instr;

typedef struct _li {
  Instr* head;
  struct _li* tail;

} lista_Instr;


Instr* mkInstr(IKind kind, int n);
Instr* head(lista_Instr* l1);
lista_Instr* tail(lista_Instr* l1);
lista_Instr* append(lista_Instr* l1, lista_Instr* l2);
lista_Instr* mkList(Instr* code,  lista_Instr* l1);
