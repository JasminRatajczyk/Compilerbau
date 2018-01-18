#pragma once

enum { st_var = 1, st_const = 2, st_proc = 4 };

class Symtab_entry
{
public:
	Symtab_entry(const int type, const int nr, const int val = 0) : type(type),
																	nr(nr),
																	val(val)
	{}

	int getType() { return type; };
	int getNr() { return nr; };
	int getVal() { return val; };
	void setVal(int nval) { val = nval; };

private:
	int type;
	int nr;
	int val;
};