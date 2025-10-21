#ifndef AST_H
#define AST_H

/* 파싱 위치 정보: Bison YYLTYPE에 의존하지 않도록 별도 구조체 사용 */
typedef struct {
    int first_line, first_column;
    int last_line,  last_column;
} Loc;

/* 노드 종류: 토큰(enum yytokentype)과 충돌 방지 위해 NK_* 사용 */
typedef enum {
    NK_NUM, NK_ADD, NK_SUB, NK_MUL, NK_DIV, NK_UPLUS, NK_UMINUS
} NodeKind;

typedef struct Node {
    NodeKind kind;
    struct Node *lhs, *rhs;
    double value;   /* NK_NUM일 때만 사용 */
    Loc loc;        /* 이 노드(연산자/리터럴)의 소스 위치 */
} Node;

/* 생성기 */
struct Node* new_num(double v, Loc loc);
struct Node* new_un(NodeKind k, struct Node* x, Loc loc);
struct Node* new_bin(NodeKind k, struct Node* a, struct Node* b, Loc loc);

/* 유틸 */
void free_ast(struct Node* n);

/* 정적 검사(확정 0 나눗셈만) */
void check_div_by_zero(struct Node* n);

/* 런타임 평가(0 나눗셈 가드 포함) */
double eval(struct Node* n);

#endif /* AST_H */
