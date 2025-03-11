%option noyywrap
%{
    #include<stdio.h>
    #include<string.h>
%}

%%
charusat     { printf("university"); }
CHARUSAT     { printf("UNIVERSITY"); }
[Cc]harusat   { printf("University"); }
.            { printf("%s", yytext); }
%%

int main()
{
    printf("Enter the input text:\n");
    yylex();
    return 0;
}