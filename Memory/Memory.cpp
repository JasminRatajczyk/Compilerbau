#include "Memory.hpp"
#include <iostream>

Memory::Memory()
{
    RAM.push_back(0);
}

int Memory::getAdr (int delta, int nr)
{
    int adr = RAM.at(0);
    for(int i=0; i<delta; i++)
    {
        adr = RAM.at(adr);
    }
    adr = adr - ARG;
    adr = adr - nr;
    return adr;
}

int Memory::getVal(int delta, int nr)
{
    return RAM.at(getAdr(delta, nr));
}

void Memory::setVal(int delta, int nr, int val)
{
    RAM.at(getAdr(delta, nr)) = val;
    std::cout << "Val set to " << val << std::endl;
}

void Memory::ram_neusegment(int n, int delta)
{
    for(int i= 0; i<n+ARG; i++){
        RAM.push_back(0);
    }

    RAM.at(RAM.at(0)+n+ARG -1) = RAM.at(0); //Dynamic Link
    int adr = RAM.at(0);
    for(int i=0; i<delta; i++)
    {
        adr = RAM.at(adr);
    }
    RAM.at(RAM.at(0)+n+ARG) = adr; //Static Link
    RAM.at(0) = RAM.at(0) +n +ARG; //TOS
    std::cout << " RAMnew " << std::endl;    
}

void Memory::print()
{
    for(int i = 0; i < RAM.size(); i++)
    {
        std::cout << RAM.at(i) << std::endl;
    }
}

void Memory::ram_loeschsegment()
{
    RAM.at(0) = RAM.at(RAM.at(0)-1) ; //TOS
    RAM.resize(RAM.at(0)+1); //TOS
    std::cout << " RAMdelete " << std::endl;
}