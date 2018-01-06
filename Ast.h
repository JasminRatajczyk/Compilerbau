#ifndef __TERM_TREE_H__
#define __TERM_TREE_H__ 1
typedef struct s_node * ast;
typedef struct s_node ast_node;

struct s_node
{
    char text[10];
    ast l;
    ast r;
};

struct ast_node
{
	int type;  // Befehl
	int stl;	//Level der Symboltabellen für assign und read
	int sto;	//Offset '='
	struct ast_node * next;  //Nächster Befehl
	struct ast_node * cond;		//Abhängige Kette für if und while
};

//Prototypen
void tree_output(ast , int);
void tree_free(ast );
void tree_code(ast );
double tree_result(ast );
ast new_node(char *, ast, ast, ast);



	
};
#endif