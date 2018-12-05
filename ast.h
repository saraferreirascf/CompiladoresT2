
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
      struct _BoolExpr* left;
      struct _BoolExpr* right;
    } comp; // for binary expressions
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;


// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(int v);
BoolExpr* ast_booleanop(int operator,BoolExpr* left, BoolExpr* right);

#endif
