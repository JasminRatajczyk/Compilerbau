#pragma once

#include "Symtab_entry.h"
#include<string>
#include<map>

class Symtab
{
public:
	Symtab();
	void level_up();
	void level_down();
	int insert(const std::string name, const int type, const int val);
	int lookup(const std::string name, int type, int &l, int &o, int &value);
	void print();
	int get_procnr();
	int get_procnr(const std::string name);
private:
	std::map<std::string, Symtab_entry> m_content[10];
	int m_level;
	int m_procnr;
};