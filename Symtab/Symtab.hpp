#include <map>
#include <string>
#include <iostream>

enum { st_var = 1, st_const = 2, st_proc = 4 };

class Symtab_entry
{
	public:
		Symtab_entry(int = 0, int = 0);
		
		int type;
		int nr;
};

class Symtab
{
public:
	Symtab();
	void level_up();
	void level_down();
	void insert(const std::string name, const int type);
	void lookup(const std::string name, int type, int &l, int &o);
	void print();
	int get_procnr();
	int get_procnr(const std::string name);
	
	static const int LEVEL_MAX = 10;

private:	
	std::map<std::string, Symtab_entry> m_content[LEVEL_MAX];
	int m_level;
	int m_procnr;
};