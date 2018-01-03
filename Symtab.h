#pragma once

#include "symtab_entry.h"
#include<string>
#include<map>

class Symtab
{
public:
	Symtab();
	void level_up();
	void level_down();
	int insert(const std::string name, const int type, const int var);
	int lookup(std::string name, int type, int &l, int &o, int value);
	void print();
	int get_procnr();
	int get_procnr(std::string name);
private:
	std::map<std::string, symtab_entry> m_content[10];
	int m_level;
	int m_procnr;
};