%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YY_WRAP 1

int line = 1;

void print_token(const char* type, const char* lexeme) {
    printf("%s: %s\n", type, lexeme);
}
%}

%%
"int"|"char"|"return"|"if"|"else"|"while"|"for"|"float"|"double"  { print_token("Keyword", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { print_token("Identifier", yytext); }

[0-9]+                  { print_token("Constant", yytext); }

\'[^\']*\'              { print_token("String", yytext); }

[+\-*/=<>!&|]+          { print_token("Operator", yytext); }

[{}()\[\],.;:]          { print_token("Punctuation", yytext); }

"//".*                  { /* Ignore single-line comments */ }

"/*"([^*]|\*+[^/*])*\*+"/"  { /* Ignore multi-line comments */ }

[ \t\r]+                { /* Ignore white spaces */ }

\n                      { line++; }

.                       { printf("Lexical Error at line %d: %s\n", line, yytext); }

%%

int main() {
    printf("Enter Input:\n");
    yylex();
    return 0;
}
