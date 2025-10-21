%{
#include <stdio.h>
#include <math.h>

/* 액션에서 Loc 리터럴을 만들기 위한 매크로(YYLTYPE에 의존 X) */
#define AS_LOC(y) ((Loc){ (y).first_line, (y).first_column, (y).last_line, (y).last_column })

int yylex(void);
static void yyerror(const char *s);
%}

/* Node*, Loc 타입이 액션/유니온에 필요하므로 requires 섹션에서 ast.h 포함 */
%code requires {
  #include "ast.h"
}

%define parse.error detailed
%locations

%union {
  double num;
  struct Node* node;
}

/* 토큰/우선순위 */
%token <num> NUMBER
%left '+' '-'
%left '*' '/'
%precedence UPLUS UMINUS

/* 비단말 타입 */
%type <node> expr

%%
input
  : %empty
  | input line
  ;

line
  : expr ';'
    {
      check_div_by_zero($1);
      double v = eval($1);
      printf("= %.10g\n", v);
      fflush(stdout);
      free_ast($1);
    }
  | error ';' { yyerror("syntax error, skipped to ';'"); yyerrok; }
  ;

expr
  : expr '+' expr   { $$ = new_bin(NK_ADD, $1, $3, AS_LOC(@2)); }
  | expr '-' expr   { $$ = new_bin(NK_SUB, $1, $3, AS_LOC(@2)); }
  | expr '*' expr   { $$ = new_bin(NK_MUL, $1, $3, AS_LOC(@2)); }
  | expr '/' expr   { $$ = new_bin(NK_DIV, $1, $3, AS_LOC(@2)); }
  | '(' expr ')'    { $$ = $2; }
  | '+' expr %prec UPLUS   { $$ = new_un(NK_UPLUS,  $2, AS_LOC(@1)); }
  | '-' expr %prec UMINUS  { $$ = new_un(NK_UMINUS, $2, AS_LOC(@1)); }
  | NUMBER          { $$ = new_num($1, AS_LOC(@1)); }
  ;
%%

static void yyerror(const char *s) {
  fprintf(stderr, "[syn] %s at %d:%d\n",
          s, yylloc.first_line, yylloc.first_column);
}
