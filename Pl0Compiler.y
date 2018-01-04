%{
#include <stdlib.h>
#include <stdio.h>
int yylex();
%}
%token PLUS MINUS MUL DIV KLA_AUF KLA_ZU
       ODD EQUAL NEQUAL LESS LEQUAL GREATER
       GREQUAL COMMA SEMICOLON PERIOD BECOME
       BEGINSYM END IF THEN WHILE DO
       CALL PROCEDURE CONST INT OUT IN READ
       WRITE FEHLER

%union { char _ident[10]; int _int};
%token<_ident> IDENT
%token<_int> ZAHL
%%

program: block PERIOD;

block:  {st.level_up();}
        constdeclare vardeclare procdeclare statement
        {st.level_down();}
        ;

constdeclare: CONST IDENT EQUAL ZAHL 
              {st.insert($$->name, st_const);}
              anotherconstdeclare SEMICOLON
            | /*empty*/
            ;

anotherconstdeclare: COMMA IDENT EQUAL ZAHL {st.insert($$->name, st_const);}
                     anotherconstdeclare
                   | /*empty*/
                   ;

vardeclare: INT 
            IDENT {st.insert($$->name, st_var);}
            anothervardeclare 
            SEMICOLON
          | /*empty*/
          ;

anothervardeclare: COMMA 
                   IDENT {st.insert($$->name, st_var)}
                   anothervardeclare
                 | /* empty*/
                 ;

procdeclare: PROCEDURE 
             IDENT {st.insert($2, st_proc)}
             SEMICOLON 
             block 
             SEMICOLON 
             procdeclare
           | /*empty*/
		   ;

statement: IDENT BECOME expression
           {
               int stl, sto;
               st.lookup($1, st_var, &stl, &sto);
           }
         | CALL IDENT
           {
               int stl, sto;
               st.lookup($2, st_proc, &stl, &sto);
           }
         | BEGINSYM statement anotherStatement END 
         | IF condition THEN statement
         | WHILE condition DO statement
         | READ IDENT
           {
               int stl, sto;
               st.lookup($2, st_var, &stl, &sto);
           }
         | WRITE expression
         | /* empty */
         ;

anotherStatement: SEMICOLON statement anotherStatement
		| /*empty*/
		;

condition: ODD expression
         | expression relop expression
         ;

relop: EQUAL
     | NEQUAL
     | LESS
     | LEQUAL
     | GREATER
     | GREQUAL
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
          {
              int stl, sto;
              st.lookup($1, st_var | st_const, &stl, &sto);
          }
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