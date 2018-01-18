%{
#include <stdlib.h>
#include <stdio.h>
#include "Symtab/Symtab.hpp"
#include "Ast/AstGenerator.h"
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

block:  { yyerror ( !st.level_up() ); }
        constdeclare vardeclare procdeclare statement
        { yyerror ( !st.level_down() ); }
        ;

constdeclare: CONST IDENT EQUAL ZAHL 
              { yyerror ( !st.insert($2, st_const, $4) ); }
              anotherconstdeclare SEMICOLON
            | /*empty*/
            ;

anotherconstdeclare: COMMA IDENT EQUAL ZAHL 
                     { yyerror ( !st.insert($2, st_const,$4) ); }
                     anotherconstdeclare
                   | /*empty*/
                   ;

vardeclare: INT IDENT 
            { yyerror ( !st.insert($2, st_var) ); }
            anothervardeclare SEMICOLON
          | /*empty*/
          ;

anothervardeclare: COMMA IDENT
                   { yyerror( !st.insert($2, st_var) ); }
                   anothervardeclare
                 | /* empty*/
                 ;

procdeclare: PROCEDURE IDENT 
             { yyerror ( !st.insert($2, st_proc) ); }
             SEMICOLON block SEMICOLON procdeclare
           | /*empty*/
		   ;

statement: IDENT BECOME expression
           {
               int stl, sto;
               { yyerror ( !st.modify($1, st_var, &stl, &sto) ); }
           }
         | CALL IDENT
           {
                int stl, sto;
                yyerror ( !st.lookup($2, st_proc, &stl, &sto) );
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
    Symtab st = new_Symtab();

    int rc = yyparse();
    if (rc == 0)
        printf("\n Program executed Successfully!");
    else 
        printf("\n Program has been stopped!");
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