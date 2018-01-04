
%{
/****************************************************
LEX−Programm zur Berechnung arithmetischer Ausdruecke
****************************************************/
#include <string.h>
#include <stdio.h>
#include "yy.tab.h"
%}
%%
"+" return PLUS;
"−" return MINUS;
"*" return MUL;
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
"//".* "\n" /*do nothing*/;
"/*".* "*/" /*do nothing*/;
"begin" return BEGINSYM;
"end" return END;
"if" return IF;
"then" return THEN;
"while" return WHILE;
"do" return DO;
"call" return CALL;
"procedure" return PROCEDURE;
"const" return CONST;
"int" return INT;
"out" return OUT;
"in" return IN;
"read" return READ;
"write" return WRITE;
[0-9]+ return ZAHL;
[a-z A-Z][a-z A-Z 0-9]* return IDENT;
[ \t \n ] /* do nothing */;
. return FEHLER;
%%