#include "ast.h"
#include <string.h>

static char *dupstr(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *p = (char*)malloc(len + 1);
    memcpy(p, s, len + 1);
    return p;
}

Node *node(NodeKind kind, int line, const char *op, int nchild, ...) {
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->kind = kind;
    n->op = op ? dupstr(op) : NULL;
    n->nchild = nchild;
    n->line = line;
    n->is_mutable = 0;
    
    if (nchild > 0) {
        n->child = (Node**)calloc(nchild, sizeof(Node*));
        va_list ap;
        va_start(ap, nchild);
        for (int i = 0; i < nchild; i++) {
            n->child[i] = va_arg(ap, Node*);
        }
        va_end(ap);
    }
    return n;
}

Node *nodev(NodeKind kind, int line, const char *op, int nchild, Node **arr) {
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->kind = kind;
    n->op = op ? dupstr(op) : NULL;
    n->nchild = nchild;
    n->line = line;
    n->is_mutable = 0;
    
    if (nchild > 0) {
        n->child = (Node**)calloc(nchild, sizeof(Node*));
        for (int i = 0; i < nchild; i++) {
            n->child[i] = arr[i];
        }
    }
    return n;
}

static const char* kind_str(NodeKind k) {
    switch (k) {
        case NK_PROGRAM: return "PROGRAM";
        case NK_VAL_DECL: return "VAL_DECL";
        case NK_VAR_DECL: return "VAR_DECL";
        case NK_FUNC_DEF: return "FUNC_DEF";
        case NK_PARAM: return "PARAM";
        case NK_PARAM_LIST: return "PARAM_LIST";
        case NK_BLOCK: return "BLOCK";
        case NK_STMT_LIST: return "STMT_LIST";
        case NK_ASSIGN: return "ASSIGN";
        case NK_IF: return "IF";
        case NK_WHEN: return "WHEN";
        case NK_WHEN_BRANCH: return "WHEN_BRANCH";
        case NK_WHILE: return "WHILE";
        case NK_FOR: return "FOR";
        case NK_RETURN: return "RETURN";
        case NK_EXPR_STMT: return "EXPR_STMT";
        case NK_PRINT: return "PRINTLN";
        case NK_BINOP: return "BINOP";
        case NK_UNOP: return "UNOP";
        case NK_CALL: return "CALL";
        case NK_ARG_LIST: return "ARG_LIST";
        case NK_IF_EXPR: return "IF_EXPR";
        case NK_RANGE: return "RANGE";
        case NK_INT: return "INT";
        case NK_STRING: return "STRING";
        case NK_BOOL: return "BOOL";
        case NK_VAR: return "VAR";
        case NK_TYPE: return "TYPE";
        default: return "UNKNOWN";
    }
}

void print_ast(Node *n, int indent) {
    if (!n) return;
    
    for (int i = 0; i < indent; i++)
        putchar(' ');
    
    printf("(%s", kind_str(n->kind));
    if (n->op)
        printf(" : %s", n->op);
    if (n->kind == NK_VAR_DECL || n->kind == NK_VAL_DECL)
        printf(" [%s]", n->is_mutable ? "mutable" : "immutable");
    printf(") @%d\n", n->line);
    
    for (int i = 0; i < n->nchild; i++)
        print_ast(n->child[i], indent + 2);
}

void free_ast(Node *n) {
    if (!n) return;
    
    for (int i = 0; i < n->nchild; i++)
        free_ast(n->child[i]);
    
    free(n->child);
    free((char*)n->op);
    free(n);
}
