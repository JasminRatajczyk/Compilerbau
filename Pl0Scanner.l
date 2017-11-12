%{
/****************************************************
LEX−Programm zur Berechnung arithmetischer Ausdruecke
****************************************************/
#include <string.h>
#include <stdio.h>
enum 
{
    PLUS = 1, MINUS, MUL, DIV, KLA_AUF, KLA_ZU, ODD, EQUAL, NEQUAL,
    LESS, LEQUAL, GREATER, GREQUAL, COMMA, SEMICOLON, PERIOD, BECOME,
    BEGINSYM, END, IF, THEN, WHILE, DO, CALL, CONST, INT, PROCDURE,
    OUT, IN, ELSE, ZAHL, VARIABLE, FEHLER
};
%}
%%
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
"procedure" return PROCDURE;
"out" return OUT;
"in" return IN;
"else" return ELSE;
[0-9]+ return ZAHL;
[a-z A-Z]+[0-9]+ return VARIABLE;
[ \t \n ] /* do nothing */;
. return FEHLER;
%%

int main()
{
    return 0;
}

int yywrap() 
{
    return 1;
}