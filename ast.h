
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr{
  enum {
    VALOR,
    COMPARA
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } comp; // for binary expressions
  } attr;
};

struct _var {
  char* letra;
} ;

struct _Cmd{
  enum {
    E_IF, //expr e uma lista de comando
    E_CICLO,
    E_ATTR,//1 var
    E_SCAN,
    E_PRINT,
    E_DECL
  } kind;
  union {
    struct atributo*  a;
    struct decl* d;
    struct se*  se;
    struct print*  p;
    struct scan* s;
    struct ciclo* c;
  } attr;
};

struct atributo{
  char* var;
  struct _Expr* value;
}; // para atribuições
struct ciclo{
  struct _BoolExpr* cond;
  struct _lcmd* list;
} ; //para o while
struct se {
  struct _BoolExpr* cond;
  struct _lcmd* comandos;
  struct _lcmd* ncomandos;
} ; //if
struct scan{
  char* str;
  int valor;
  //struct _lvar_print* list;
};
struct print{
  union{
    char* str;
    int num;
  } cenas;
  //struct _lvar_print* list;
} ;
struct decl{
  char* var;
} ;
typedef struct atributo atributo;
typedef struct ciclo ciclo;
typedef struct se se;
typedef struct scan scan;
typedef struct print print;
typedef struct decl decl;


struct _lcmd {
  struct _Cmd* comando;
  struct _lcmd* next;
} ;


typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Cmd Cmd;
typedef struct _var var;
typedef struct _lcmd lcmd;



// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(int v);
BoolExpr* ast_booleanop( int operator,Expr* left, Expr* right);

//comandos para as operações
Cmd* ast_c_atrib(atributo* a);
Cmd* ast_c_decl(decl* d);
Cmd* ast_c_se(se* se);
Cmd* ast_c_print(print* p);
Cmd* ast_c_scan(scan* s);
Cmd* ast_c_ciclo(ciclo* c);

//operações
atributo* ast_atrib(char* var, Expr* value);
decl* ast_decl(char* var);
se* ast_se_s(BoolExpr* cond, Cmd* comandos);
se* ast_se_bs(BoolExpr* cond, lcmd* comandos, Cmd* ncomandos);
se* ast_se_bb(BoolExpr* cond, lcmd* comandos, lcmd* ncomandos);
print* ast_print(char* str);
scan* ast_scan(int valor,char* str);
print* ast_printi(int num);

ciclo* ast_ciclo_s(BoolExpr* cond, Cmd* comando);
ciclo* ast_ciclo_b(BoolExpr* cond, lcmd* list);

lcmd* lista_comandos(Cmd* comando, lcmd* next);

#endif
