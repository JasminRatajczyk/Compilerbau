flex Scanner.l
bison -d Parser.y
g++ std=c++0x lex.yy.c Parser.tab.c Symtab/Symtab.cpp Ast/Ast.c Memory/Memory.cpp -o pl0.exe
