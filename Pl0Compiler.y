%{
#include <stdlib.h>
#include <stdio.h>
int yylex();
%}
%token PLUS MINUS MUL DIV KLA_AUF KLA_ZU 
       ODD EQUAL NEQUAL 
       LESS LEQUAL GREATER GREQUAL 
       COMMA SEMICOLON PERIOD 
       BECOME
       COMMENTSTART COMMENTEND
       BEGINSYM END 
       IF THEN ELSE 
       WHILE DO 
       CALL PROCEDURE
       CONST INT 
       OUT IN 
       READ WRITE 
       ZAHL IDENT STRING
       FEHLER

//%union { char t[100]};
%%

program: block PERIOD;

block: constdeclare
     | vardeclare
     | procdeclare
     | statement
     ;

constdeclare: CONST IDENT EQUAL ZAHL anotherconstdeclare SEMICOLON ;
anotherconstdeclare: COMMA IDENT EQUAL ZAHL anotherconstdeclare ;

vardeclare: INT IDENT anothervardeclare SEMICOLON ;
anothervardeclare: COMMA IDENT ;



procdeclare: anotherProcdeclare;

statement: IDENT BECOME expression
         | CALL IDENT
         | BEGINSYM statement anotherStatement END 
         | IF condition THEN statement elseblock
         | WHILE condition DO statement
         | READ IDENT
         | WRITE expression
         | /* empty */
         ;

elseblock: ELSE statement;

condition: ODD expression
         | expression relop expression
         ;

relop: EQUAL
     | NEQUAL
     | LEQUAL
     | LEQUAL
     | GREATER
     | GREQUAL
     ;

anotherStatement: statement SEMICOLON
		| /*empty*/
		;

anotherProcdeclare: PROCEDURE IDENT SEMICOLON block SEMICOLON
		| /*empty*/
		;

expression: term
          | expression PLUS term
          | expression MINUS term
          ;
term:       factor
          | term MUL factor
          | term DIV factor
          ;
factor:   IDENT
          | ZAHL
          | KLA_AUF expression KLA_ZU
          | PLUS factor
          | MINUS factor
          ;
%%
int main()
{
    int rc = yyparse();
    if (rc == 0)
        printf("\n Verdammt nochmal ich bin der Beste!");
    else 
        printf("\n Verdammt nochmal ich bin nicht der Beste!!");
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
