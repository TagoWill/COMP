%{
	#include <stdio.h>
	#include <string.h>
	
%}

%union {
	int value;
	char *id;
	char *str;

	is_Prog *p;
	is_ProgHeading *ph;
	is_ProgBlock *pb;
	is_VarPart *vp;
	is_VarDeclaration *vd;
	is_IDList *il;
	is_FuncPart *fp;
	is_FuncDeclaration1 *fd1; 
	is_FuncDeclaration2 *fd2;
	is_FuncDeclaration3 *fd3;
	is_FuncHeading *fh;
	is_FuncIdent *fi;
	is_FormalParamList *fpl;
	is_FormalParams *fps;
	is_FuncBlock *fb;
	is_StatPart *sp;
	is_CompStat *cs;
	is_StatList *sl;
	is_Stat1 *s1;
	is_Stat2 *s2;
	is_Stat3 *s3;
	is_Stat4 *s4;
	is_Stat5 *s5;
	is_Stat6 *s6;
	is_Stat7 *s7;
	is_WritelnPList *wl;
	is_Expr1 *ex1;
	is_Expr2 *ex2;
	is_Expr3 *ex3;
	is_Expr4 *ex4;
	is_Expr5 *ex5;
	is_ParamList *pl;
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

%type <p> Prog
%type <ph> ProgHeading
%type <pb> ProgBlock
%type <vp> VarPart
%type <vd> VarDeclaration
%type <il> IDList
%type <fp> FuncPart
%type <fd1> FuncDeclaration1
%type <fd2> FuncDeclaration2
%type <fd3> FuncDeclaration3
%type <fh> FuncHeading
%type <fi> FuncIdent
%type <fpl> FormalParamList
%type <fps> FormalParams
%type <fb> FuncBlock
%type <sp> StatPart
%type <cs> CompStat
%type <sl> StatList
%type <s1> Stat1
%type <s2> Stat2
%type <s3> Stat3
%type <s4> Stat4
%type <s5> Stat5
%type <s6> Stat6
%type <s7> Stat7
%type <wl> WritelnPList
%type <ex1> Expr1
%type <ex2> Expr2
%type <ex3> Expr3
%type <ex4> Expr4
%type <ex5> Expr5
%type <pl> ParamList

%left	COMMA
%right	ASSIGN
%left	OR
%left	AND            
%left   EQUALS DIFFERENT
%left   GREATER LESS LEQUAL GEQUAL
%left	PLUS MINUS
%left	MULT DIV MOD        		
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
