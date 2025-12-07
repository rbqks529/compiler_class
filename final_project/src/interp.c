#include "interp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 값 타입 */
typedef enum {
    VAL_INT,
    VAL_STRING,
    VAL_BOOL,
    VAL_NONE
} ValueType;

/* 값 구조체 */
typedef struct {
    ValueType type;
    union {
        int i;
        char *s;
        bool b;
    } data;
} Value;

/* 심볼 테이블 엔트리 */
typedef struct Symbol {
    char *name;
    Value value;
    bool is_mutable;
    struct Symbol *next;
} Symbol;

/* 함수 정의 */
typedef struct Function {
    char *name;
    Node *params;
    Node *body;
    struct Function *next;
} Function;

static Symbol *symbols = NULL;
static Function *functions = NULL;
static bool has_return = false;
static Value return_value;

/* 전방 선언 */
static Value eval_expr(Node *n);
static void exec_stmt(Node *n);

/* 값 생성 함수 */
static Value make_int(int i) {
    Value v;
    v.type = VAL_INT;
    v.data.i = i;
    return v;
}

static Value make_string(const char *s) {
    Value v;
    v.type = VAL_STRING;
    v.data.s = strdup(s);
    return v;
}

static Value make_bool(bool b) {
    Value v;
    v.type = VAL_BOOL;
    v.data.b = b;
    return v;
}

static Value make_none(void) {
    Value v;
    v.type = VAL_NONE;
    return v;
}

/* 심볼 테이블 함수 */
static Symbol *find_symbol(const char *name) {
    for (Symbol *s = symbols; s; s = s->next) {
        if (strcmp(s->name, name) == 0)
            return s;
    }
    return NULL;
}

static void add_symbol(const char *name, Value val, bool is_mutable) {
    Symbol *s = (Symbol*)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->value = val;
    s->is_mutable = is_mutable;
    s->next = symbols;
    symbols = s;
}

static void update_symbol(const char *name, Value val) {
    Symbol *s = find_symbol(name);
    if (!s) {
        fprintf(stderr, "Runtime error: undefined variable '%s'\n", name);
        exit(1);
    }
    if (!s->is_mutable) {
        fprintf(stderr, "Runtime error: cannot reassign val '%s'\n", name);
        exit(1);
    }
    s->value = val;
}

/* 함수 테이블 */
static void add_function(const char *name, Node *params, Node *body) {
    Function *f = (Function*)malloc(sizeof(Function));
    f->name = strdup(name);
    f->params = params;
    f->body = body;
    f->next = functions;
    functions = f;
}

static Function *find_function(const char *name) {
    for (Function *f = functions; f; f = f->next) {
        if (strcmp(f->name, name) == 0)
            return f;
    }
    return NULL;
}

/* 표현식 평가 */
static Value eval_expr(Node *n) {
    if (!n) return make_none();
    
    switch (n->kind) {
        case NK_INT:
            return make_int(atoi(n->op));
        
        case NK_STRING: {
            char *s = strdup(n->op + 1);
            s[strlen(s) - 1] = '\0';
            Value v = make_string(s);
            free(s);
            return v;
        }
        
        case NK_BOOL:
            return make_bool(strcmp(n->op, "true") == 0);
        
        case NK_VAR: {
            Symbol *s = find_symbol(n->op);
            if (!s) {
                fprintf(stderr, "Runtime error: undefined variable '%s'\n", n->op);
                exit(1);
            }
            return s->value;
        }
        
        case NK_BINOP: {
            Value left = eval_expr(n->child[0]);
            Value right = eval_expr(n->child[1]);
            
            if (strcmp(n->op, "+") == 0) {
                if (left.type == VAL_INT && right.type == VAL_INT)
                    return make_int(left.data.i + right.data.i);
            } else if (strcmp(n->op, "-") == 0) {
                return make_int(left.data.i - right.data.i);
            } else if (strcmp(n->op, "*") == 0) {
                return make_int(left.data.i * right.data.i);
            } else if (strcmp(n->op, "/") == 0) {
                if (right.data.i == 0) {
                    fprintf(stderr, "Runtime error: division by zero\n");
                    exit(1);
                }
                return make_int(left.data.i / right.data.i);
            } else if (strcmp(n->op, "%") == 0) {
                return make_int(left.data.i % right.data.i);
            } else if (strcmp(n->op, "<") == 0) {
                return make_bool(left.data.i < right.data.i);
            } else if (strcmp(n->op, ">") == 0) {
                return make_bool(left.data.i > right.data.i);
            } else if (strcmp(n->op, "<=") == 0) {
                return make_bool(left.data.i <= right.data.i);
            } else if (strcmp(n->op, ">=") == 0) {
                return make_bool(left.data.i >= right.data.i);
            } else if (strcmp(n->op, "==") == 0) {
                if (left.type == VAL_INT && right.type == VAL_INT)
                    return make_bool(left.data.i == right.data.i);
                else if (left.type == VAL_BOOL && right.type == VAL_BOOL)
                    return make_bool(left.data.b == right.data.b);
            } else if (strcmp(n->op, "!=") == 0) {
                if (left.type == VAL_INT && right.type == VAL_INT)
                    return make_bool(left.data.i != right.data.i);
                else if (left.type == VAL_BOOL && right.type == VAL_BOOL)
                    return make_bool(left.data.b != right.data.b);
            } else if (strcmp(n->op, "&&") == 0) {
                return make_bool(left.data.b && right.data.b);
            } else if (strcmp(n->op, "||") == 0) {
                return make_bool(left.data.b || right.data.b);
            }
            break;
        }
        
        case NK_UNOP: {
            Value val = eval_expr(n->child[0]);
            if (strcmp(n->op, "!") == 0)
                return make_bool(!val.data.b);
            else if (strcmp(n->op, "-") == 0)
                return make_int(-val.data.i);
            break;
        }
        
        case NK_IF_EXPR: {
            Value cond = eval_expr(n->child[0]);
            if (cond.data.b)
                return eval_expr(n->child[1]);
            else
                return eval_expr(n->child[2]);
        }
        
        case NK_CALL: {
            Function *f = find_function(n->op);
            if (!f) {
                fprintf(stderr, "Runtime error: undefined function '%s'\n", n->op);
                exit(1);
            }
            
            Symbol *old_symbols = symbols;
            
            Value *arg_vals = NULL;
            int num_args = 0;
            if (f->params && f->params->nchild > 0) {
                Node *args = n->child[0];
                num_args = f->params->nchild;
                arg_vals = malloc(sizeof(Value) * num_args);
                for (int i = 0; i < num_args; i++) {
                    arg_vals[i] = eval_expr(args->child[i]);
                }
            }
            
            symbols = NULL;
            
            for (int i = 0; i < num_args; i++) {
                add_symbol(f->params->child[i]->op, arg_vals[i], false);
            }
            if (arg_vals) free(arg_vals);
            
            exec_stmt(f->body);
            
            Value result = has_return ? return_value : make_none();
            has_return = false;
            
            symbols = old_symbols;
            return result;
        }
        
        default:
            break;
    }
    
    return make_none();
}

/* 문장 실행 */
static void exec_stmt(Node *n) {
    if (!n || has_return) return;
    
    switch (n->kind) {
        case NK_PROGRAM:
        case NK_STMT_LIST:
            for (int i = 0; i < n->nchild; i++)
                exec_stmt(n->child[i]);
            break;
        
        case NK_VAL_DECL:
        case NK_VAR_DECL: {
            Value val = eval_expr(n->child[n->nchild - 1]);
            add_symbol(n->op, val, n->is_mutable);
            break;
        }
        
        case NK_ASSIGN: {
            Value val = eval_expr(n->child[0]);
            update_symbol(n->op, val);
            break;
        }
        
        case NK_FUNC_DEF:
            add_function(n->op, n->child[0], n->child[n->nchild - 1]);
            break;
        
        case NK_BLOCK:
            exec_stmt(n->child[0]);
            break;
        
        case NK_IF: {
            Value cond = eval_expr(n->child[0]);
            if (cond.data.b)
                exec_stmt(n->child[1]);
            else if (n->nchild == 3)
                exec_stmt(n->child[2]);
            break;
        }
        
        case NK_WHILE: {
            while (true) {
                Value cond = eval_expr(n->child[0]);
                if (!cond.data.b) break;
                exec_stmt(n->child[1]);
                if (has_return) break;
            }
            break;
        }
        
        case NK_FOR: {
            Node *range = n->child[0];
            Value start = eval_expr(range->child[0]);
            Value end = eval_expr(range->child[1]);
            
            for (int i = start.data.i; i <= end.data.i; i++) {
                Symbol *s = find_symbol(n->op);
                if (s) {
                    s->value = make_int(i);
                } else {
                    add_symbol(n->op, make_int(i), false);
                }
                exec_stmt(n->child[1]);
                if (has_return) break;
            }
            break;
        }
        
        case NK_WHEN: {
            Value val = eval_expr(n->child[0]);
            Node *branches = n->child[1];
            
            for (int i = 0; i < branches->nchild; i++) {
                Node *branch = branches->child[i];
                if (branch->op && strcmp(branch->op, "else") == 0) {
                    return_value = eval_expr(branch->child[0]);
                    break;
                } else {
                    Value cond = eval_expr(branch->child[0]);
                    if (val.type == VAL_INT && cond.type == VAL_INT &&
                        val.data.i == cond.data.i) {
                        return_value = eval_expr(branch->child[1]);
                        break;
                    }
                }
            }
            break;
        }
        
        case NK_RETURN:
            if (n->nchild > 0)
                return_value = eval_expr(n->child[0]);
            else
                return_value = make_none();
            has_return = true;
            break;
        
        case NK_PRINT: {
            Value val = eval_expr(n->child[0]);
            if (val.type == VAL_INT)
                printf("%d\n", val.data.i);
            else if (val.type == VAL_STRING)
                printf("%s\n", val.data.s);
            else if (val.type == VAL_BOOL)
                printf("%s\n", val.data.b ? "true" : "false");
            break;
        }
        
        case NK_EXPR_STMT:
            eval_expr(n->child[0]);
            break;
        
        default:
            break;
    }
}

void interpret(Node *root) {
    exec_stmt(root);
}
