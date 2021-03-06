all : scanner parser compiler
scanner : Scanner.l
	flex Scanner.l
parser : Parser.y
	bison -d Parser.y
compiler : lex.yy.c Parser.tab.c Symtab/Symtab.cpp Ast/Ast.c Memory/Memory.cpp ProcList/ProcList.cpp
	g++ -g -std=c++0x lex.yy.c Parser.tab.c Symtab/Symtab.cpp ProcList/ProcList.cpp Memory/Memory.cpp Ast/Ast.c  -o pl0.out