#include "ProcList.hpp"
#include <iostream>

ProcEntry::ProcEntry(int offset, block b): offset(offset),
                                           b(b)
{
}

ProcList::ProcList()
{
}

block ProcList::getProc (int offset) 
{
    if (m_list.find(offset) != m_list.end())
    {
        return m_list.find(offset)->second;
    }
    else
    {
        std::cout << "ERR: Procedure not found!" << std::endl;
    }
    return nullptr;
}

void ProcList::addProc (int offset, block b) 
{
    if(m_list.find(offset) == m_list.end())
    {
        m_list[offset] = b;
    }
    else
    {
        std::cout << "ERR: offset already used!" << std::endl;
    }
}