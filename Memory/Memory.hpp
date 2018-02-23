#include <map>
#include <vector>

class Memory 
{
public:
    static Memory* getInstance();
    
    int getAdr(int delta, int nr);
    int getVal(int delta, int nr);
    void setVal(int delta, int nr, int val);
    void ram_neusegment(int n, int delta);
    void ram_loeschsegment();

    Memory(Memory const&)         = delete;
    void operator=(Memory const&) = delete;
private:  
    Memory() {}
    static Memory* instance;
    static const int ARG = 2;
    std::vector<int> RAM;
};