#include <stdio.h>
#include "AstGenerator.h"


ast f_start()
{
	scanner(), error = 0;
	ast p = f_expression();
	if(token != END)
	{
		error = 3;
	}
	return p;
}

ast f_block()
{
	ast p, p2, p3;
	int token2;
	scanner();
	
	if (token == INT)
	{
		p = f_var();
		scanner();
	}
	
	if (token == BEGINSYM)
	{
		p2 = f_block();
		scanner();
	}

	while (token == PROCEDURE)
	{
		token2 = token;
		p3 = new_node((token2 == PROCEDURE));
		scanner();
	}
}

ast f_var()
{
	ast p = f_var();
	scanner();
}

ast f_statement()
{
	scanner();
}

ast f_expression()
{
	ast p;
	int token2;
	p = f_term();
	while (token == PLUS || token == MINUS)
	{
		token2 = token;
		scanner();
		p = new_node((token2 == PLUS)? "+" : "-", p, f_term());
	}
	return p;	
}

ast f_term()
{
	ast p;
	char * txt;
	p= f_factor();
	while(token == MUL || token == DIV)
	{
		txt = (token == MUL)? "*" : "/";
		scanner();
		p= new_node(txt, p, f_factor(),);
	}
	return p;
}

ast f_factor()
{
	ast p;
	if(token == PLUS)
	{
		scanner();
		p= f_factor();
	} 
	else if ((token == MINUS)
	{
		scanner();
		p = new_node("C", f_factor(), NULL);
	}
	else if(token == ZAHL)
	{
		p= new_node(zahl, NULL, NULL);
		scanner();	
	}
	else if(token == KLA_AUF)
	{
		scanner();
		p= f_expression();
		if(token == KLA_ZU)
		{
			scanner();
		}
		else 
		{
			error = 1;
		}
	}
	else 
	{
		error = 2;
	}

	return p;
}