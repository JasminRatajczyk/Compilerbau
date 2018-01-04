#ifndef __TERM_TREE_H__
#define __TERM_TREE_H__ 1
typedef struct s_node * Ast;
typedef struct s_node ast_node;

struct s_node
{
    char text[10];
    Ast l;
    Ast r;
};

//Prototypen
void tree_output(Ast , int);
void tree_free(Ast );
void tree_code(Ast );
double tree_result(Ast );
Ast new_node(char *, Ast, Ast, Ast);
#endif