#include <stdio.h>
#include<stdlib,h>

enum{st_var = 1, st_const =2 , st_proc = 4};

class symtab_entry
{
	public: 
		symtab_entry(const int = 0, const int = 0, const int = 0);
	int type;
	int nr;
	int val;
};