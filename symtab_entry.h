#pragma once
#include <stdio.h>
#include <stdlib.h>

enum { st_var = 1, st_const = 2, st_proc = 4 };

class symtab_entry
{
public:
	symtab_entry(const int type = 0, const int nr = 0, const int val = 0) : type(type),
																			nr(nr),
																			val(val)
	{}

	int getType() { return type; };
	int getNr() { return nr; };
	int getVal() { return val; };

private:
	int type;
	int nr;
	int val;
};