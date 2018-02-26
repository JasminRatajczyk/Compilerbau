#ifndef __PL_TREE_H__
#define __PL_TREE_H__ 1

#include "../Memory/Memory.hpp"
#include "../ProcList/ProcList.hpp"

//forward declaration
class ProcList;

typedef struct b_node * block;
typedef struct b_node block_node;

typedef struct s_node * statement;
typedef struct s_node statement_node;

typedef struct v_node * variable;
typedef struct v_node variable_node;

typedef struct e_node * expression;
typedef struct e_node expression_node;

enum //different types of statements
{
	stmnt_write = 0, stmnt_read, stmnt_assign, 
	stmnt_if, stmnt_while, stmnt_call
};

struct b_node
{
	variable  constants;
	variable  variables;
	block     blocks;
	statement statements;
	char* name[100];
};

struct s_node // used for all kinds of statements
{
	int type;   //Befehl
	int stl;    //Level der Symboltabellen fuer assign und read
	int sto;	//Offset der Symboltabellen fuer assign und read
	statement  follow; //Neachster Befehl
	statement  next; //Auszufuehrender Befehl wenn Bedingung erfuellt
	expression cond; //Abhaengige Kette fuer if und while
	Memory* mem;
	block b;
};

struct v_node //used for variable and const
{
	int type;
	int stl;
	int sto;
	variable next;
};

struct e_node //expression, factor, term
{
    char text[10];
    expression l;
    expression r;
	int sto;
	int stl;
	Memory* mem;
};

//BLOCK
void block_output ( block , int );
void block_code ( block );
void block_free ( block );
double block_result ( block );
block new_block ( variable, variable, block, statement);
block new_block ( variable, variable, block, statement, char*, int, int);

//STATEMENT
void statement_output ( statement , int );
void statement_code ( statement );
void statement_free ( statement );
double statement_result ( statement );
statement new_statement (int, int, int, statement, expression, Memory*, block, statement );

//VARIABLE
void variable_output ( variable , int );
void variable_code ( variable );
void variable_free ( variable );
variable new_variable (int, int, int, variable);

//EXPRESSION
void expression_output ( expression , int );
void expression_code ( expression );
void expression_free ( expression );
double expression_result ( expression );
expression new_expression ( char *, expression, expression, Memory*  );
expression new_expression ( char *, expression, expression, Memory*, int, int );

#endif