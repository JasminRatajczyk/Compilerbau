#pragma once
#include<map>
#include<string>
#include "Symtab_entry.hpp"

class Symtab
{
public:
	Symtab();
	bool level_up();
	bool level_down();
	bool insert(const std::string name, const int type, const int val);
	bool modify(const std::string name, const int type, const int val);
	int lookup(const std::string name, int type, int &l, int &o, int &value);
	void print();
	int get_procnr();
	int get_procnr(const std::string name);
	
	static const int LEVEL_MAX = 10;

private:	
	std::map<std::string, Symtab_entry> m_content[LEVEL_MAX];
	int m_level;
	int m_procnr;
};