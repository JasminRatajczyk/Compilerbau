#include <stdlib.h>
#include "Symtab.hpp"

Symtab_entry::Symtab_entry(int t, int n) 
{
	type = t;
	nr = n;
}

Proc_Entry::Proc_Entry(int n, int p) : Symtab_entry(st_proc, n)			   
{
	proc = p;
}

Symtab::Symtab() 
{
	m_level = -1;
	m_procnr = 0;
}

void Symtab::level_up()
{
	if (m_level < LEVEL_MAX)
	{
		m_level++;		
		std::cout << "level up to: " << m_level << std::endl;
	}
	else
	{
		std::cout << "Error: Highest Level has been reached!\n";
		exit (EXIT_FAILURE);
	}
}

void Symtab::level_down()
{
	if (m_level > -1)
	{	
		std::cout << "level down to: " << m_level << std::endl;
		m_content[m_level--].clear();
	}
	else
	{
		std::cout << "Error: Lowest Level has been reached!\n";
		exit (EXIT_FAILURE);
	}
}

void Symtab::insert(const std::string name, const int typ)
{
	int n = m_content[m_level].size();

	if (m_content[m_level].find(name) == m_content[m_level].end()) 
	{
		if (typ > 3)
		{
			m_content[m_level][name] = Proc_Entry(n, ++m_procnr);			
		}
		else
		{
			m_content[m_level][name] = Symtab_entry(typ, n);
		}
			
		std::cout << "Symtab insert '" << name << "', " << 
		"Typ: " << m_content[m_level][name].type << 
		", level: " << m_level << 
		", offset: " << m_content[m_level][name].nr << std::endl;
	}
	else
	{
		std::cout << "Name is already used! \n";
		exit (EXIT_FAILURE);
	}
}

void Symtab::lookup(const std::string name, int type, int &l, int &o)
{
	int i = m_level + 1, rc = 0;
	l = o = -1;
	
	std::cout << "Lookup: '" << name << 
	"' (Typ " << type << " )" << std::endl;

	while (--i >= 0 && m_content[i].find(name) == m_content[i].end()) {}

	if (i >= 0)
	{
		if (m_content[i][name].type & type) //Bitshifting
		{
			std::cout << type << " equal to " << m_content[i][name].type << std::endl;
			
			l = m_level - i;
			o = m_content[i][name].nr;

			std::cout << "found: name '" << name << "', Type: " 
			<< m_content[i][name].type << std::endl;
		}
		else
		{
			std::cout << "ERROR: Wrong type!"
				  << std::endl;
			exit (EXIT_FAILURE);
		}			
	}
	else
	{
		std::cout << "ERROR: Symbolname not found!"
				  << std::endl;
		exit (EXIT_FAILURE);
	}
}

void Symtab::print()
{
	std::map<std::string, Symtab_entry>::iterator pos;
	std::cout << "Akt. Level: " << m_level << std::endl;
	for (int i = 0; i <= m_level; i++)
	{
		std::cout << "Level " << i << " Hoehe " << m_content[i].size();
		pos = m_content[i].begin();
		for (pos = m_content[i].begin(); pos != m_content[i].end(); ++i)
		{
			std::cout << "Key: " << (*pos).first << (*pos).second.nr;
		}
	}
}

int Symtab::get_procnr()
{
	return m_procnr;
}

int Symtab::get_procnr(const std::string name)
{
	int i = m_level + 1;
	int num = -1;
	
	while(i-- >= 0 && m_content[i].find(name) == m_content[i].end()){}
	if(i >= 0){
		if(m_content[i][name].type == st_proc) {
			num = m_content[i][name].proc;
		}
	}
	return num;
}