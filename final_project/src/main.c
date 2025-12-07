#include <stdio.h>
#include "ast.h"
#include "interp.h"

int yyparse(void);
extern Node *root;

int main(void) {
    if (yyparse() == 0) {
        printf("=== AST ===\n");
        print_ast(root, 0);
        
        printf("\n=== Execution ===\n");
        interpret(root);
        
        free_ast(root);
        return 0;
    }
    return 1;
}
