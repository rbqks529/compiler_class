%option noyywrap yylineno
%{
#include <stdlib.h>
#include "parser.tab.h"   /* NUMBER, yylval */
%}

/* 숫자: 정수/실수/지수 */
D      [0-9]
NUM    {D}+(\.{D}+)?([eE][+-]?{D}+)?

%%
[ \t\r]+           ;                            /* 공백 무시 */
\n                 ;                            /* 줄바꿈: yylineno 자동 증가 */

{NUM}              { yylval.num = strtod(yytext, 0); return NUMBER; }

"("                { return '('; }
")"                { return ')'; }
";"                { return ';'; }

"+"                { return '+'; }
"-"                { return '-'; }
"*"                { return '*'; }
"/"                { return '/'; }

.                  { return yytext[0]; }
%%
