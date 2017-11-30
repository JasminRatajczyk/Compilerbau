%{
#include <y.tab.h>
int yyerror();
%}
%%
"/*" return COMMENTSTART;
"*/" return COMMENTEND;
"+" return PLUS;
"−" return MINUS;
"∗" return MUL;
"/" return DIV;
"(" return KLA_AUF;
")" return KLA_ZU;
"odd" return ODD;
"=" return EQUAL;
"<>" return NEQUAL;
"<" return LESS;
"<=" return LEQUAL;
">" return GREATER;
">=" return GREQUAL;
"," return COMMA;
";" return SEMICOLON;
"." return PERIOD;
":=" return BECOME;
"begin" return BEGINSYM;
"end" return END;
"if" return IF;
"then" return THEN;
"while" return WHILE;
"do" return DO;
"call" return CALL;
"const" return CONST;
"int" return INT;
"procedure" return PROCEDURE;
"out" return OUT;
"in" return IN;
"else" return ELSE;
[0-9]+ return ZAHL;
[a-z A-Z]+[0-9]+ return VARIABLE;
("\""" .* "\""") return STRING;
[ \t \n ] /* do nothing */;
. return FEHLER;
%%