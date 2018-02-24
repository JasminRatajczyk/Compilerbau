#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"


/*************************** Block functions *************************************/
void block_output ( block b , int n){
    if ( b )
    {
        printf("%s", " " + n);
        
        if(b->constants) 
        {
            variable_output( b->constants, n+1 );
        }
        
        if(b->variables) 
        {
            variable_output( b->variables, n+1 );
        }
        
        if(b->blocks) 
        {
            block_output( b->blocks, n+1);
        }

        if(b->statements) 
        {
            statement_output( b->statements, n+1);
        }
    }
}

void block_code ( block p){
    if(p){
        if(p->constants){
            variable_code(p->constants);
        }
        if(p->variables){
            variable_code(p->variables);
        }
        if(p->statements){
            statement_code(p->statements);
        }
        if(p->blocks){
            block_code(p->blocks);
        }

        
    }
}

void block_free ( block p){
    if(p!=NULL){
        if(p->constants!=NULL)variable_free(p->constants);
        if(p->variables!=NULL)variable_free(p->variables);
        if(p->statements!=NULL)statement_free(p->statements);
        if(p->blocks)block_free(p->blocks);
        free(p);
    }
}
double block_result ( block b){
    if(b!=NULL){
        if(b->statements)statement_result(b->statements);
        if(b->blocks)block_result(b->blocks);
    }
}

block new_block (variable c, variable v, block b, statement s)
{
    block p = (block) malloc(sizeof(block_node));
    if (p != NULL)
    {
        p->constants = c;
        p->variables = v;
        p->blocks = b;
        p->statements = s;
    }

    return p;
}

/*************************** Statement functions *********************************/


void statement_output(statement p, int n){
    if(p){
        printf("%d", n);
        if(p->cond){
            switch(p->type){
                case stmnt_assign:                   
                    printf("Assign: %d %d %d", p->stl, p->sto, n); 
                    expression_output(p->cond, n+1);                     
                    break;
                case stmnt_read:
                    printf("Read: %d %d %d", p->stl, p->sto);
                    break;
                case stmnt_write:
                    printf("Write: %d %d", p->mem.getVal(p->stl, p->sto),n);
                    break;
                case stmnt_if:
                    printf("If: %d", n);
                    expression_output(p->cond, n+1);
                    if(p->next)statement_output(p->next, n+1);
                    break;
                case stmnt_while:
                    printf("While: %d", n);
                    expression_output(p->cond, n+1);
                    statement_output(p->next, n+1);
                    break;
                case stmnt_call:
                    break;
            }
        }
            
        
        if(p->next)statement_output(p->next, n+1);
            }
}

void statement_code(statement p){
    if(p){
        if(p->cond){
            switch(p->type){
                case stmnt_assign: 
                    expression_code(p->cond);
                    printf("Assign: %d %d", p->stl, p->sto);
                    break;
                case stmnt_read:
                    printf("Read: %d %d", p->stl, p->sto);
                    break;
                case stmnt_write:
                    printf("Write: %d", p->mem.getVal(p->stl, p->sto));
                    break;
                case stmnt_if:
                    expression_code(p->cond);
                    if(p->next)statement_code(p->next);
                    printf("If: ");
                    break;
                case stmnt_while:
                    expression_code(p->cond);
                    if(p->next)statement_code(p->next);
                    printf("While: ");
                    break;
                case stmnt_call:
                
                    break;
            }
        }
        
        if(p->next)statement_code(p->next);
    }
}

double statement_result (statement p)
{
    switch ( p->type )
    {
        case stmnt_assign:
            p->mem.setVal(p->stl, p->sto, expression_result(p->cond));
            break;
        case stmnt_read:
            int input;
            scanf("input: %d", input);
            p->mem.setVal(p->stl, p->sto, input);
            break;
        case stmnt_write:
            printf ("%d",expression_result( p->cond ));
            break;
        case stmnt_if:
            if (expression_result(p->cond))
            {
                statement_result(p->next, 0);
            }
            break;
        case stmnt_while:
            while (expression_result(p->cond))
            {
                statement_result(p->next, 0);
            }
            break;
        case stmnt_end:
            statement next = p;
            do
            {
                statement_result( next, 0 );
                next = next->next;
            } while (next->next);
            break;
        case stmnt_call:
            ////p->mem.ram_neusegment(p->stl, p->sto);
            //block_result() blabl
            //p->mem.ram_loeschsegemnt(p->stl, p->sto);
            break;
        default:
    }
}

void statement_free ( statement s){
    if(s->cond)expression_free(s->cond);
    if(s->next)statement_free(s->next);
    free(s);
}

statement new_statement (int t, int l, int o, statement st, expression ex, Memory* mem)
{
    statement p = (statement) malloc(sizeof(statement_node));
    if ( p != NULL )
    {
        p->type = t; 
        p->stl = l;
        p->sto = o; 
        p->next = st; 
        p->cond = ex;
    }
    return p;
}

/*************************  Variable functions  **********************************/

void variable_output(variable p, int n)
{
    if ( p )
    {
        printf("%s", " " + n);
        printf("%d %d %d\n", p->type, p->stl, p->sto);
        variable_output(p->next, n+1);
    }
}

void variable_code(variable p)
{
    if ( p )
    {
        variable_code(p->next);
        printf("%d %d %d\n", p->type, p->stl, p->sto);
    }
}

void variable_free(variable var)
{
    variable_free( var->next );
    free ( var );
}

variable new_variable(int type, int level, int offset, variable n)
{
    variable p = (variable) malloc (sizeof (variable_node));
    if ( p != NULL )
    {
        p->type = type;
        p->stl = level;
        p->sto = offset;
        p->next = n;
    }
    return p;
}



/************************* Expression functions **********************************/

void expression_output (expression p, int n)
{
    if ( p != NULL ) 
    {
        printf("%s", " " + n);
        printf("%s\n", p->text);
        expression_output(p->l, n+1);
        expression_output(p->r, n+1);
    }
}

void expression_code (expression p)
{
    if (p != NULL)
    {
        expression_code ( p->l );
        expression_code ( p->r );
        printf ( "%s\n", p->text );
    }
}

double expression_result (expression p)
{
    double erg;
    switch (p->text[0]) 
    {
        case  '+': erg =         expression_result ( p->l ) +  expression_result ( p->r ); break;
        case  '-': erg =         expression_result ( p->l ) -  expression_result ( p->r ); break;
        case  '/': erg =         expression_result ( p->l ) /  expression_result ( p->r ); break;
        case  '*': erg =         expression_result ( p->l ) *  expression_result ( p->r ); break;
        case  '=': erg =         expression_result ( p->l ) == expression_result ( p->r ); break;
        case  '#': erg =         expression_result ( p->l ) != expression_result ( p->r ); break;
        case  '>': erg =         expression_result ( p->l ) >  expression_result ( p->r ); break;
        case  '<': erg =         expression_result ( p->l ) <  expression_result ( p->r ); break;
        case '>=': erg =         expression_result ( p->l ) >= expression_result ( p->r ); break;
        case '<=': erg =         expression_result ( p->l ) <= expression_result ( p->r ); break;
        case  'O': erg =   (int) expression_result ( p->l ) %  2;                          break;
        case  'C': erg =       - expression_result ( p->l );                               break;
        case  'I': erg =         p->mem.getVal(p->stl, p->sto);                            break;
        default:   erg =         atof(p->text);
    }
    return erg;
}

void expression_free (expression p)
{
    if ( p != NULL )
    {
        expression_free ( p->l );
        expression_free ( p->r );
        free ( p );
    }
}

expression new_expression ( char *t, expression l, expression r, Memory* mem )
{
    expression p = (expression) malloc (sizeof (expression_node));
    if ( p != NULL )
    {
        p->l = l, p->r = r;
        strcpy ( p->text, t );
    }
    return p;
}

expression new_expression ( char *t, expression l, expression r, Memory* mem, int sto, int stl)
{
    expression p = (expression) malloc (sizeof (expression_node));
    if ( p != NULL )
    {
        p->l = l, p->r = r;
        p->stl = stl;
        p->sto = sto;
        strcpy ( p->text, t );
    }
    return p;
}