flex Scanner.l
bison -d Parser.y
g++ lex.yy.c Parser.tab.c Symtab/Symtab.cpp -o pl0.exe
