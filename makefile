all : scanner parser compiler
scanner : Scanner.l
	flex Scanner.l
parser : Parser.y
	bison -d Parser.y
compiler : lex.yy.c Parser.tab.c Symtab/Symtab.cpp
	g++ lex.yy.c Parser.tab.c Symtab/Symtab.cpp -o pl0.out