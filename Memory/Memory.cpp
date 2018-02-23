#include "Memory.hpp"

Memory* Memory::instance = 0;

Memory::Memory()
{
    RAM.push_back(0);
}

Memory* Memory::getInstance()
{
    if (instance == 0)
    {
        instance = new Memory();
    }

    return instance;
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
}

void Memory::ram_neusegment(int n, int delta)
{
    RAM.at(RAM.at(0)+n+ARG -1) = RAM.at(0); //Dynamic Link
    int adr = RAM.at(0);
    for(int i=0; i<delta; i++)
    {
        adr = RAM.at(adr);
    }
    RAM.at(RAM.at(0)+n+ARG) = adr; //Static Link
    RAM.at(0) = RAM.at(0) +n +ARG; //TOS
}

void Memory::ram_loeschsegment()
{
    RAM.at(0) = RAM.at(RAM.at(0)-1) ; //TOS
}