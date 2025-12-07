#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * NodeKind - AST 노드 타입
 */
typedef enum {
    // 프로그램
    NK_PROGRAM,
    
    // 선언
    NK_VAL_DECL,        // val 선언
    NK_VAR_DECL,        // var 선언
    NK_FUNC_DEF,        // 함수 정의
    NK_PARAM,           // 파라미터
    NK_PARAM_LIST,      // 파라미터 리스트
    
    // 문장
    NK_BLOCK,           // 블록 { ... }
    NK_STMT_LIST,       // 문장 리스트
    NK_ASSIGN,          // 대입
    NK_IF,              // if 문
    NK_WHEN,            // when 문
    NK_WHEN_BRANCH,     // when 분기
    NK_WHILE,           // while 문
    NK_FOR,             // for 문
    NK_RETURN,          // return 문
    NK_EXPR_STMT,       // 표현식 문장
    NK_PRINT,           // println
    
    // 표현식
    NK_BINOP,           // 이항 연산
    NK_UNOP,            // 단항 연산
    NK_CALL,            // 함수 호출
    NK_ARG_LIST,        // 인자 리스트
    NK_IF_EXPR,         // if 표현식
    NK_RANGE,           // 범위 (1..10)
    
    // 리터럴
    NK_INT,             // 정수
    NK_STRING,          // 문자열
    NK_BOOL,            // 불리언
    NK_VAR,             // 변수
    
    // 타입
    NK_TYPE             // 타입 표시
} NodeKind;

/**
 * Node - AST 노드 구조체
 */
typedef struct Node {
    NodeKind kind;          // 노드 종류
    const char *op;         // 연산자/식별자/값
    struct Node **child;    // 자식 노드 배열
    int nchild;            // 자식 개수
    int line;              // 소스 라인 번호
    
    // 추가 정보
    int is_mutable;        // var인지 val인지 (0=val, 1=var)
} Node;

/**
 * node() - 새 AST 노드 생성 (가변 인자)
 */
Node *node(NodeKind kind, int line, const char *op, int nchild, ...);

/**
 * nodev() - 새 AST 노드 생성 (배열)
 */
Node *nodev(NodeKind kind, int line, const char *op, int nchild, Node **arr);

/**
 * print_ast() - AST 출력
 */
void print_ast(Node *n, int indent);

/**
 * free_ast() - AST 메모리 해제
 */
void free_ast(Node *n);

#endif
