%{
	#include <stdio.h>
	#include <string.h>
	
%}

%union {
	int value;
	char* id;
	char* str;
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
%token <str> STRING

%type Prog
%type ProgHeading
%type ProgBlock
%type VarPart
%type VarDeclaration
%type IDList
%type FuncPart
%type FuncDeclaration
%type FuncDeclaration2
%type FuncDeclaration3
%type FuncHeading
%type FuncIdent
%type FormalParamList
%type FormalParams
%type FuncBlock
%type StatPart
%type CompStat
%type StatList
%type Stat
%type Stat2
%type Stat3
%type Stat4
%type Stat5
%type Stat6
%type Stat7
%type WritelnPList
%type Expr
%type Expr2
%type Expr3
%type Expr4
%type Expr5
%type ParamList

%left	COMMA
%right	ASSIGN
%left	OR
%left	AND            
%left   EQUALS DIFFERENT
%left   GREATER LESS LEQUAL GEQUAL
%left	PLUS MINUS
%left	MULT DIV MOD        		
%right	NOT
%left	RBRAC LBRAC

%nonassoc	IF ELSE

%%
Prog: 
	ProgHeading
	SEMIC
	ProgBlock
	DOT
	;

ProgHeading:
	PROGRAM
	ID
	LBRAC
	OUTPUT
	RBRAC
	;

ProgBlock:
	VarPart
	FuncPart
	StatPart
	;

VarPart:
	VAR
	VarDeclaration
	SEMIC
	VarDeclaration
	SEMIC
	;

VarDeclaration:
	IDList
	COLON
	ID
	;

IDList:
	ID
	COMMA
	ID
	;

FuncPart:
	FuncDeclaration 
	SEMIC
	;

FuncDeclaration:
	FuncHeading
	SEMIC
	FORWARD
	;

FuncDeclaration2:
	FuncIdent
	SEMIC
	FuncBlock
	;

FuncDeclaration3:
	FuncHeading
	SEMIC
	FuncBlock
	;

FuncHeading:
	FUNCTION
	ID
	FormalParamList
	COLON
	ID
	;

FuncIdent:
	FUNCTION
	ID
	;

FormalParamList:
	LBRAC
	FormalParams
	SEMIC
	FormalParams
	RBRAC
	;

FormalParams:
	VAR
	IDList
	COLON
	ID
	;

FuncBlock:
	VarPart
	StatPart
	;

StatPart:
	CompStat
	;

CompStat:
	BEGIN
	StatList
	END
	;

StatList:
	Stat
	SEMIC
	Stat
	;

Stat:
	CompStat
	;

Stat2:
	IF
	Expr
	THEN
	Stat
	ELSE
	Stat
	;

Stat3:
	WHILE
	Expr
	DO
	Stat
	;

Stat4:
	REPEAT 
	StatList 
	UNTIL 
	Expr
	;

Stat5:
	VAL
	LBRAC
	PARAMSTR
	LBRAC
	Expr
	RBRAC
	COMMA
	ID
	RBRAC
	;

Stat6:
	ID
	ASSIGN
	Expr
	;

Stat7:
	WRITELN
	WritelnPList
	;

WritelnPList:
	LBRAC
	Expr
	String
	COMMA
	Expr
	STRING
	RBRAC
	;

Expr:
	Expr
	OP1
	OP2
	OP3
	OP4
	Expr
	;

Expr2:
	OP3
	NOT
	Expr
	;

Expr3:
	LBRAC
	Expr
	RBRAC
	;

Expr4:
	INTLIT
	REALLIT
	;

Expr5:
	ID
	ParamList
	;

ParamList:
	LBRAC
	Expr
	COMMA
	Expr
	RBRAC
	;


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
