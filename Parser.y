%{
#include <stdlib.h>
#include <stdio.h>
#include "Symtab/Symtab.hpp"

void yyerror(const char* s);
int yylex();
int yyparse();

Symtab st;
%}

%token t_PLUS t_MINUS t_MUL t_DIV t_KLA_AUF t_KLA_ZU
       t_ODD t_EQUAL t_NEQUAL t_LESS t_LEQUAL t_GREATER
       t_GREQUAL t_COMMA t_SEMICOLON t_PERIOD t_ASSIGN
       t_BEGIN t_END t_IF t_THEN t_WHILE t_DO
       t_CALL t_PROCEDURE t_CONST t_VAR t_READ t_WRITE

%union { char _ident[10]; int _int;}
%token<_ident> t_IDENT
%token<_int> t_ZAHL
%%

program: block t_PERIOD;

block:
{ st.level_up(); }  
constdeclare vardeclare procdeclare statement 
{ st.level_down(); }
;

constdeclare: t_CONST t_IDENT t_EQUAL t_ZAHL 
              { st.insert ( $2 , st_const , $4 ); }
              anotherconstdeclare t_SEMICOLON
            | /*empty*/
            ;

anotherconstdeclare: t_COMMA t_IDENT t_EQUAL t_ZAHL 
                     { st.insert ( $2, st_const, $4 ); } 
                     anotherconstdeclare
                   | /*empty*/
                   ;

vardeclare: t_VAR t_IDENT 
            { st.insert ( $2, st_var ); }
            anothervardeclare t_SEMICOLON
          | /*empty*/
          ;

anothervardeclare: t_COMMA t_IDENT anothervardeclare
                   { st.insert ( $2, st_var ); }
                 | /* empty*/
                 ;

procdeclare: t_PROCEDURE t_IDENT 
             { st.insert ( $2, st_proc ); }
             t_SEMICOLON block t_SEMICOLON procdeclare
           | /*empty*/
		   ;

statement: t_IDENT t_ASSIGN expression
           {
               int sto, stl, val;
               st.lookup($1, st_var, sto, stl, val);
           }
         | t_CALL t_IDENT
           {
               int sto, stl, val;
               st.lookup($2, st_proc, sto, stl, val);
           }
         | t_BEGIN statement anotherStatement t_END 
         | t_IF condition t_THEN statement
         | t_WHILE condition t_DO statement
         | t_READ t_IDENT
           {
               int sto, stl, val;
               st.lookup($2, st_var, sto, stl, val);
           }
         | t_WRITE t_IDENT
           {
               int sto, stl, val;
               st.lookup($2, st_var | st_const, sto, stl, val);
           }
         | /* empty */
         ;

anotherStatement: t_SEMICOLON statement anotherStatement
		| /*empty*/
		;

condition: t_ODD expression
         | expression relop expression
         ;

relop: t_EQUAL
     | t_NEQUAL
     | t_LESS
     | t_LEQUAL
     | t_GREATER
     | t_GREQUAL
     ;

expression: term
          | expression t_PLUS term
          | expression t_MINUS term
          ;
term:       factor
          | term t_MUL factor
          | term t_DIV factor
          ;
factor:   t_IDENT
          | t_ZAHL
          | t_KLA_AUF expression t_KLA_ZU
          | t_PLUS factor
          | t_MINUS factor
          ;
%%
int main()
{
    int rc = yyparse();
    if (rc == 0)
    {
        printf("\n Program executed Successfully!\n");
    }
    else 
    {
        printf("\n Program has been stopped!\n");
    }
    return 0;
}

void yyerror(const char *s)
{
    printf("%s", s);
    exit(1);
}