%{
#include <stdlib.h>
#include <stdio.h>
#include "Symtab/Symtab.hpp"
#include "Ast/Ast.h"

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

%union 
{ 
    char _ident[100]; 
    int _int; 
    block _block; 
    statement _statement;
    variable _variable;
    expression _expression; 
}

%token<_ident> t_IDENT
%token<_int> t_ZAHL

%type<_ident> relop
%type<_block> block procdeclare
%type<_statement> statement anotherStatement
%type<_variable> vardeclare anothervardeclare constdeclare anotherconstdeclare
%type<_expression> expression term factor condition
%%

program: block t_PERIOD;

block:
{ 
    st.level_up(); 
    $$ = new_block($1, $2, $3, $4);
}
constdeclare vardeclare procdeclare statement
{ 
    st.level_down(); 
}
;

constdeclare: t_CONST t_IDENT t_EQUAL t_ZAHL
              { 
                  int stl, sto;
                  st.insert ( $2 , st_const );
                  st.lookup($2, st_const, stl, sto);
                  $$ = new_variable(st_const, stl, sto, NULL);
              }
              anotherconstdeclare 
              { 
                  $$->next = $5; 
              } 
              t_SEMICOLON {
                  
              }
            | { $$ = NULL;} /*empty*/
            ;

anotherconstdeclare: t_COMMA t_IDENT t_EQUAL t_ZAHL
                     { 
                         int stl, sto;
                         st.insert ( $2 , st_const );
                         st.lookup($2, st_const, stl, sto);
                         $$ = new_variable(st_const, stl, sto, NULL);
                     }
                     anotherconstdeclare 
                     { 
                         $$->next = $5; 
                     }
                   | { $$ = NULL; } /*empty*/
                   ;

vardeclare: t_VAR t_IDENT
            {
                int stl, sto;
                st.insert ( $2, st_var );
                st.lookup ( $2, st_var, stl, sto );
                $$ = new_variable ( st_var, stl, sto, NULL ); 
            }
            anothervardeclare 
            { 
                $$->next = $3; 
            } 
            t_SEMICOLON
          | { $$ = NULL; } /*empty*/
          ;

anothervardeclare: t_COMMA t_IDENT 
                   {    
                        int stl, sto;
                        st.insert ( $2, st_var );
                        st.lookup ( $2, st_var, stl, sto );
                        $$ = new_variable ( st_var, stl, sto, $3 );
                    }
                    anothervardeclare 
                    { 
                        $$->next = $3;
                    }

                 | { $$ = NULL; } /* empty*/
                 ;

procdeclare: t_PROCEDURE t_IDENT //AST FINISHED
             { 
                 st.insert ( $2, st_proc ); 
             }
             t_SEMICOLON 
             block 
             {
                 $$ = $4; 
             }
             t_SEMICOLON procdeclare
           | { $$ = NULL; } /*empty*/
		   ;

statement: t_IDENT t_ASSIGN expression
         {
            int sto, stl;
            st.lookup($1, st_var, sto, stl );
            $$ = new_statement ( stmnt_assign, stl, sto, NULL, $3 );
         }
         | t_CALL t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_proc, sto, stl );

            $$ = new_statement (stmnt_call, sto, stl, NULL, NULL ); //TODO
         }
         | t_BEGIN statement anotherStatement t_END
         {
            $2->next = $3;
            $$ = $3;
         }
         | t_IF condition t_THEN statement
         {
            $$ = new_statement ( stmnt_if, -1, -1, $2, $4);
         }
         | t_WHILE condition t_DO statement
         {
            $$ = new_statement ( stmnt_while, -1, -1, $2, $4);
         }
         | t_READ t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_var, sto, stl );
            $$ = new_statement ( stmnt_read, stl, sto, NULL, NULL);
         }
         | t_WRITE expression
         {
            $$ = new_statement ( stmnt_write, -1, -1, NULL, $2);
         }
         | { $$ = NULL; } /* empty */
         ;

anotherStatement: t_SEMICOLON statement anotherStatement //AST FINISHED
		        {
                    $$ = new_statement ( stmnt_end, -1, -1, $4, NULL);
                }
                | { $$ = NULL;} /*empty*/
		        ;

condition: t_ODD expression //AST FINISHED
         {
             $$ = new_expression ("ODD", $2, NULL);
         }
         | expression relop expression
         {
             $$ = new_expression ($2, $1, $3);
         }
         ;

relop: t_EQUAL   { $$ = "=" ; } //AST FINISHED
     | t_NEQUAL  { $$ = "#" ; } 
     | t_GREATER { $$ = ">" ; }
     | t_LESS    { $$ = "<" ; }
     | t_GREQUAL { $$ = ">="; }
     | t_LEQUAL  { $$ = "<="; }
     ;

expression: term                    { $$ = new_expression (" ", $1, NULL);  } //AST FINISHED
          | expression t_PLUS term  { $$ = new_expression ("+", $1, $3);    }
          | expression t_MINUS term { $$ = new_expression ("-", $1, $3);    }
          ;
term:       factor            { $$ = new_expression (" ", $1, NULL); } //AST FINISHED
          | term t_MUL factor { $$ = new_expression ("*", $1, $3);   }
          | term t_DIV factor { $$ = new_expression ("/", $1, $3);   }
          ;
factor:     t_IDENT 
            {
                int stl, sto, val;
                st.lookup($1, st_var | st_const,stl, sto);
                $$ = new_expression (" ", $1, NULL); //TODO
            } //nicht sicher
          | t_ZAHL                        { $$ = new_expression (" ", $1, NULL); }
          | t_PLUS factor                 { $$ = new_expression ("+", $2, NULL); }
          | t_MINUS factor                { $$ = new_expression ("C", $2, NULL); }
          | t_KLA_AUF expression t_KLA_ZU { $$ = $2; }
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