#include <stdlib.h>
#include "ast.h"

struct Node* new_num(double v, Loc loc){
    struct Node* n = (struct Node*)calloc(1, sizeof(*n));
    n->kind = NK_NUM; n->value = v; n->loc = loc;
    return n;
}
struct Node* new_un(NodeKind k, struct Node* x, Loc loc){
    struct Node* n = (struct Node*)calloc(1, sizeof(*n));
    n->kind = k; n->lhs = x; n->loc = loc;
    return n;
}
struct Node* new_bin(NodeKind k, struct Node* a, struct Node* b, Loc loc){
    struct Node* n = (struct Node*)calloc(1, sizeof(*n));
    n->kind = k; n->lhs = a; n->rhs = b; n->loc = loc;
    return n;
}

void free_ast(struct Node* n){
    if(!n) return;
    free_ast(n->lhs);
    free_ast(n->rhs);
    free(n);
}
