#include "Symtab.hpp"
#include <iostream>

Symtab::Symtab() 
{
	m_level = -1;
	m_procnr = 0;
}

bool Symtab::level_up()
{
	if (m_level < Symtab::LEVEL_MAX)
	{
		std::cout << "Symtab-level-up\n";
		m_level++;
		return true;
	}
	else
	{
		std::cout << "Error: Highest Level has been reached!\n";
		return false;
	}
}

bool Symtab::level_down()
{
	if (m_level > 0)
	{
		std::cout << "Symtab-level-down\n";
		m_content[m_level--].clear();
		return true;
	}
	else
	{
		std::cout << "Error: Lowest Level has been reached!\n";
		return false;
	}
}

bool Symtab::insert(const std::string name, const int typ, const int val)
{
	int n = m_content[m_level].size();
	if (m_content[m_level].find(name) == m_content[m_level].end()) 
	{
		m_content[m_level][name] =
			Symtab_entry(typ, n, (typ == st_proc) ? ++m_procnr : val);

		std::cout << "Symtab-insert "
			<< name
			<< ": "
			<< m_level
			<< "/"
			<< m_content[m_level][name].getNr()
			<< " procnr: " 
			<< m_procnr
			<< std::endl;
		return true;
	}
	else
	{
		std::cout << "Name is already used! \n";
		return false;
	}
	
}

int Symtab::lookup(const std::string name, int type, int &l, int &o, int &value)
{
	int i = m_level + 1, rc = 0;
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
				std::cout << "ERROR: Wrong type!"
				  << std::endl;
			}
		}
		else
		{
			rc = -2; //Nicht gefunden
			std::cout << "ERROR: Symbolname not found!"
				  << std::endl;
		}
	}
	return rc;
}

bool Symtab::modify(const std::string name, const int type, const int value)
{
	int stl, sto, val, lookupResult;
	if (type == st_var)
	{
		if (Symtab::lookup(name, type, stl, sto, val) >= 0)
		{
			m_content[stl][name].setVal(val);
			return true;
		}

		return false;
	}
	else
	{
		std::cout << "Error: Only Variables are allowed to be modified!";
		return false;
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