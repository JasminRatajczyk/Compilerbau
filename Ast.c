#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "Ast.h"

void tree_output(ast p, int n)
{
    if (p != NULL) 
    {
        printf("%s", " " + 14-2*n);
        printf("%s\n", p->text);
        tree_output(p->l, n+1);
        tree_output(p->r, n+1);
    }
}

void tree_code(ast p)
{
    if (p != NULL)
    {
        tree_code(p->l);
        tree_code(p->r);
        printf("%s\n", p->text);
    }
}

double tree_result(ast p)
{
    double erg;
    switch (p->text[0]) 
    {
        case '+': erg = tree_result(p->l) + tree_result(p->r); break;
        case '-': erg = tree_result(p->l) + tree_result(p->r); break;
        case '*': erg = tree_result(p->l) + tree_result(p->r); break;
        case '/': erg = tree_result(p->l) + tree_result(p->r); break;
        case 'C': erg = tree_result(p->l) + tree_result(p->r); break;
    }
    return erg;
}

ast new_node(char *t, ast l, ast r)
{
    ast p = (ast) malloc(sizeof(ast_node));
    if (p != NULL)
    {
        p->l = l, p->r = r;
        strcpy(p->text, t);
    }
    return p;
}

void tree_free(ast p)
{
    if (p != NULL)
    {
        tree_free(p->l);
        tree_free(p->r);
        free(p);
    }
}