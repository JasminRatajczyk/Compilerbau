#ifndef __TERM_TREE_H__
#define __TERM_TREE_H__ 1

#include "Ast.h"
#include "y.tab.h"

void f_init();
ast f_start();
ast f_block();
ast f_var();
ast f_statement();
ast f_factor();
ast f_expression();
ast f_term();

char zahl[20];
int token, error;

#endif