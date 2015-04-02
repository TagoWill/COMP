%{
	#include <stdio.h>
	#include <string.h>
	
%}

%union {

}

%token ASSIGN
%token BEGIN
%token COLON
%token COMMA
%token DO
%token DOT
%token ELSE
%token END
%token FORWARD
%token FUNCTION
%token IF
%token LBRAC
%token NOT
%token OUTPUT
%token PARAMSTR
%token PROGRAM
%token RBRAC
%token REPEAT
%token SEMIC
%token THEN
%token UNTIL
%token VAL
%token VAR
%token WHILE
%token WRITELN
%token OR
%token AND
%token GREATER
%token LESS
%token GEQUAL
%token LEQUAL
%token EQUALS
%token DIFFERENT
%token PLUS
%token MINUS
%token MULT
%token DIV
%token MOD
%token RESERVED

%token <id> ID
%token <value> INTLIT
%token <value> REALLIT
%token <id> STRING

%left	COMMA
%right	ASSIGN
%left	OR
%left	AND            
%left   EQUALS DIFFERENT
%left   GREATER LESS LEQUAL GEQUAL
%left	PLUS MINUS
%left	MULT DIV MOD        		
%right	NOT
%right	NEW
%left	CCURV OSQUARE CSQUARE OCURV
%left	DOTLENGTH

%nonassoc	IF ELSE

%%


				
%%
int yyerror (char *s)
{
	if(strcmp(yytext, "")==0)
	{
		printf ("Line %d, col %d: %s: %s\n", line, (col), s, yytext);
	} else {
		printf ("Line %d, col %d: %s: %s\n", line, (col-yyleng), s, yytext);
	}
	return 1;
}

int main()
{
	yyparse();
	return 0;
}
