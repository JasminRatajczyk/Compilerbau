flex pl0Scanner.l
bison -dy Pl0Compiler.y
gcc lex.yy.c y.tab.c -o compiler.exe
