%{
#include "y.tab.h"
%}
%option noyywrap
%option nodefault
%%
"+" return PLUS;
"−" return MINUS;
"*" return MUL;
"/" return DIV;
"(" return KLA_AUF;
")" return KLA_ZU;
[0-9]+ return ZAHL;
[ \t \n ] /* do nothing */;
. return FEHLER;
%%