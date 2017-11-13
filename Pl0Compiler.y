%{
int yyerror(char *s)
int yylex();
%}
%token PLUS, MINUS, MUL, DIV, KLA_AUF, KLA_ZU, ODD, EQUAL, NEQUAL,
    LESS, LEQUAL, GREATER, GREQUAL, COMMA, SEMICOLON, PERIOD, BECOME,
    BEGINSYM, END, IF, THEN, WHILE, DO, CALL, CONST, INT, PROCDURE,
    OUT, IN, ELSE, ZAHL, VARIABLE, FEHLER

%union { char t[100]}
%%
expression: term
          | expression PLUS term
          | expression MINUS term
          ;
term:       factor
          | term MUL factor
          | term DIV factor
          ;
factor:     ZAHL
          | KLA_AUF expression KLA_ZU
          | PLUS factor
          | MINUS factor
          ;
%%