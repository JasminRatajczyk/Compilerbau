#include<stdio.h>
#include<stdlib.h>
#include "symtab_entry.h"

class symtab
{

public :
	symtab();
	void level_up();
	void level_down();
	int insert(const std::string name, const int type, const int var);
	int lookup(std::string name, int type, int &l, int &o, int blaaa);
	void print();
	int get_procnr(){return procnr};
	int get_procnr(std::string name);
private :
	map<std::string, symtab_entry> content[10];
	int level;
	int procnr;
};