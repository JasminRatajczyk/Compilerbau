#include <stdio.h>
#include "Ast.h"
#include "Pl0Scanner.h"

//Protottypen
void scanner();
ast f_start();
ast f_factor();
ast f_expression();
ast f_term();


//Globale Daten
char zahl[20];
int token, error;

//Hauptprogramm
int main(){
char text[100];
ast s;

while(printf("Input:"), fgets(text, 255,stdin)!=NULL){
	Pl0Scanner(text, NULL); //Scanner-Reset
	s = f_start();
	if(!error){
		printf("Syntaxbaum:\n");
		tree_output(s,0);
		printf("UPN-Codeausgabe\n");
		tree_code(s);
		printf("Ergebnis: %lf\n", tree_result(s));
	}
	else printf("Syntax nicht OK, error=%d\a\n", error);
	tree_free(s);
}
return 0;

}

//Funktionen
void scanner(){
	token = Pl0Scanner(NULL, zahl);
}

ast f_factor(){
	ast p;
	if(token == PLUS){
		scanner();
		p= f_factor();
	} else if ((token == MINUS){
		scanner();
		p = new_node("C", f_factor(), NULL);
	}else if(token == ZAHL){
		p= new_node(zahl, NULL, NULL);
		scanner();
	
	}else if(token == KLA_AUF){
		scanner();
		p= f_expression();
		if(token == KLA_ZU)scanner();
		else error = 1;
	}
	else error = 2;
	return p;
	
	
}

ast f_term(){
	ast p;
	char * txt;
	p= f_factor();
	while(token == MAL || token == DIV){
		txt = (token == MAL)? "*" : "/";
		scanner();
		p= new_node(txt, p, f_factor());
	}
	return p;
}

ast f_expression(){
	ast p;
	int token2;
	p = f_term();
	while (token == PLUS || token == MINUS){
		token2 = token;
		 scanner();
		 p = new_node((token2 == PLUS)? "+" : "-", p, f_term());
	}
	return p;
	
}

ast f_start(){
	scanner(), error = 0;
	ast p = f_expression();
	if(token != END)error = 3;
	return p;
}


