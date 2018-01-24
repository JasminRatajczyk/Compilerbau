#include "../Symtab/Symtab.cpp"
#include <string>
#include <iostream>

Symtab* symtab;

void testInsert();
void testLookUp();

int main ()
{
    symtab = new Symtab::Symtab();
    testInsert();
    return 0;
}

void testInsert()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Test " << i << std::endl;
        symtab->insert(std::to_string(i), st_const, i);
    }
}

void testLookUp()
{
    for (int i = 0; i < 10; i++)
    {

    }
}

