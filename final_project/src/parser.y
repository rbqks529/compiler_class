%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern int yylineno;
void yyerror(const char *s);

Node *root = NULL;
%}

%code requires {
  #include "ast.h"
}

%define api.value.type {Node*}
%define parse.error verbose

/* 토큰 선언 */
%token IDENT INTEGER STRING
%token FUN VAL VAR IF ELSE WHEN WHILE FOR IN RETURN PRINTLN
%token TYPE_INT TYPE_STRING TYPE_BOOL
%token TRUE FALSE
%token EQ NE LE GE AND OR DOTDOT ARROW

/* 연산자 우선순위 */
%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!' UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start program

%%

program
  : stmt_list
    { $$ = node(NK_PROGRAM, yylineno, NULL, 1, $1); root = $$; }
  ;

stmt_list
  : /* empty */
    { $$ = node(NK_STMT_LIST, yylineno, NULL, 0); }
  | stmt_list statement
    {
      Node **arr = (Node**)calloc($1->nchild + 1, sizeof(Node*));
      for (int i = 0; i < $1->nchild; i++) arr[i] = $1->child[i];
      arr[$1->nchild] = $2;
      $$ = nodev(NK_STMT_LIST, yylineno, NULL, $1->nchild + 1, arr);
      free($1->child); $1->child = NULL; $1->nchild = 0; free($1);
    }
  ;

statement
  : val_decl
  | var_decl
  | func_def
  | assignment ';'
  | if_stmt
  | when_stmt
  | while_stmt
  | for_stmt
  | return_stmt ';'
  | print_stmt ';'
  | expr_stmt ';'
  | block
  ;

val_decl
  : VAL IDENT '=' expr ';'
    { $$ = node(NK_VAL_DECL, yylineno, $2->op, 1, $4); free_ast($2); }
  | VAL IDENT ':' type '=' expr ';'
    { $$ = node(NK_VAL_DECL, yylineno, $2->op, 2, $4, $6); free_ast($2); }
  ;

var_decl
  : VAR IDENT '=' expr ';'
    { $$ = node(NK_VAR_DECL, yylineno, $2->op, 1, $4); $$->is_mutable = 1; free_ast($2); }
  | VAR IDENT ':' type '=' expr ';'
    { $$ = node(NK_VAR_DECL, yylineno, $2->op, 2, $4, $6); $$->is_mutable = 1; free_ast($2); }
  ;

type
  : TYPE_INT
  | TYPE_STRING
  | TYPE_BOOL
  ;

func_def
  : FUN IDENT '(' param_list_opt ')' block
    { $$ = node(NK_FUNC_DEF, yylineno, $2->op, 2, $4, $6); free_ast($2); }
  | FUN IDENT '(' param_list_opt ')' ':' type block
    { $$ = node(NK_FUNC_DEF, yylineno, $2->op, 3, $4, $7, $8); free_ast($2); }
  ;

param_list_opt
  : /* empty */
    { $$ = node(NK_PARAM_LIST, yylineno, NULL, 0); }
  | param_list
  ;

param_list
  : param
    { $$ = node(NK_PARAM_LIST, yylineno, NULL, 1, $1); }
  | param_list ',' param
    {
      Node **arr = (Node**)calloc($1->nchild + 1, sizeof(Node*));
      for (int i = 0; i < $1->nchild; i++) arr[i] = $1->child[i];
      arr[$1->nchild] = $3;
      $$ = nodev(NK_PARAM_LIST, yylineno, NULL, $1->nchild + 1, arr);
      free($1->child); $1->child = NULL; $1->nchild = 0; free($1);
    }
  ;

param
  : IDENT ':' type
    { $$ = node(NK_PARAM, yylineno, $1->op, 1, $3); free_ast($1); }
  ;

block
  : '{' stmt_list '}'
    { $$ = node(NK_BLOCK, yylineno, NULL, 1, $2); }
  ;

assignment
  : IDENT '=' expr
    { $$ = node(NK_ASSIGN, yylineno, $1->op, 1, $3); free_ast($1); }
  ;

if_stmt
  : IF '(' expr ')' block %prec LOWER_THAN_ELSE
    { $$ = node(NK_IF, yylineno, NULL, 2, $3, $5); }
  | IF '(' expr ')' block ELSE block
    { $$ = node(NK_IF, yylineno, "else", 3, $3, $5, $7); }
  | IF '(' expr ')' block ELSE if_stmt
    { $$ = node(NK_IF, yylineno, "else", 3, $3, $5, $7); }
  ;

when_stmt
  : WHEN '(' expr ')' '{' when_branches '}'
    { $$ = node(NK_WHEN, yylineno, NULL, 2, $3, $6); }
  ;

when_branches
  : when_branch
    { $$ = node(NK_STMT_LIST, yylineno, NULL, 1, $1); }
  | when_branches when_branch
    {
      Node **arr = (Node**)calloc($1->nchild + 1, sizeof(Node*));
      for (int i = 0; i < $1->nchild; i++) arr[i] = $1->child[i];
      arr[$1->nchild] = $2;
      $$ = nodev(NK_STMT_LIST, yylineno, NULL, $1->nchild + 1, arr);
      free($1->child); $1->child = NULL; $1->nchild = 0; free($1);
    }
  ;

when_branch
  : expr ARROW expr
    { $$ = node(NK_WHEN_BRANCH, yylineno, NULL, 2, $1, $3); }
  | ELSE ARROW expr
    { $$ = node(NK_WHEN_BRANCH, yylineno, "else", 1, $3); }
  ;

while_stmt
  : WHILE '(' expr ')' block
    { $$ = node(NK_WHILE, yylineno, NULL, 2, $3, $5); }
  ;

for_stmt
  : FOR '(' IDENT IN range ')' block
    { $$ = node(NK_FOR, yylineno, $3->op, 2, $5, $7); free_ast($3); }
  ;

range
  : expr DOTDOT expr
    { $$ = node(NK_RANGE, yylineno, NULL, 2, $1, $3); }
  ;

return_stmt
  : RETURN
    { $$ = node(NK_RETURN, yylineno, NULL, 0); }
  | RETURN expr
    { $$ = node(NK_RETURN, yylineno, NULL, 1, $2); }
  ;

print_stmt
  : PRINTLN '(' expr ')'
    { $$ = node(NK_PRINT, yylineno, NULL, 1, $3); }
  ;

expr_stmt
  : expr
    { $$ = node(NK_EXPR_STMT, yylineno, NULL, 1, $1); }
  ;

expr
  : logical_or
  ;

logical_or
  : logical_and
  | logical_or OR logical_and
    { $$ = node(NK_BINOP, yylineno, "||", 2, $1, $3); }
  ;

logical_and
  : equality
  | logical_and AND equality
    { $$ = node(NK_BINOP, yylineno, "&&", 2, $1, $3); }
  ;

equality
  : relational
  | equality EQ relational
    { $$ = node(NK_BINOP, yylineno, "==", 2, $1, $3); }
  | equality NE relational
    { $$ = node(NK_BINOP, yylineno, "!=", 2, $1, $3); }
  ;

relational
  : additive
  | relational '<' additive
    { $$ = node(NK_BINOP, yylineno, "<", 2, $1, $3); }
  | relational '>' additive
    { $$ = node(NK_BINOP, yylineno, ">", 2, $1, $3); }
  | relational LE additive
    { $$ = node(NK_BINOP, yylineno, "<=", 2, $1, $3); }
  | relational GE additive
    { $$ = node(NK_BINOP, yylineno, ">=", 2, $1, $3); }
  ;

additive
  : multiplicative
  | additive '+' multiplicative
    { $$ = node(NK_BINOP, yylineno, "+", 2, $1, $3); }
  | additive '-' multiplicative
    { $$ = node(NK_BINOP, yylineno, "-", 2, $1, $3); }
  ;

multiplicative
  : unary
  | multiplicative '*' unary
    { $$ = node(NK_BINOP, yylineno, "*", 2, $1, $3); }
  | multiplicative '/' unary
    { $$ = node(NK_BINOP, yylineno, "/", 2, $1, $3); }
  | multiplicative '%' unary
    { $$ = node(NK_BINOP, yylineno, "%", 2, $1, $3); }
  ;

unary
  : primary
  | '!' unary
    { $$ = node(NK_UNOP, yylineno, "!", 1, $2); }
  | '-' unary %prec UMINUS
    { $$ = node(NK_UNOP, yylineno, "-", 1, $2); }
  ;

primary
  : INTEGER
  | STRING
  | TRUE
  | FALSE
  | IDENT
  | func_call
  | if_expr
  | '(' expr ')'
    { $$ = $2; }
  ;

func_call
  : IDENT '(' arg_list_opt ')'
    { $$ = node(NK_CALL, yylineno, $1->op, 1, $3); free_ast($1); }
  ;

arg_list_opt
  : /* empty */
    { $$ = node(NK_ARG_LIST, yylineno, NULL, 0); }
  | arg_list
  ;

arg_list
  : expr
    { $$ = node(NK_ARG_LIST, yylineno, NULL, 1, $1); }
  | arg_list ',' expr
    {
      Node **arr = (Node**)calloc($1->nchild + 1, sizeof(Node*));
      for (int i = 0; i < $1->nchild; i++) arr[i] = $1->child[i];
      arr[$1->nchild] = $3;
      $$ = nodev(NK_ARG_LIST, yylineno, NULL, $1->nchild + 1, arr);
      free($1->child); $1->child = NULL; $1->nchild = 0; free($1);
    }
  ;

if_expr
  : IF '(' expr ')' expr ELSE expr
    { $$ = node(NK_IF_EXPR, yylineno, NULL, 3, $3, $5, $7); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
