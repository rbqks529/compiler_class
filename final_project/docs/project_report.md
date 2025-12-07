# 컴파일러 프로젝트 (KotlinLite)

> 컴파일러 설계 최종 프로젝트  
> 2025년 12월 7일
> 
> 202012362 조규빈

---

## 목차

1. [언어 개요 및 설계 의도](#1-언어-개요-및-설계-의도)
2. [문법 정의](#2-문법-정의)
3. [전체 구조](#3-전체-구조)
4. [구현된 기능](#4-구현된-기능)
5. [미구현/제한 사항](#5-미구현제한-사항)
6. [테스트](#6-테스트)
7. [빌드 및 실행](#7-빌드-및-실행)
8. [결론](#8-결론)

---

## 1. 언어 개요 및 설계 의도

### 1.1 언어 소개

**KotlinLite**는 Kotlin 프로그래밍 언어의 핵심 문법을 참고하여 설계한 교육용 프로그래밍 언어입니다. 
실무에서 널리 사용되는 Kotlin의 간결하고 표현력 있는 문법 특징을 반영하면서도, 
학습과 구현이 용이하도록 핵심 기능에 집중하였습니다.

### 1.2 설계 의도

본 프로젝트는 다음과 같은 설계 의도를 가지고 개발되었습니다:

1. **명확한 의미론**: 불변성(`val`)과 가변성(`var`)을 명확히 구분하여 안전한 프로그래밍 패턴을 제공
2. **간결한 문법**: Kotlin의 간결하고 읽기 쉬운 문법을 차용하여 가독성 향상
3. **타입 안전성**: 정적 타입 시스템을 통한 실행 전 오류 검출
4. **함수형 지원**: 함수를 객체로 다루며 재귀 호출 지원

### 1.3 주요 특징

| 특징 | 설명 | Kotlin과의 유사성 |
|-----|------|-----------------|
| **변수 선언** | `val`(불변), `var`(가변) 구분 |  동일 |
| **타입 시스템** | Int, String, Boolean 지원 | 기본 타입 동일 |
| **함수 정의** | `fun` 키워드 사용 | 동일 |
| **제어 구조** | if-else, while, for-in-range | 유사 |
| **타입 표기** | 명시적 타입 선언 가능 | 동일 |

### 1.4 과제 요구사항

본 프로젝트는 다음의 과제 필수 요구사항을 모두 충족합니다:

- **변수 선언 및 대입**: val, var를 통한 변수 선언
- **산술/비교/논리 연산**: +, -, *, /, %, <, >, ==, !=, &&, ||, ! 지원
- **조건문**: if-else 구조 구현
- **반복문**: while, for-in-range 구현
- **함수 호출**: 함수 정의, 호출, 재귀 지원

---

## 2. 문법 정의 (EBNF)

### 프로그램 구조
```ebnf
Program        ::= Statement*
Statement      ::= VarDecl | FuncDef | IfStmt | WhileStmt | ForStmt 
                 | ReturnStmt | ExprStmt
```

### 변수 선언
```ebnf
VarDecl        ::= 'val' IDENTIFIER (':' Type)? '=' Expression
                 | 'var' IDENTIFIER (':' Type)? '=' Expression
Type           ::= 'Int' | 'String' | 'Boolean'
```

### 함수 정의
```ebnf
FuncDef        ::= 'fun' IDENTIFIER '(' ParamList? ')' (':' Type)? Block
ParamList      ::= Param (',' Param)*
Param          ::= IDENTIFIER ':' Type
Block          ::= '{' Statement* '}'
```

### 제어문
```ebnf
IfStmt         ::= 'if' '(' Expression ')' Block ('else' Block)?
WhileStmt      ::= 'while' '(' Expression ')' Block
ForStmt        ::= 'for' '(' IDENTIFIER 'in' Expression '..' Expression ')' Block
ReturnStmt     ::= 'return' Expression?
```

### 표현식
```ebnf
Expression     ::= LogicalOr
LogicalOr      ::= LogicalAnd ('||' LogicalAnd)*
LogicalAnd     ::= Comparison ('&&' Comparison)*
Comparison     ::= Additive (('<' | '>' | '<=' | '>=' | '==' | '!=') Additive)?
Additive       ::= Multiplicative (('+' | '-') Multiplicative)*
Multiplicative ::= Unary (('*' | '/' | '%') Unary)*
Unary          ::= '!' Unary | Primary
Primary        ::= INTEGER | STRING | 'true' | 'false' | IDENTIFIER
                 | FunctionCall | '(' Expression ')'
FunctionCall   ::= IDENTIFIER '(' ArgList? ')'
ArgList        ::= Expression (',' Expression)*
```

---

## 3. 전체 구조

### 3.1 시스템 아키텍처

본 컴파일러는 전통적인 파이프라인 구조를 따릅니다:

```
┌─────────────────┐
│  소스 코드 (.kl)  │
└────────┬────────┘
         │
         ▼
┌─────────────────────────────────────┐
│   1. 어휘 분석 (Lexical Analysis)     │
│   - Flex (lexer.l)                  │
│   - 토큰 생성: ID, NUM, IF, WHILE...  │
└────────┬────────────────────────────┘
         │ Token Stream
         ▼
┌─────────────────────────────────────┐
│   2. 구문 분석 (Syntax Analysis)      │
│   - Bison (parser.y)                │
│   - LALR(1) 파싱                     │
│   - 구문 오류 검출                     │
└────────┬────────────────────────────┘
         │ AST
         ▼
┌─────────────────────────────────────┐
│   3. 추상 구문 트리 (AST)              │
│   - ast.c / ast.h                   │
│   - 트리 구조 생성                     │
│   - 30+ 노드 타입                     │
└────────┬────────────────────────────┘
         │ AST Root
         ▼
┌─────────────────────────────────────┐
│   4. 인터프리터 (Interpreter)          │
│   - interp.c / interp.h             │
│   - 트리 워킹 실행                     │
│   - 심볼 테이블 관리                    │
└────────┬────────────────────────────┘
         │
         ▼
┌─────────────────┐
│   실행 결과       │
└─────────────────┘
```

### 3.2 모듈별 상세 설명

#### 3.2.1 어휘 분석기 (Lexer)

**파일**: `src/lexer.l`  
**도구**: GNU Flex 2.6+  
**역할**: 소스 코드를 토큰으로 분해

**주요 기능**:

| 토큰 종류 | 예시 | 설명 |
|---------|------|------|
| 키워드 | `fun`, `val`, `var`, `if`, `while` | 예약어 |
| 식별자 | `myVar`, `calculateSum` | 변수/함수 이름 |
| 리터럴 | `42`, `"hello"`, `true` | 상수 값 |
| 연산자 | `+`, `-`, `*`, `&&`, `==` | 산술/논리/비교 |
| 구분자 | `{`, `}`, `(`, `)`, `;` | 구조 구분 |
| 주석 | `//...`, `/* ... */` | 무시됨 |

**구현 특징**:
- 정규 표현식 기반 패턴 매칭
- 상태 머신을 이용한 블록 주석 처리
- 줄 번호 추적 (`yylineno`)

#### 3.2.2 구문 분석기 (Parser)

**파일**: `src/parser.y`  
**도구**: GNU Bison 3.8+  
**역할**: 토큰 스트림을 AST로 변환

**주요 기능**:
- **LALR(1) 파싱**: 효율적인 상향식 파싱
- **연산자 우선순위**: 
  ```
  낮음: ||
        &&
        ==, !=
        <, >, <=, >=
        +, -
        *, /, %
  높음: ! (단항)
  ```
- **결합성 제어**: 좌결합 (`%left`), 우결합 (`%right`)
- **Dangling-else 해결**: `%nonassoc LOWER_THAN_ELSE`

**구현 특징**:
- 재귀 하강 대신 테이블 기반 파싱
- 14개의 shift/reduce 충돌 (의도된 설계)
- 즉시 AST 노드 생성

#### 3.2.3 추상 구문 트리 (AST)

**파일**: `src/ast.c`, `include/ast.h`  
**역할**: 프로그램의 계층적 구조 표현

**노드 타입** (30개 이상):
```c
typedef enum {
    // 프로그램 구조
    NK_PROGRAM, NK_BLOCK, NK_STMT_LIST,
    
    // 선언문
    NK_VAL_DECL, NK_VAR_DECL, NK_FUNC_DEF, NK_PARAM,
    
    // 제어문
    NK_IF, NK_WHILE, NK_FOR, NK_RETURN,
    
    // 표현식
    NK_BINOP, NK_UNOP, NK_ASSIGN,
    NK_INT_LITERAL, NK_STRING_LITERAL, NK_BOOL_LITERAL,
    NK_IDENTIFIER, NK_CALL,
    
    // 기타
    NK_EXPR_STMT, NK_PRINTLN
} NodeKind;
```

**주요 함수**:
- `node()`: 가변 인자로 AST 노드 생성
- `nodev()`: 배열로 자식 노드 전달
- `print_ast()`: 디버깅용 트리 출력
- `free_ast()`: 메모리 해제

#### 3.2.4 인터프리터 (Interpreter)

**파일**: `src/interp.c`, `include/interp.h`  
**역할**: AST를 순회하며 코드 실행

**핵심 데이터 구조**:

1. **값 표현**:
```c
typedef struct {
    ValueType type;  // VAL_INT, VAL_STRING, VAL_BOOL
    union {
        int intVal;
        char *strVal;
        int boolVal;
    };
} Value;
```

2. **심볼 테이블** (변수 관리):
```c
typedef struct Symbol {
    char *name;
    Value value;
    int is_mutable;  // val: 0, var: 1
    struct Symbol *next;
} Symbol;
```

3. **함수 테이블**:
```c
typedef struct Function {
    char *name;
    ASTNode *params;
    ASTNode *body;
    struct Function *next;
} Function;
```

**실행 과정**:
1. `eval_expr()`: 표현식 평가 (재귀적)
2. `exec_stmt()`: 문장 실행
3. `add_symbol()`, `find_symbol()`: 변수 관리
4. `add_function()`, `find_function()`: 함수 관리

### 3.3 데이터 흐름

```
입력: val x = 10 + 5

[Lexer] → VAL, ID(x), ASSIGN, NUM(10), PLUS, NUM(5)

[Parser] → (VAL_DECL x
             (BINOP +
               (INT 10)
               (INT 5)))

[Interpreter] → 심볼 테이블에 x=15 저장 (불변)
```

#### AST (Abstract Syntax Tree)
- **파일**: `src/ast.c`, `include/ast.h`
- **기능**:
  - 30개 이상의 노드 타입 정의
  - 트리 구조 생성 및 관리
  - 메모리 관리 (생성/해제)

#### 인터프리터
- **파일**: `src/interp.c`, `include/interp.h`
- **기능**:
  - 트리 워킹 방식으로 AST 실행
  - 심볼 테이블 관리 (변수)
  - 함수 테이블 관리 (함수 정의)
  - 타입 검사 및 실행

### 3.3 데이터 구조

#### AST 노드 타입
```c
typedef enum {
    NK_PROGRAM,
    NK_VAL_DECL, NK_VAR_DECL,
    NK_FUNC_DEF, NK_PARAM,
    NK_IF, NK_WHILE, NK_FOR,
    NK_RETURN, NK_EXPR_STMT,
    NK_BINOP, NK_UNOP,
    NK_INT_LITERAL, NK_STRING_LITERAL, NK_BOOL_LITERAL,
    NK_IDENTIFIER, NK_CALL,
    NK_ASSIGN, NK_BLOCK
} NodeKind;
```

#### 값 타입
```c
typedef enum {
    VAL_INT,
    VAL_STRING,
    VAL_BOOL,
    VAL_NONE
} ValueType;
```

---

## 4. 구현된 기능

### 4.1 변수 선언 및 대입
```kotlin
val x = 10          // 불변 변수
var y = 20          // 가변 변수
y = y + x           // 재할당 가능
```

### 4.2 산술/비교/논리 연산
```kotlin
val a = 10 + 5 * 2  // 산술: +, -, *, /, %
val b = a > 10      // 비교: <, >, <=, >=, ==, !=
val c = b && true   // 논리: &&, ||, !
```

### 4.3 조건문
```kotlin
if (x > 10) {
    println("large")
} else {
    println("small")
}
```

### 4.4 반복문
```kotlin
// while loop
while (i < 10) {
    i = i + 1
}

// for loop
for (i in 1..10) {
    println(i)
}
```

### 4.5 함수
```kotlin
fun add(a: Int, b: Int): Int {
    return a + b
}

fun fibonacci(n: Int): Int {
    if (n <= 1) {
        return n
    } else {
        return fibonacci(n-1) + fibonacci(n-2)
    }
}
```

---

## 5. 미구현/제한 사항

### 미구현 기능
- 배열 및 컬렉션 (List, Map 등)
- 클래스 및 객체 지향 기능
- when 표현식 (부분 구현만 존재)
- 타입 추론 (명시적 타입 선언 필수)
- 람다 표현식
- 고차 함수
- null 안전성

### 제한 사항
- 함수는 최상위 레벨에서만 정의 가능
- 전역 변수 미지원
- 표준 라이브러리 미지원 (println만 지원)
- 파일 I/O 미지원
- 문자열 연산 제한적

---

## 6. 테스트

### 테스트 구성
총 11개의 테스트 프로그램으로 모든 기능 검증

| 번호 | 테스트 | 검증 내용 |
|-----|--------|---------|
| 01 | variables | val, var 선언 |
| 02 | arithmetic | 산술 연산 (+, -, *, /, %) |
| 03 | ifelse | if-else 조건문 |
| 04 | while | while 반복문 |
| 05 | for | for-in-range 반복문 |
| 06 | function | 함수 정의 및 호출 |
| 07 | comparison | 비교 연산 |
| 08 | logical | 논리 연산 |
| 09 | nested | 중첩 제어 구조 |
| 10 | fibonacci | 재귀 함수 (피보나치) |
| 11 | factorial | 재귀 함수 (팩토리얼) |

### 테스트 결과
- **전체**: 11개
- **성공**: 11개

---

## 7. 빌드 및 실행

### 빌드 요구사항
- GCC 7.0+
- Flex 2.6+
- Bison 3.8+
- Make

### 빌드 명령
```bash
make clean
make
```

### 실행 방법
```bash
# 파일 실행
./kotlinlite < test.kl

# 대화형 실행
./kotlinlite
```

---

## 8. 참고 자료

### 개발 도구
- Flex: https://github.com/westes/flex
- Bison: https://www.gnu.org/software/bison/
- GCC: https://gcc.gnu.org/

### 참고 문서
- Kotlin Language: https://kotlinlang.org/

---

## 8. 결론

### 8.1 프로젝트

본 프로젝트에서는 Kotlin 언어를 참고한 **KotlinLite**라는 코틀린의 가벼운 버전인 프로그래밍 언어를 설계하고, 
완전히 동작하는 컴파일러/인터프리터를 구현하였습니다.

#### 구현 사항

1. **완전한 컴파일러 파이프라인 구현**
   - Flex 기반 어휘 분석기 (Lexer)
   - Bison 기반 구문 분석기 (Parser)
   - 추상 구문 트리 (AST) 생성
   - 트리 워킹 인터프리터 (Interpreter)

2. **핵심 언어 기능 구현**
   - 변수 선언 및 대입 (val/var 구분)
   - 산술, 비교, 논리 연산자
   - 조건문 (if-else)
   - 반복문 (while, for-in-range)
   - 함수 정의, 호출, 재귀

3. **충분한 테스트 및 검증**
   - 11개의 테스트 프로그램 작성 및 실행
   - 모든 테스트 케이스 100% 통과
   - 오류 처리 메커니즘 구현

4. **완전한 문서화**
   - EBNF 형식의 문법 정의
   - 시스템 구조 및 흐름도
   - 상세한 빌드 및 실행 가이드

### 8.2 한계 및 향후 개선 방향

#### 현재의 한계점

1. **제한적인 타입 시스템**: 기본 타입만 지원, 타입 추론 미지원
2. **표준 라이브러리 부재**: println 외 추가 기능 없음
3. **고급 기능 부재**: 배열, 클래스, 람다 등 미구현

#### 향후 개선 방향

1. **기능 확장**
   - when 표현식 완전 구현
   - 배열 및 컬렉션 타입 추가
   - 클래스 및 객체 지향 기능
   - 람다 표현식 및 고차 함수

2. **품질 개선**
   - 더욱 정확한 오류 메시지 (라인 번호, 컨텍스트 정보)
   - 타입 추론 기능
   - 최적화된 실행

3. **도구 개선**
   - REPL (Read-Eval-Print Loop) 개선
   - 디버거 기능
   - IDE 통합 (LSP 지원)

### 8.3 최종 결론

KotlinLite 프로젝트는 **컴파일러의 전체 파이프라인을 구현**하였으며,
과제의 모든 요구사항을 충족하고 있습니다. 

Flex와 Bison을 활용한 전통적인 컴파일러 구조를 따르면서도,
AST 기반의 인터프리터를 통해 실제로 동작하는 프로그래밍 언어를 구현하였습니다.

테스트 케이스가 모두 성공적으로 통과하여, 
구현된 모든 기능이 올바르게 동작함을 검증하였습니다.

이번 프로젝트를 통해 컴파일러 설계의 이론과 실무를 모두 경험하였으며,
프로그래밍 언어 설계 및 구현에 대한 깊이 있는 이해를 얻을 수 있었습니다.

---

## 참고 문헌

1. Alfred V. Aho, Monica S. Lam, Ravi Sethi, Jeffrey D. Ullman, "Compilers: Principles, Techniques, and Tools (2nd Edition)", Pearson, 2006
2. Kotlin Language Documentation, https://kotlinlang.org/docs/home.html
3. Flex Manual, https://github.com/westes/flex
4. GNU Bison Manual, https://www.gnu.org/software/bison/manual/