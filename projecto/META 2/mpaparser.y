%{
	#include "y.tab.h"
	#include <stdio.h>
	#include <string.h>
	
	extern int line;
	extern int col;
	extern char *yytext;
	extern int yyleng;

%}

%union {
	char *str;
}

%token ASSIGN
%token BEG
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
%token <str> RESERVED
%token <str> ID
%token <str> INTLIT
%token <str> REALLIT
%token <str> STRING



%left 	MULT DIV MOD AND
%left	PLUS MINUS OR
%left	GREATER LESS GEQUAL LEQUAL EQUALS DIFFERENT
%left 	NOT
%left 	IF
%left	THEN
%left   ELSE



%%
Prog: 
	ProgHeading SEMIC ProgBlock DOT 							{}
	;

ProgHeading:
	PROGRAM	ID LBRAC OUTPUT RBRAC 								{}
	;

ProgBlock:
	VarPart FuncPart StatPart 									{}
	;

VarPart:
	VAR VarDeclaration SEMIC VarPart2 							{}
	|
	;

VarPart2:
	VarDeclaration SEMIC VarPart2 								{}
	|
	;

VarDeclaration:
	IDList COLON ID 											{}
	;

IDList:
	ID IDList2 													{}
	;

IDList2:
	COMMA ID IDList2 											{}
	|
	;

FuncPart:
	FuncDeclaration SEMIC FuncPart 								{}
	| 
	;

FuncDeclaration:
	FuncHeading SEMIC FORWARD 									{}
	| FuncIdent SEMIC FuncBlock 								{}
	| FuncHeading SEMIC FuncBlock 								{}
	;

FuncHeading:
	FUNCTION ID FormalParamList COLON ID 						{}
	| FUNCTION ID COLON ID 										{}
	;

FuncIdent:
	FUNCTION ID 												{}
	;

FormalParamList:
	LBRAC FormalParams2 FormalParams RBRAC 						{}
	;

FormalParams:
	SEMIC FormalParams2 FormalParams 							{}
	| 
	;

FormalParams2:
	VAR IDList COLON ID 										{}
	| IDList COLON ID 											{}
	;

FuncBlock:
	VarPart StatPart 											{}
	;

StatPart:
	CompStat 													{}
	;

CompStat:
	BEG StatList END 											{}
	;

StatList:
	Stat StatList2 												{}
	;

StatList2:
	SEMIC Stat StatList2 										{}
	|
	;

Stat:
	CompStat 													{}
	| IF Expr THEN Stat ELSE Stat  								{}
	| IF Expr THEN Stat  										{}
	| WHILE Expr DO Stat 										{}
	| REPEAT StatList UNTIL Expr 								{}
	| VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC		{}
	| Stat2 							{}
	| WRITELN WritelnPList 				{}
	| WRITELN 							{}
	;

Stat2:
	ID ASSIGN Expr 						{}
	|
	;

WritelnPList:
	LBRAC Expr RBRAC WritelnPList2 		{}
	| LBRAC STRING RBRAC WritelnPList2 	{}
	;

WritelnPList2:
	COMMA STRING WritelnPList2 			{}
	|COMMA Expr WritelnPList2 			{}
	|
	;

Expr:
	Expr PLUS Expr 						{}
	| Expr MINUS Expr 					{}
	| Expr AND Expr 					{}
	| Expr OR Expr 						{}
	| Expr MULT Expr 					{}
	| Expr DIV Expr 					{}
	| Expr MOD Expr	 					{}
	| Expr GREATER Expr 				{}
	| Expr LESS Expr 					{}
	| Expr GEQUAL Expr 					{}
	| Expr EQUALS Expr 					{}
	| Expr DIFFERENT Expr 				{}
	| AND Expr 							{}
	| MINUS Expr 						{}
	| NOT Expr 							{}
	| LBRAC Expr RBRAC 					{}
	| INTLIT 							{}
	| REALLIT 							{}
	| ID ParamList 						{}
	| ID 								{}
	;

ParamList:
	LBRAC Expr ParamList2 RBRAC			{}
	;

ParamList2:
	COMMA Expr ParamList2				{}
	|
	;

%%
int yyerror (char *s)
{
	if(strcmp(s, "")==0)
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
