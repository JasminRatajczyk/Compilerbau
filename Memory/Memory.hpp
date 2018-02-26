#pragma once
#include <vector>

class Memory 
{
public:
    int getAdr(int delta, int nr);
    int getVal(int delta, int nr);
    void setVal(int delta, int nr, int val);
    void print();
    void ram_neusegment(int n, int delta);
    void ram_loeschsegment();

    Memory();
private:  
    static const int ARG = 2;
    std::vector<int> RAM;
};