# KotlinLite Compiler

> **컴파일러 설계 최종 프로젝트**  
> Kotlin 문법을 기반으로 한 교육용 프로그래밍 언어의 컴파일러/인터프리터

---

## 프로젝트 개요

**KotlinLite**는 Kotlin 프로그래밍 언어의 핵심 문법을 참고하여 설계한 간단한 프로그래밍 언어입니다.  
Flex와 Bison을 사용한 전통적인 컴파일러 구조를 따르며, AST 기반 인터프리터로 실행됩니다.

### 주요 특징

- **Flex 기반 어휘 분석**: 키워드, 연산자, 리터럴 토큰화
- **Bison 기반 구문 분석**: LALR(1) 파서, EBNF 문법
- **AST 생성**: 30개 이상의 노드 타입으로 프로그램 구조 표현
- **트리 워킹 인터프리터**: 즉시 실행, 심볼 테이블 관리
- **타입 시스템**: Int, String, Boolean 지원
- **11개 테스트**: 모든 기능 검증 완료

### 지원 기능 (과제 요구사항 충족)

| 기능 | 구현 내용 | 과제 요구사항 |
|-----|---------|-------------|
| **변수 선언** | `val` (불변), `var` (가변) | 필수 |
| **산술 연산** | `+`, `-`, `*`, `/`, `%` | 필수 |
| **비교 연산** | `<`, `>`, `<=`, `>=`, `==`, `!=` | 필수 |
| **논리 연산** | `&&`, `||`, `!` | 필수 |
| **조건문** | `if-else` | 필수 |
| **반복문** | `while`, `for-in-range` | 필수 |
| **함수** | 정의, 호출, 재귀 | 필수 |
| **출력** | `println()` | 구현 |

---

## 빌드 방법

### 필수 도구
- GCC 7.0 이상
- Flex 2.6 이상
- Bison 3.8 이상
- Make

### 도구 설치
```bash
# macOS
brew install flex bison gcc make
export PATH="/opt/homebrew/opt/bison/bin:$PATH"

# Linux
sudo apt install flex bison gcc make
```

### 빌드
```bash
cd final_project
make clean
make
```

빌드 성공 시 `./kotlinlite` 실행 파일이 생성됩니다.

---

## 실행 방법

### 파일 실행
```bash
./kotlinlite < examples/hello.kl
```

### 대화형 실행
```bash
./kotlinlite
val x = 10
var y = 20
println(x + y)
```

---

## 예제 코드

### Hello World
```kotlin
fun main() {
    println("Hello, KotlinLite!")
}
```

### 변수와 연산
```kotlin
val x = 10
var y = 20
y = y + x
println(y)  // 출력: 30
```

### 조건문
```kotlin
val x = 15
if (x > 10) {
    println("x is greater than 10")
} else {
    println("x is less than or equal to 10")
}
```

### 반복문
```kotlin
// while loop
var i = 0
while (i < 5) {
    println(i)
    i = i + 1
}

// for loop
for (i in 1..5) {
    println(i)
}
```

### 함수
```kotlin
fun add(a: Int, b: Int): Int {
    return a + b
}

fun main() {
    val result = add(10, 20)
    println(result)  // 출력: 30
}
```

### 재귀 함수
```kotlin
fun factorial(n: Int): Int {
    if (n <= 1) {
        return 1
    } else {
        return n * factorial(n - 1)
    }
}

fun main() {
    println(factorial(5))  // 출력: 120
}
```

---

## 테스트

프로젝트에는 11개의 테스트 파일이 포함되어 있습니다:

| 테스트 | 파일 | 내용 |
|-------|------|------|
| Test 01 | `tests/test01_variables.kl` | 변수 선언 (val, var) |
| Test 02 | `tests/test02_arithmetic.kl` | 산술 연산 |
| Test 03 | `tests/test03_ifelse.kl` | if-else 조건문 |
| Test 04 | `tests/test04_while.kl` | while 반복문 |
| Test 05 | `tests/test05_for.kl` | for 반복문 |
| Test 06 | `tests/test06_function.kl` | 함수 정의/호출 |
| Test 07 | `tests/test07_comparison.kl` | 비교 연산 |
| Test 08 | `tests/test08_logical.kl` | 논리 연산 |
| Test 09 | `tests/test09_nested.kl` | 중첩 구조 |
| Test 10 | `tests/test10_fibonacci.kl` | 피보나치 (재귀) |
| Test 11 | `tests/test11_factorial.kl` | 팩토리얼 (재귀) |

### 개별 테스트 실행
```bash
./kotlinlite < tests/test01_variables.kl
```

### 전체 테스트 실행
```bash
chmod +x run_all_tests.sh
./run_all_tests.sh
```

---

## 프로젝트 구조

### 디렉토리 구조
```
final_project/
├── src/                    # 소스 코드
│   ├── lexer.l            # Flex 어휘 분석기
│   ├── parser.y           # Bison 구문 분석기
│   ├── ast.c              # AST 구현
│   ├── interp.c           # 인터프리터 구현
│   └── main.c             # 메인 함수
├── include/               # 헤더 파일
│   ├── ast.h             # AST 헤더
│   └── interp.h          # 인터프리터 헤더
├── tests/                # 테스트 프로그램 (11개)
│   ├── test01_variables.kl
│   ├── test02_arithmetic.kl
│   └── ...
├── examples/             # 예제 코드
├── docs/                 # 문서
│   └── project_report.md # 프로젝트 설명서 (과제 제출용)
├── Makefile              # 빌드 설정
└── README.md             # 본 파일
```

### 컴파일 과정
```
lexer.l ──(flex)──> lex.yy.c ─┐
                               ├─(gcc)──> kotlinlite
parser.y ─(bison)─> parser.c ─┘
ast.c, interp.c, main.c ───────┘
```

---

## 문서

### 필수 문서 (과제 제출용)

| 문서 | 위치 | 내용 |
|-----|------|------|
| **README** | `README.md` | 빌드/실행 방법, 의존성 |
| **프로젝트 설명서** | `docs/project_report.md` | 언어 개요, 문법, 구조, 기능 |

---

## 구현 특징

### 어휘 분석 (Lexer)
- 정규 표현식 기반 토큰 인식
- 블록 주석 처리 (`/* */`)
- 라인 주석 처리 (`//`)
- 줄 번호 추적

### 구문 분석 (Parser)
- LALR(1) 파서
- 연산자 우선순위 및 결합성 정의
- Dangling-else 문제 해결
- 즉시 AST 생성

### 실행 (Interpreter)
- 트리 워킹 방식
- 심볼 테이블로 변수 관리
- 함수 테이블로 함수 관리
- val/var 불변성 검사

---

## 테스트 검증

### 테스트 통과율
- **전체**: 11개
- **성공**: 11개 (100%)
- **실패**: 0개

---

## 제한사항

### 미구현 기능
- 배열 및 컬렉션
- 클래스/객체 지향
- 타입 추론
- when 표현식 (부분적)
- 람다 표현식

### 알려진 제약
- 전역 변수 미지원
- 표준 라이브러리 제한적 (println만)
- 파일 I/O 미지원

---

## 과제 제출 정보

### 제출물 체크리스트
- 소스 코드 전체 (`src/`, `include/`)
- README (본 파일)
- 프로젝트 설명서 (`docs/project_report.md`)
- 테스트 프로그램 ≥10개 (`tests/`)
- Makefile (빌드 자동화)

### 과제 요구사항 충족
- 어휘 분석 (Flex)
- 구문 분석 (Bison) + 문법 문서화
- AST 생성 + 인터프리터 실행
- 필수 기능 5개 (변수, 연산, 조건, 반복, 함수)
- 10개 이상 테스트 (11개 완성)

---

## 개발 정보

- **개발 환경**: macOS / Linux
- **컴파일러**: GCC 7.0+
- **도구**: Flex 2.6+, Bison 3.8+
- **빌드 시스템**: GNU Make

---

본 프로젝트는 컴파일러 설계 과목의 교육용 프로젝트입니다.