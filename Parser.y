%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Symtab/Symtab.hpp"
#include "Ast/Ast.h"
#include "Memory/Memory.hpp"
#include "ProcList/ProcList.hpp"

void yyerror(const char* s);
int yylex();
int yyparse();

extern FILE* yyin;

Symtab st;
Memory* mem = new Memory();
ProcList* procList = new ProcList();
block root;

int level = -1, offset = -1;

%}

%token t_PLUS t_MINUS t_MUL t_DIV t_KLA_AUF t_KLA_ZU
       t_ODD t_EQUAL t_NEQUAL t_LESS t_LEQUAL t_GREATER
       t_GREQUAL t_COMMA t_SEMICOLON t_PERIOD t_ASSIGN
       t_BEGIN t_END t_IF t_THEN t_WHILE t_DO
       t_CALL t_PROCEDURE t_CONST t_VAR t_READ t_WRITE

%union 
{ 
    char       _ident[100]; 
    int        _int; 
    block      _block; 
    statement  _statement;
    variable   _variable;
    expression _expression; 
}

%token<_int>   t_ZAHL
%token<_ident> t_IDENT

%type <_ident> relop
%type <_block> block procdeclare
%type <_statement> statement anotherStatement
%type <_variable> vardeclare anothervardeclare constdeclare anotherconstdeclare
%type <_expression> expression term factor condition
%%

program: block t_PERIOD {root = $1;} ;

block: { st.level_up(); } constdeclare vardeclare procdeclare statement
{
    if ( $5 != NULL)
    {
        $$ = new_block($2, $3, $4, $5); 
    }
    else
    {
        $$ = NULL;
    }

    st.level_down();    
    printf("BlockRule\n");
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
                  printf("constdeclare.\n");
              }
              | 
              { 
                  $$ = NULL;
                  printf("EmptyConstDeclare.\n");
              }
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
                         printf("anotherconstdeclare\n");
                     }
                     | 
                     { 
                         $$ = NULL; 
                         printf("emptyAnotherConstdeclare\n");
                     } /*empty*/
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
                printf("Vardeclare\n");
            }
            | { $$ = NULL; 
                printf("EmptyVardeclare\n");
              } /*empty*/
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
                        printf("anothervardeclare\n");
                    }
                  | { $$ = NULL; 
                      printf("EmptyAnotherVardeclare\n");
                    } /* empty*/
                  ;

procdeclare: t_PROCEDURE t_IDENT
             {
                 st.insert ( $<_ident>2, st_proc );
                 st.lookup ( $<_ident>2, st_proc, level, offset );
             }
             t_SEMICOLON block t_SEMICOLON procdeclare
             {
                $$ = $5;
                printf("Procdeclare\n");
                if(st.get_procnr($2) > -1)
                {
                    procList->addProc(st.get_procnr($2), $5);
                }
                else
                {
                    yyerror("ERR: procedure not found:");
                }
             }
           | { $$ = NULL; 
               printf("EmptyProcdeclare\n");
             }
		   ;

statement: t_IDENT t_ASSIGN expression
         {
            int sto, stl;
            st.lookup($1, st_var, sto, stl );
            $$ = new_statement ( stmnt_assign, stl, sto, NULL, $3, mem, NULL, NULL);
            printf("assignstatement");
         }
         | t_CALL t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_proc, sto, stl );
            if(st.get_procnr($2)>-1){
            block b = procList->getProc(st.get_procnr($2));

            $$ = new_statement (stmnt_call, sto, stl, NULL, NULL, mem, b, NULL);
            printf("callstatement\n");
            }else yyerror("No such function");
         }
         | t_BEGIN statement anotherStatement t_END
         {
            if($2!=NULL && $3==NULL)
            {
                $$=$2;
            }
            else 
            {
                if ($2 != NULL && $3 != NULL) 
                {
                    $2->follow = $3;
                    $$ = $2;                
                }
                else 
                {
                    $$ = NULL;
                }
            }
            printf("BeginStatement\n");
         }
         | t_IF condition t_THEN statement
         {
            $$ = new_statement ( stmnt_if, -1, -1, $4, $2, mem, NULL, NULL);
            printf("IfStatement\n");
         }
         | t_WHILE condition t_DO statement
         {
            $$ = new_statement ( stmnt_while, -1, -1, $4, $2, mem, NULL, NULL);
            printf("WhileStatement\n");
         }
         | t_READ t_IDENT
         {
            int sto, stl;
            st.lookup($2, st_var, sto, stl );
            $$ = new_statement ( stmnt_read, stl, sto, NULL, NULL, mem, NULL, NULL);
            printf("ReadStatement");
         }
         | t_WRITE expression
         {            
            if ($2)
            {
                $$ = new_statement ( stmnt_write, -1, -1, NULL, $2, mem, NULL, NULL);
            }
            else
            {              
                $$ = NULL;
            }
            printf("Write");
         }
         | { $$ = NULL; 
             printf("EmptyStatement");
           }
         ;

anotherStatement: t_SEMICOLON statement anotherStatement
		        {
                    if ($2 != NULL)
                    {                    
                        $$ = $2;
                        
                        if($3 != NULL)
                        {
                            $$->follow = $3;
                        }
                    }
                    else
                    {
                        $$ = NULL;
                    }
                    printf("AnotherStatement\n");
                }
                | { $$ = NULL; 
                    printf("EmptyAnotherStatement\n");
                  } 
		        ;

condition: t_ODD expression
         {
             char buffer[100];
              snprintf(buffer, sizeof(buffer), "ODD");
             $$ = new_expression (buffer, $2, NULL, mem);
             printf("OddCondition\n");
         }
         | expression relop expression
         {
             $$ = new_expression ($2, $1, $3, mem);
             printf("RelopCondition");
         }
         ;

relop: t_EQUAL   
     { 
         snprintf($$, 9, "="); 
         printf("EqualRelop\n" );
     }
     | t_NEQUAL  
     { 
         snprintf($$, 9, "#"); 
         printf("NequalRelop\n");
     } 
     | t_GREATER 
     { 
         snprintf($$, 9, ">"); 
         printf("GreaterRelop\n");
     }
     | t_LESS    
     { 
        snprintf($$, 9, "<"); 
        printf("LessRelop\n");
     }
     | t_GREQUAL 
     { 
        snprintf($$, 9, "|"); 
        printf("GrequalRelop\n");
     }
     | t_LEQUAL  
     {         
        snprintf($$, 9, "."); 
        printf("LequalRelop\n");
     }
     ;

expression: term
          {
              $$ = $1; 
          }
          | expression t_PLUS term  
          { 
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "+");
              
              $$ = new_expression (buffer, $1,   $3, mem); 
              printf("PlusExpression \n");  
          }
          | expression t_MINUS term 
          { 
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "-");

              $$ = new_expression (buffer, $1, $3, mem); 
              printf("MinusExpression\n");  
          }
          ;
term:     factor            
          { 
              $$ = $1;
          }
          | term t_MUL factor 
          { 
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "*");
              $$ = new_expression (buffer, $1,   $3, mem); printf("MultTerm\n");
          }
          | term t_DIV factor 
          { 
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "/");  
              $$ = new_expression (buffer, $1, $3, mem); printf("DivTerm\n");
          }
          ;
factor:   t_IDENT 
          {
              int stl, sto, val;
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "I");
              
              st.lookup($1, st_var | st_const,stl, sto);
              
              $$ = new_expression (buffer, NULL, NULL, mem, stl, sto);
                
              printf("IdentFactor");
          }
          | t_ZAHL
          {
              char temp[10];
              sprintf(temp, "%i", $1);
              $$ = new_expression (temp, NULL, NULL, mem);
              printf("ZahlFactor\n");
          }
          | t_PLUS factor
          {
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "+");
              $$ = new_expression (buffer, $2, NULL, mem);
              printf("PlusFactor\n");
          }
          | t_MINUS factor
          { 
              char buffer[100];
              snprintf(buffer, sizeof(buffer), "C");
              $$ = new_expression (buffer, $2, NULL, mem);
              printf("IdentFactor\n");
          }
          | t_KLA_AUF expression t_KLA_ZU { $$ = $2; printf("KlammerExpression\n");}
          ;
%%
int main(int argc, char** argv)
{
    ++argv; --argc;
    if(argc > 0)
    {
        yyin = fopen(argv[0], "r");
    }
    else
    {
        yyin = stdin;
    }

    int rc = yyparse();
    fclose(yyin);

    if (rc == 0)
    {
        if(root){
            int n = 0;
            if(root->constants!=NULL){
                n++;
                variable c = root->constants;
                while(c->next!=NULL){
                    c=c->next;
                    n++;
                }
            }
            if(root->variables!=NULL){
                n++;
                variable v = root->variables;
                while(v->next!=NULL){
                    v = v->next;
                    n++;
                }
            }
            //printf("%d %d\n", n, p->stl);
            mem->ram_neusegment(n, 1);

            printf("\n Output: \n");
            block_output(root,0);
            printf("\n Tree: \n");
            block_result(root);
            mem->ram_loeschsegment();
        }
        else{
            printf("\n Output: empty\n");
            printf("\n Tree: empty\n");
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