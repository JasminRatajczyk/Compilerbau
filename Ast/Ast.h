#ifndef __TERM_TREE_H__
#define __TERM_TREE_H__ 1

typedef struct s_node * ast;
typedef struct s_node ast_node;

struct ast
{
    char text[10];
    struct ast l;
    struct ast r;
};

/*
struct ast_node
{
	int type;   // Befehl
	int stl;    //Level der Symboltabellen fuer assign und read
	int sto;	//Offset '='
	struct ast_node * next; //Naechster Befehl
	struct ast_node * cond;	//Abhaengige Kette fuer if und while
};
*/

//Prototypen
void tree_output ( ast , int );
void tree_code ( ast );
void tree_free ( ast );
int tree_result ( ast );
ast new_node ( char *, ast, ast, ast );
#endif