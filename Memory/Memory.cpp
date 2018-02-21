#include "Memory.hpp"

Memory::Memory()
{
    RAM.at(0) = 0;
}

int Memory::getAdr (int delta, int nr)
{
    int adr = RAM.at(0);
    for(int i=0; i<delta; i++){
        adr = RAM.at(adr);
    }
    adr = adr - ARG;
    adr = adr - nr;
    return adr;
}

void Memory::ram_neusegment(int n, int delta)
{
    RAM.at(RAM.at(0)+n+ARG -1) = RAM.at(0); //Dynamic Link
    int adr = RAM.at(0);;
    for(int i=0; i<delta; i++){
        adr = RAM.at(adr);
    }
    RAM.at(RAM.at(0)+n+ARG) = adr; //Static Link
    RAM.at(0) = RAM.at(0) +n +ARG; //TOS
}

void Memory::ram_loeschsegment()
{
    RAM.at(0) = RAM.at(RAM.at(0)-1) ; //TOS
}