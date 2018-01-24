#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"

void tree_output(ast p, int n)
{
    if (p != NULL) 
    {
        printf("%s", " " + n);
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

int tree_result(ast p)
{
    int erg;
    switch (p->text[0]) 
    {
        case '+': erg = tree_result(p->l) + tree_result(p->r); break;
        case '-': erg = tree_result(p->l) - tree_result(p->r); break;
        case '*': erg = tree_result(p->l) * tree_result(p->r); break;
        case '/': erg = tree_result(p->l) / tree_result(p->r); break;
        case 'C': erg = - tree_result(p->l);                   break;
        default:  erg = atof(p->text);
    }
    return erg;
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