#include <map>
#include <vector>

class Memory 
{
public:
    Memory();
    ~Memory();
    int getAdr(int delta, int nr);
    void ram_neusegment(int n, int delta);
    void ram_loeschsegment();

    std::vector<int> RAM;

private:  
    const int ARG = 2;
};