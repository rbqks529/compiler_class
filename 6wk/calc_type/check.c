#include <math.h>
#include <stdio.h>
#include "ast.h"

static int const_eval(struct Node* n, double* out) {
    if (!n) return 0;
    switch (n->kind) {
    case NK_NUM:
        *out = n->value; return 1;
    case NK_UPLUS: {
        double v; if (!const_eval(n->lhs, &v)) return 0; *out = +v; return 1;
    }
    case NK_UMINUS: {
        double v; if (!const_eval(n->lhs, &v)) return 0; *out = -v; return 1;
    }
    case NK_ADD: case NK_SUB: case NK_MUL: case NK_DIV: {
        double a, b;
        if (!const_eval(n->lhs, &a) || !const_eval(n->rhs, &b)) return 0;
        switch (n->kind) {
        case NK_ADD: *out = a + b; return 1;
        case NK_SUB: *out = a - b; return 1;
        case NK_MUL: *out = a * b; return 1;
        case NK_DIV:
            if (fabs(b) < 1e-12) return 0;   /* 분모 0이면 “정의불가” → 상수 아님 처리 */
            *out = a / b; return 1;
        default: return 0;
        }
    }
    default:
        return 0;
    }
}

void check_div_by_zero(struct Node* n) {
    if (!n) return;
    check_div_by_zero(n->lhs);
    check_div_by_zero(n->rhs);

    if (n->kind == NK_DIV) {
        double denom;
        if (const_eval(n->rhs, &denom) && fabs(denom) < 1e-12) {
            fprintf(stderr, "[sem] division by zero at %d:%d\n",
                    n->loc.first_line, n->loc.first_column);
        }
    }
}
