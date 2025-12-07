%option noyywrap
%option yylineno
%option nounput
%option noinput

%{
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>

/* yylineno는 flex가 자동 관리 */
%}

/* 블록 주석 처리 */
%x COMMENT

%%

[ \t\r\n]+                        { /* skip whitespace */ }

"/*"                              { BEGIN(COMMENT); }
<COMMENT>[^*]+                    { /* skip */ }
<COMMENT>"*"+[^*/]                { /* skip */ }
<COMMENT>"*"+"/"                  { BEGIN(INITIAL); }
<COMMENT><<EOF>>                  { BEGIN(INITIAL); }

"//".*                            { /* skip line comment */ }

"fun"                             { return FUN; }
"val"                             { return VAL; }
"var"                             { return VAR; }
"if"                              { return IF; }
"else"                            { return ELSE; }
"when"                            { return WHEN; }
"while"                           { return WHILE; }
"for"                             { return FOR; }
"in"                              { return IN; }
"return"                          { return RETURN; }
"println"                         { return PRINTLN; }

"Int"                             { yylval = node(NK_TYPE, yylineno, "Int", 0); return TYPE_INT; }
"String"                          { yylval = node(NK_TYPE, yylineno, "String", 0); return TYPE_STRING; }
"Boolean"                         { yylval = node(NK_TYPE, yylineno, "Boolean", 0); return TYPE_BOOL; }

"true"                            { yylval = node(NK_BOOL, yylineno, "true", 0); return TRUE; }
"false"                           { yylval = node(NK_BOOL, yylineno, "false", 0); return FALSE; }

"=="                              { return EQ; }
"!="                              { return NE; }
"<="                              { return LE; }
">="                              { return GE; }
"&&"                              { return AND; }
"||"                              { return OR; }
".."                              { return DOTDOT; }
"->"                              { return ARROW; }

"="                               { return '='; }
"<"                               { return '<'; }
">"                               { return '>'; }
"+"                               { return '+'; }
"-"                               { return '-'; }
"*"                               { return '*'; }
"/"                               { return '/'; }
"%"                               { return '%'; }
"!"                               { return '!'; }
";"                               { return ';'; }
","                               { return ','; }
":"                               { return ':'; }
"("                               { return '('; }
")"                               { return ')'; }
"{"                               { return '{'; }
"}"                               { return '}'; }

[a-zA-Z_][a-zA-Z0-9_]*            { 
                                    yylval = node(NK_VAR, yylineno, yytext, 0);
                                    return IDENT;
                                  }

[0-9]+                            { 
                                    yylval = node(NK_INT, yylineno, yytext, 0);
                                    return INTEGER;
                                  }

\"([^\\\n\"]|\\.)*\"              { 
                                    yylval = node(NK_STRING, yylineno, yytext, 0);
                                    return STRING;
                                  }

.                                 { /* unknown char */ }

%%
