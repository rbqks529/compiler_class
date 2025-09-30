/* scanner.l */
%option noyywrap

%{
#include "parser.tab.h"   /* bison이 생성하는 헤더 */
%}

DIGIT   [0-9]+

%%

{DIGIT}     { yylval.ival = atoi(yytext); return T_NUMBER; }
"+"         { return '+'; }
"*"         { return '*'; }
"("         { return '('; }
")"         { return ')'; }
"\n"        { return '\n'; } /* 개행을 토큰으로 넘김 */
[\t\r]+     { /* 그냥 무시 */ }

.           { /* 알 수 없는 문자 무시(혹은 에러 출력 가능) */ }

%%