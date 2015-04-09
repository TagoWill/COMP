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
%token <str> RESERVED
%token <str> OP1
%token <str> OP2
%token <str> OP3
%token <str> OP4
%token <str> ID
%token <str> INTLIT
%token <str> REALLIT
%token <str> STRING


%left	COMMA
%right	ASSIGN
%right	OP1            
%right  OP2
%left   OP4
%right	OP3
%right   NOT       		
%left	RBRAC LBRAC

%nonassoc	IF ELSE

%%
Prog: 
	ProgHeading SEMIC ProgBlock DOT
	;

ProgHeading:
	PROGRAM	ID LBRAC OUTPUT RBRAC
	;

ProgBlock:
	VarPart FuncPart StatPart
	;

VarPart:
	VAR VarDeclaration SEMIC VarPart2
	|
	;

VarPart2:
	VarDeclaration SEMIC
	|
	;

VarDeclaration:
	IDList ID VarDeclaration SEMIC
	| IDList COLON ID
	|
	;

IDList:
	ID COMMA IDList
	| ID
	;

FuncPart:
	FuncDeclaration SEMIC
	| 
	;

FuncDeclaration:
	FuncHeading SEMIC FORWARD
	| FuncIdent SEMIC FuncBlock
	| FuncHeading SEMIC FuncBlock
	;

FuncHeading:
	FUNCTION ID FormalParamList COLON ID
	| FUNCTION ID COLON ID
	;

FuncIdent:
	FUNCTION ID
	;

FormalParamList:
	LBRAC FormalParams2 FormalParams RBRAC
	;

FormalParams:
	SEMIC FormalParams2 FormalParams
	| 
	;

FormalParams2:
	VAR IDList COLON ID
	| IDList COLON ID
	;

FuncBlock:
	VarPart StatPart {/*SHIFT/REDUCE no VarPart*/}
	;

StatPart:
	CompStat
	;

CompStat:
	BEG StatList END
	;

StatList:
	Stat SEMIC StatList
	| Stat
	;

Stat:
	CompStat
	| IF Expr THEN Stat Stat2
	| WHILE Expr DO Stat
	| REPEAT StatList UNTIL Expr
	| VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC
	| Stat3
	| WRITELN WritelnPList
	| WRITELN
	;

Stat2:
	ELSE Stat 	{/*SIGHT/REDUCE No lo se soluciono*/}
	;

Stat3:
	ID ASSIGN Expr
	|
	;

WritelnPList:
	LBRAC Expr RBRAC WritelnPList2
	| LBRAC STRING RBRAC WritelnPList2
	;

WritelnPList2:
	COMMA STRING WritelnPList2
	|COMMA Expr WritelnPList2
	|
	;

Expr:
	Expr OP1 Expr
	| Expr OP2 Expr
	| Expr OP3 Expr
	| Expr OP4 Expr	
	| OP3 Expr
	| NOT Expr
	| LBRAC Expr RBRAC
	| INTLIT
	| REALLIT
	| ID ParamList
	| ID
	;

ParamList:
	LBRAC Expr ParamList2 RBRAC
	;

ParamList2:
	COMMA Expr
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
