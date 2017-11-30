%{
#include <stdlib.h>
#include <stdio.h>

void yyerror(char *s);
%}
%token PLUS MINUS MUL DIV KLA_AUF KLA_ZU ZAHL FEHLER
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
void yyerror(char *s)
{
}
int main()
{
    int rc;
    rc = yyparse();
    if (rc == 0)
        printf("Syntax OK");
    else
        printf("Syntax nicht OK");
    return rc;
}

