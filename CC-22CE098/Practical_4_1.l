%option noyywrap
%{
    #include<stdio.h>
%}

%%
[0-9]+   { printf("%s\n", yytext); }
.
%%

int main()
{
    printf("Enter the input string: \n");
    yylex();
    return 0;
}