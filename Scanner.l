%{
/****************************************************
LEX−Programm zur Ausführung von Pl/0 Programmen
****************************************************/
#include <string.h>
#include <stdio.h>
#include "Parser.tab.h"
%}
%option noyywrap
%%
"+"                        return t_PLUS;
"-"                        return t_MINUS;
"*"                        return t_MUL;
"/"                        return t_DIV;
"("                        return t_KLA_AUF;
")"                        return t_KLA_ZU;
"ODD"                      return t_ODD;
"="                        return t_EQUAL;
"#"                        return t_NEQUAL;
"<"                        return t_LESS;
"<="                       return t_LEQUAL;
">"                        return t_GREATER;
">="                       return t_GREQUAL;
","                        return t_COMMA;
";"                        return t_SEMICOLON;
"."                        return t_PERIOD;
":="                       return t_ASSIGN;
"//".* "\n"                /*do nothing*/;
"/*".* "*/"                /*do nothing*/;
"BEGIN"                    return t_BEGIN;
"END"                      return t_END;
"IF"                       return t_IF;
"THEN"                     return t_THEN;
"WHILE"                    return t_WHILE;
"DO"                       return t_DO;
"CALL"                     return t_CALL;
"PROCEDURE"                return t_PROCEDURE;
"CONST"                    return t_CONST;
"VAR"                      return t_VAR;
"?"                        return t_READ;
"!"                        return t_WRITE;
[0-9]+                     yylval._int = atoi(yytext);  return t_ZAHL;
[a-zA-Z][0-9a-zA-Z]*       strncpy(yylval._ident, yytext, 99); yylval._ident[99] = '\0';    return t_IDENT;
[ \n\t]                    /*do nothing*/;
%%