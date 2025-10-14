#include <stdio.h>
#include <math.h>
#include "ast.h"

double eval(struct Node* n){
    switch (n->kind) {
    case NK_NUM:    return n->value;
    case NK_UPLUS:  return +eval(n->lhs);
    case NK_UMINUS: return -eval(n->lhs);
    case NK_ADD:    return eval(n->lhs) + eval(n->rhs);
    case NK_SUB:    return eval(n->lhs) - eval(n->rhs);
    case NK_MUL:    return eval(n->lhs) * eval(n->rhs);
    case NK_DIV: {
        double a = eval(n->lhs);
        double b = eval(n->rhs);
        if (fabs(b) < 1e-12) {
            fprintf(stderr, "[sem] division by zero at %d:%d (runtime)\n",
                    n->loc.first_line, n->loc.first_column);
            return NAN; /* 정책: NaN 반환 */
        }
        return a / b;
    }
    default:
        fprintf(stderr, "[bug] unknown node kind\n");
        return NAN;
    }
}
