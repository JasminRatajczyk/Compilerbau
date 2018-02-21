#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"
#include "../Memory/Memory.hpp"

Memory mem;

/*************************** Block functions *************************************/

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

double statement_result (statement p)
{
    switch ( p->type )
    {
        case stmnt_assign:

            //TODO Speicherverwaltung Wert zuweisen
            break;
        case stmnt_read:
            int input;
            scanf("input: %d", input);
            //TODO Speicherverwaltung Wert einspeichern
            mem.RAM.at(mem.getAdress(p->stl, p->sto))= input;
            break;
        case stmnt_write:
            printf ("%d", expression_result( p->cond ));
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
            //TODO: find out what Bantel was thinking (Mission impossible)
            statement next = p;
            do
            {
                statement_result( next, 0 );
                next = next->next;
            } while (next->next);

            break;
        case stmnt_call:
            
            break;
        default:
    }
}

statement new_statement (int t, int l, int o, statement st, expression ex)
{
    statement p = (statement) malloc(sizeof(statement_node));
    if ( p != NULL )
    {
        p->type = t; 
        p->stl = l;
        p->sto = o; 
        p->next = st; 
        p->next = ex;
    }
    return p;
}
/*************************  Variable functions  **********************************/

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

void variable_free(variable var)
{
    variable_free( var->next );
    free ( var );
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

expression new_expression ( char *t, expression l, expression r )
{
    expression p = (expression) malloc (sizeof (expression_node));
    if ( p != NULL )
    {
        p->l = l, p->r = r;
        strcpy ( p->text, t );
    }
    return p;
}