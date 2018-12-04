typedef enum {LDC,ADI,SBI,MPI,DVI,LOD,STO,RDI,FJP,GRT,WRI,UJP,LABEL,EQU,NEQ,LDA} IKind;

typedef struct {
  IKind kind;
  int arg;
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
