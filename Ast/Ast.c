#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"

/*************************** Block functions *************************************/

void block_output ( block b , int n ){
    if ( b!=NULL )
    {
        
        printf("%d\n", n);
        
        if(b->constants!=NULL) 
        {
            variable_output( b->constants, n+1 );
        }
        
        if(b->variables!=NULL) 
        {
            variable_output( b->variables, n+1 );
        }
        
        if(b->blocks!=NULL) 
        {
            block_output( b->blocks, n+1);
        }

        if(b->statements!=NULL) 
        {
            statement_output( b->statements, n+1);
        }
        printf("block_output\n");
    }
}

void block_code ( block p ){
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
        printf("block_code\n");
    }
}

void block_free ( block p ){
    if( p ){
        
        if(p->constants)
        {
            variable_free(p->constants);
        }
        
        if(p->variables)
        {
            variable_free(p->variables);
        }
        
        if(p->statements)
        {
            statement_free(p->statements);
        }

        if(p->blocks)
        {
            block_free(p->blocks);
        }

        free(p);
        printf("block_free\n");
    }
}

double block_result (block b){
    if(b!=NULL){
        if(b->statements!=NULL)
        {
            statement_result(b->statements);
        }
    }
}

block new_block (variable c, variable v, block b, statement s)
{
    block p = (block) malloc(sizeof(block_node));
    
    if (c!=NULL)
    {
        p->constants = c;
    }

    if (v!=NULL)
    {
        p->variables = v;
    }
    
    if(b!=NULL)
    {
        p->blocks = b;
    }

    if(s!=NULL)
    {
        p->statements = s;
    }
    printf("new_block\n");
    return p;
}

/*************************** Statement functions *********************************/


void statement_output(statement p, int n)
{
    if(p)
    {
        printf("%d", n);
        if(p->cond)
        {
            switch(p->type)
            {
                case stmnt_assign:
                {
                    if (p->stl >= 0 && p->sto >= 0 && p->cond)
                    {
                        printf("Assign: %d %d %d \n", p->stl, p->sto, n); 
                        expression_output(p->cond, n+1);                     
                    }
                    break;
                }
                case stmnt_read:
                {
                    printf("Read: %d %d %d \n", p->stl, p->sto,n);
                    break;
                }
                case stmnt_write:
                {
                    printf("Write: %d %d \n", p->mem->getVal(p->stl, p->sto),n);
                    break;
                }
                case stmnt_if:
                {
                    printf("If: %d \n", n);
                    expression_output(p->cond, n+1);
                    if(p->next)statement_output(p->next, n+1);
                    break;
                }
                case stmnt_while:
                {
                    printf("While: %d \n", n);
                    expression_output(p->cond, n+1);
                    statement_output(p->next, n+1);
                    break;
                }
                case stmnt_call:
                { 
                    break;
                }
            }
        }
        if(p->next){
            statement_output(p->next, n+1);
        }
        printf("statement_output\n");
    }
}

void statement_code(statement p){
    if(p){
        if(p->cond){
            switch(p->type){
                case stmnt_assign: 
                    expression_code(p->cond);
                    printf("Assign: %d %d \n", p->stl, p->sto);
                    break;
                case stmnt_read:
                    printf("Read: %d %d \n", p->stl, p->sto);
                    break;
                case stmnt_write:
                    printf("Write: %d \n", p->mem->getVal(p->stl, p->sto));
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
            printf("statement_code\n");
        }
        
        if(p->next)statement_code(p->next);
    }
}

void statement_free ( statement s){
    if(s->cond)expression_free(s->cond);
    if(s->next)statement_free(s->next);
    free(s);
    printf("statement_free\n");
}

double statement_result (statement p)
{   
    printf("X type: %d\n", p->type);
    if(p->follow)
    {
        printf("Found Follow\n");
    }
    else
    {
        printf("No Follow\n");
    }
    switch ( p->type )
    {
        case stmnt_assign:
        {
            if(p->cond){
                p->mem->setVal(p->stl, p->sto, expression_result(p->cond));
                int i= p->mem->getVal(p->stl, p->sto);
                printf("Value: %d \n",i);
            }
            break;
        }
        case stmnt_read:
        {
            int input;
            printf("input: "); 
            scanf("%d", &input);
            p->mem->setVal(p->stl, p->sto, input);
            break;
        }
        case stmnt_write:
        {
            if(p->cond){
                printf ("%f \n",expression_result( p->cond ));
            }
            break;
        }
        case stmnt_if:
        {
            if(p->cond){
                if (expression_result(p->cond))
                {
                    if(p->next) statement_result(p->next);
                }
            }
            break;
        }
        case stmnt_while:
        {
            if(p->cond){
                while (expression_result(p->cond))
                {
                    if(p->next) statement_result(p->next);
                }
            }else printf("While has no cond\n");
            break;
        }
        case stmnt_call:
        {
             if(p->b){
                block b = p->b;
                int n =0;
                if(b->constants!=NULL){
                    n++;
                    variable c = b->constants;
                    while(c->next!=NULL){
                         c=c->next;
                         n++;
                    }
                }
                
                if(b->variables!=NULL){
                    n++;
                    variable c = b->variables;
                    while(c->next!=NULL){
                         c=c->next;
                         n++;
                    }
                }
                printf("RAM: %d %d\n", n, p->stl);
                
                p->mem->ram_neusegment(n, p->stl);
                block_result(b);
                p->mem->ram_loeschsegment();
            }
            else printf("The function does not exist\n");            
            break;
        }
        printf("statement_result: %d\n", p->type);
    }

    if(p->follow) {
        statement_result(p->follow);
    }    
}

statement new_statement (int t, int l, int o, statement st, expression ex, Memory* mem, block b, statement f)
{
    statement p = (statement) malloc(sizeof(statement_node));
    if ( p != NULL )
    {
        p->type = t; 
        p->stl = l;
        p->sto = o; 
        p->next = st; 
        p->cond = ex;
        p->mem = mem;
        p->b = b;
        p->follow = f;
        printf("Statement erstellt\n");
    }
    return p;
}

/*************************  Variable functions  **********************************/

void variable_output(variable p, int n)
{
    if ( p )
    {
        printf("%d\n",  n);
        //printf("Das war variable n\n");
        printf("%d %d %d\n", p->type, p->stl, p->sto);
        if(p->next)variable_output(p->next, n+1);
        printf("variable output\n");
    }
}

void variable_code(variable p)
{
    if ( p )
    {
       if(p->next) variable_code(p->next);
        printf("%d %d %d\n", p->type, p->stl, p->sto);
        printf("variable_code\n");
    }
}

void variable_free(variable var)
{
   if(var->next) variable_free( var->next );
    free ( var );
    printf("variable_free\n");
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
    printf("variable erstellt\n");
    return p;
}

/************************* Expression functions **********************************/

void expression_output (expression p, int n)
{
    if ( p != NULL ) 
    {
        printf("%s \n", " " + n);
        printf("%s\n", p->text);
        expression_output(p->l, n+1);
        expression_output(p->r, n+1);
        printf("expression_output\n");
    }
}

void expression_code (expression p)
{
    if (p != NULL)
    {
        expression_code ( p->l );
        expression_code ( p->r );
        printf ( "%s\n", p->text );
        printf("expression_code\n");
    }
}

void expression_free (expression p)
{
    if ( p != NULL )
    {
        expression_free ( p->l );
        expression_free ( p->r );
        free ( p );
        printf("expression_free\n");
    }
}

double expression_result (expression p)
{

    double erg, first, second;
    int v; 
    
    if(p->stl>=0 && p->sto>=0)
    {

       v = p->mem->getVal(p->stl, p->sto);
    }

    printf("V %d\n", v);


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
        case  '|': erg =         expression_result ( p->l ) >= expression_result ( p->r ); break;
        case  '.': erg =         expression_result ( p->l ) <= expression_result ( p->r ); break;
        case  'O': erg =   (int) expression_result ( p->l ) %  2;                          break;
        case  'C': erg =       - expression_result ( p->l );                               break;
        case  'I': erg =         v; printf("%d\n",v);                                      break;
        default:   erg =         atof(p->text); printf("expression_result: Erg lautet %f und text %s\n", erg, p->text);
    }    
    return erg;
}

expression new_expression ( char *t, expression l, expression r, Memory* mem )
{
    expression p = (expression) malloc (sizeof (expression_node));

    if(l)
    {   
        p->l = l;
    }
    
    if(r)
    {
        p->r = r;
    }
    
    if(t)
    {
        if(!p->text) {
        strncpy(p->text, t, 9);
        printf("\n!\n!p-> %s\n!\n", p->text);
        printf("\n!\n!p-> %s\n!\n", t);
        }else printf("ERR: No name inserted\n");
    }
    
    if(mem)
    {
        p->mem = mem;
    }
    
    printf("Expression erstellt\n");
   
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
        printf("Expression erstellt mit sto und stl\n");
    }
    return p;
}