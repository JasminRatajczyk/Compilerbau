%{
#include <stdlib.h>
#include <stdio.h>
int yylex();
%}
%token COMMENTSTART COMMENTEND PLUS MINUS MUL DIV KLA_AUF KLA_ZU ODD EQUAL NEQUAL
    LESS LEQUAL GREATER GREQUAL COMMA SEMICOLON PERIOD BECOME
    BEGINSYM END IF THEN WHILE DO CALL CONST INT PROCEDURE
    OUT IN ELSE ZAHL VARIABLE STRING FEHLER

//%union { char t[100]};
%%
expression: term
          | expression PLUS term
          | expression MINUS term
          ;
term:       factor
          | term MUL factor
          | term DIV factor
          ;
factor:     ZAHL
          | KLA_AUF expression KLA_ZU
          | PLUS factor
          | MINUS factor
          ;
%%
int main()
{
    printf("%d", yyparse());   
    return 0;
}

int yywrap() 
{
    return 1;
}

int yyerror()
{
    printf("Error\n");
    exit(1);
}