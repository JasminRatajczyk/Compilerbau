%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Symtab/Symtab.hpp"
#include "Ast/Ast.h"
#include "Memory/Memory.hpp"

void yyerror(const char* s);
int yylex();
int yyparse();

Symtab st;
Memory* mem = new Memory();
block root;
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

%type <_ident> relop
%type <_block> block procdeclare
%type <_statement> statement anotherStatement
%type <_variable> vardeclare anothervardeclare constdeclare anotherconstdeclare
%type <_expression> expression term factor condition
%%

program: block t_PERIOD {root = $1};

block:
{ 
    st.level_up();
}
constdeclare vardeclare procdeclare statement
{ 
    $$ = new_block($2, $3, $4, $5); 
    st.level_down(); 
}
;

constdeclare: t_CONST t_IDENT t_EQUAL t_ZAHL
              { 
                  int stl, sto;
                  st.insert ( $<_ident>2 , st_const );
              }
              anotherconstdeclare t_SEMICOLON
              {
                  int stl, sto;
                  st.lookup($2, st_const, stl, sto);
                  $$ = new_variable(st_const, stl, sto, $6);
              }
              | { $$ = NULL;} /*empty*/
              ;

anotherconstdeclare: t_COMMA t_IDENT t_EQUAL t_ZAHL
                     { 
                         int stl, sto;
                         st.insert ( $<_ident>2 , st_const );
                     } 
                     anotherconstdeclare 
                     { 
                         int stl, sto;
                         st.lookup($2, st_const, stl, sto);
                         $$ = new_variable(st_const, stl, sto, $6);
                     }
                   | { $$ = NULL; } /*empty*/
                   ;

vardeclare: t_VAR t_IDENT
            {
                int stl, sto;
                st.insert ( $<_ident>2, st_var ); 
            }
            anothervardeclare t_SEMICOLON
            { 
                int stl, sto;
                st.lookup ( $2, st_var, stl, sto );
                $$ = new_variable ( st_var, stl, sto, $4 ); 
            }
            | { $$ = NULL; } /*empty*/
            ;

anothervardeclare:  t_COMMA t_IDENT 
                    {    
                        int stl, sto;
                        st.insert ( $<_ident>2, st_var );
                    }
                    anothervardeclare 
                    {
                        int stl, sto;
                        st.lookup ( $2, st_var, stl, sto );
                        $$ = new_variable ( st_var, stl, sto, $4 );
                    }
                  | { $$ = NULL; } /* empty*/
                  ;

procdeclare: t_PROCEDURE t_IDENT
             { 
                 st.insert ( $<_ident>2, st_proc ); 
             }
             t_SEMICOLON block t_SEMICOLON procdeclare
             {
                 $$ = $5;
             }
           | { $$ = NULL; } /*empty*/
		   ;

statement: t_IDENT t_ASSIGN expression
         {
            int sto, stl;
            st.lookup($1, st_var, sto, stl );
            $$ = new_statement ( stmnt_assign, stl, sto, NULL, $3, mem );
         }
         | t_CALL t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_proc, sto, stl );

            $$ = new_statement (stmnt_call, sto, stl, NULL, NULL, mem ); //TODO
         }
         | t_BEGIN statement anotherStatement t_END
         {
             if ($2) {
                $2->next = $3;
                $$ = $2;
             }
         }
         | t_IF condition t_THEN statement
         {
            $$ = new_statement ( stmnt_if, -1, -1,  $4, $2, mem);
         }
         | t_WHILE condition t_DO statement
         {
            $$ = new_statement ( stmnt_while, -1, -1, $4, $2, mem);
         }
         | t_READ t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_var, sto, stl );
            $$ = new_statement ( stmnt_read, stl, sto, NULL, NULL, mem);
         }
         | t_WRITE expression
         {
            $$ = new_statement ( stmnt_write, -1, -1, NULL, $2, mem);
         }
         | { $$ = NULL; } /* empty */
         ;

anotherStatement: t_SEMICOLON statement anotherStatement //AST FINISHED
		        {
                    $$ = $2;
                    $$->next = $3;
                }
                | { $$ = NULL;} /*empty*/
		        ;

condition: t_ODD expression //AST FINISHED
         {
             $$ = new_expression ((char*)"ODD", $2, NULL, mem);
         }
         | expression relop expression
         {
             $$ = new_expression ($2, $1, $3, mem);
         }
         ;

relop: t_EQUAL   { strncpy($$, "=",  sizeof($$) ); } //AST FINISHED
     | t_NEQUAL  { strncpy($$, "#",  sizeof($$) ); } 
     | t_GREATER { strncpy($$, ">",  sizeof($$) ); }
     | t_LESS    { strncpy($$, "<",  sizeof($$) ); }
     | t_GREQUAL { strncpy($$, ">=", sizeof($$) ); }
     | t_LEQUAL  { strncpy($$, "<=", sizeof($$) ); }
     ;

expression: term                    { $$ = new_expression ((char*)" ", $1, NULL, mem);  } //AST FINISHED
          | expression t_PLUS term  { $$ = new_expression ((char*)"+", $1, $3, mem);    }
          | expression t_MINUS term { $$ = new_expression ((char*)"-", $1, $3, mem);    }
          ;
term:       factor            { $$ = new_expression ((char*)" ", $1, NULL, mem); } //AST FINISHED
          | term t_MUL factor { $$ = new_expression ((char*)"*", $1, $3, mem);   }
          | term t_DIV factor { $$ = new_expression ((char*)"/", $1, $3, mem);   }
          ;
factor:     t_IDENT 
            {
                int stl, sto, val;
                st.lookup($1, st_var | st_const,stl, sto);
                $$ = new_expression ((char*)"I", NULL, NULL, mem, stl, sto);
            }
          | t_ZAHL                        { $$ = new_expression ((char*) t_ZAHL, NULL, NULL, mem); }
          | t_PLUS factor                 { $$ = new_expression ((char*)"+", $2, NULL, mem); }
          | t_MINUS factor                { $$ = new_expression ((char*)"C", $2, NULL, mem); }
          | t_KLA_AUF expression t_KLA_ZU { $$ = $2; }
          ;

%%
int main()
{
    int rc = yyparse();
    
    if (rc == 0)
    {
        if(root){
            printf("Output: \n");
            block_output(root);
            printf("Tree: \n");
            block_result(root);
        }
        else{
            printf("Output: empty\n");
            printf("Tree: empty\n");
        }
        printf("\n Program executed Successfully!\n");
    }
    else
    {
        printf("\n Program has been stopped!\n");
    }
    if(root)block_free(root);
    return 0;
}

void yyerror(const char *s)
{
    printf("%s", s);
    exit(1);
}