#pragma once

#include <map>

#include "../Ast/Ast_Prototype.h"
#include "../Ast/Ast.h"

struct ProcEntry {
    ProcEntry(int, block);
    int offset;
    block b;
};

class ProcList {
    public:
        ProcList();
        block getProc(int offset);
        void addProc(int offset, block b);
    private:
        std::map<int, std::vector<ProcEntry> > list;
        std::map<int, block> m_list;
};