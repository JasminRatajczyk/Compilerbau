#include<stdio.h>
#include<stdlib.h>
#include "symtab_entry.h"

class symtab
{

public :
	symtab();
	void level_up();
	void level_down();
	int insert(const string name, const int typ, const int var);
	int lookup(string name, int type, int &l, int &o, int blaaa);
	void print();
	int get_procnr(){return procnr};
	int get_procnr(string name);
private :
	map<string, sysmtab_entry> content[10];
	int level;
	int procnr;
};