#include "Symtab.h"
#include <iostream>

Symtab::Symtab() 
{
	m_level = -1;
	m_procnr = 0;
}

void Symtab::level_up() 
{
	if (m_level < m_content->size())
	{
		std::cout << "Symtab-level-up\n";
		m_level++;
	}
	else
	{
		std::cout << "ERR: Highest level has already been reached!";
	}
}

void Symtab::level_down() 
{
	std::cout << "Symtab-level-down\n";
	m_content[m_level--].clear();
}

int Symtab::insert(const std::string name, const int typ, const int val)
{
	int n = m_content[m_level].size(), r = 1;

	if (m_content[m_level].find(name) == m_content[m_level].end()) {
		m_content[m_level][name] =
			Symtab_entry(typ, n, (typ == st_proc) ? ++m_procnr : val);

		std::cout 
			<< "Symtab-insert " 
			<< name
			<< " :"
			<< m_level
			<< "/"
			<< m_content[m_level][name].getNr()
			<< " procnr: " << m_procnr;
		r = 0;
	}
	return r;
}

int Symtab::lookup(const std::string name, int type, int &l, int &o, int &value) 
{
	int i = m_level + 1, rc;
	std::cout << "Symtab-lookup " << name << " (Typ " << type << ")";
	l = o = -1;
	while (--i >= 0 && m_content[i].find(name) == m_content[i].end()) 
	{
		if (i >= 0)
		{
			if (m_content[i][name].getType() & type) //Bitshifting
			{
				l = m_level - i, o = m_content[i][name].getNr(), value = m_content[i][name].getVal();
			}
			else 
			{
				rc = -1; //Falscher Typ
			}
		}
		else 
		{
			rc = -2; //Nicht gefunden
		}
	}
	return rc;
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
			std::cout << "Key: " << (*pos).first << (*pos).second.getNr();
		}
	}
}

int Symtab::get_procnr()
{
	return m_procnr;
}

int Symtab::get_procnr(const std::string name)
{
	int l = 0, o = 0, value = 0;
	lookup(name, st_proc, l, o, value );
	return value;
}