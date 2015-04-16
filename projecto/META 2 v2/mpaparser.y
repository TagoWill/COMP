%{
	#include "structures.h"
	#include "functions.h"
	#include "shows.h"
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	
	extern int line;
	extern int col;
	extern char *yytext;
	extern int yyleng;
	int erros = 0;


	is_Prog* myprogram = NULL;
%}

%union {
	char *str;
	is_Prog* p;
	is_ProgHeading *ph;
	is_ProgBlock *pb;
	is_VarPart_List *vp;
	is_FuncPart_List *fpl;
	is_StatPart *sp;
	is_VarDeclaration *vd;
	is_IDList_List *il;
	is_FuncDeclaration *fd;
	is_FuncHeading *fh;
	is_FuncIdent *fi;
	is_FormalParamList *fpll;
	is_FormalParams *fps;
	is_FuncBlock *fb;
	is_Stat *st1;
	is_WritelnPList *wl;
	is_Expr *exo;
	is_ParamList *pl;
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
%token REALDIV
%token MOD
%token <str> RESERVED
%token <str> ID
%token <str> INTLIT
%token <str> REALLIT
%token <str> STRING



%left 	MULT REALDIV DIV MOD AND
%right	PLUS MINUS OR
%left	GREATER LESS GEQUAL LEQUAL EQUALS DIFFERENT
%right 	NOT
%left 	IF
%left	THEN
%left   ELSE

%type <p>  Prog
%type <ph> ProgHeading
%type <pb> ProgBlock
%type <vp> VarPart
%type <fpl> FuncPart
%type <sp> StatPart
%type <vp> VarPart2
%type <vd> VarDeclaration
%type <il> IDList
%type <il> IDList2
%type <fd> FuncDeclaration
%type <fh> FuncHeading
%type <fi> FuncIdent
%type <fpll> FormalParamList
%type <fpll> FormalParams
%type <fps>	FormalParams2
%type <fb> FuncBlock
%type <st1> CompStat
%type <st1> StatList
%type <st1> StatList2
%type <st1> Stat
%type <wl> WritelnPList
%type <wl> WritelnPList2
%type <exo> Expr
%type <pl> ParamList
%type <pl> ParamList2

%%
Prog: 
	ProgHeading SEMIC ProgBlock DOT 							{$$=insert_Prog($1, $3);	myprogram=$$;}
	;

ProgHeading:
	PROGRAM	ID LBRAC OUTPUT RBRAC 								{$$=insert_ProgHeading($2);}
	;

ProgBlock:
	VarPart FuncPart StatPart 									{$$=insert_ProgBlock($1, $2, $3);}
	;

VarPart:
	VAR VarDeclaration SEMIC VarPart2 							{$$=insert_VarPart($2, $4);}
	|															{$$=insert_VarPart(NULL, NULL);}
	;

VarPart2:
	VarDeclaration SEMIC VarPart2 								{$$=insert_VarPart($1, $3);}
	|															{$$=insert_VarPart(NULL, NULL);}
	;

VarDeclaration:
	IDList COLON ID 											{$$=insert_VarDeclaration($1, $3);}
	;

IDList:
	ID IDList2 													{$$=insert_IDList($1, $2);}
	;

IDList2:
	COMMA ID IDList2 											{$$=insert_IDList($2, $3);}
	|															{$$=insert_IDList(NULL, NULL);}
	;

FuncPart:
	FuncDeclaration SEMIC FuncPart 								{$$=insert_FuncPart($1, $3);}
	| 															{$$=insert_FuncPart(NULL, NULL);}
	;

FuncDeclaration:
	FuncHeading SEMIC FORWARD 									{$$=insert_FuncDeclarationH($1, NULL);}
	| FuncIdent SEMIC FuncBlock 								{$$=insert_FuncDeclarationI($1, $3);}
	| FuncHeading SEMIC FuncBlock 								{$$=insert_FuncDeclarationH($1, $3);}
	;

FuncHeading:
	FUNCTION ID FormalParamList COLON ID 						{$$=insert_FuncHeading($2, $3, $5);}
	| FUNCTION ID COLON ID 										{$$=insert_FuncHeading($2, NULL, $4);}
	;

FuncIdent:
	FUNCTION ID 												{$$=insert_FuncIdent($2);}
	;

FormalParamList:
	LBRAC FormalParams2 FormalParams RBRAC 						{$$=insert_FormalParamList($2, $3);}
	;

FormalParams:
	SEMIC FormalParams2 FormalParams 							{$$=insert_FormalParamList($2, $3);}
	| 															{$$=insert_FormalParamList(NULL, NULL);}
	;

FormalParams2:
	VAR IDList COLON ID 										{$$=insert_FormalParams($2, $4);}
	| IDList COLON ID 											{$$=insert_FormalParams($1, $3);}
	;

FuncBlock:
	VarPart StatPart 											{$$=insert_FuncBlock($1, $2);}
	;

StatPart:
	CompStat 													{$$=insert_StatPart($1);}
	;

CompStat:
	BEG StatList END 											{$$=insert_CompStat($2);}
	;

StatList:
	Stat StatList2 												{$$=insert_StatList($1, $2);}
	;

StatList2:
	SEMIC Stat StatList2 										{$$=insert_StatList($2, $3);}
	|															{$$=insert_StatList(NULL, NULL);}
	;

Stat:
	CompStat 													{$$=insert_Stat1($1);}
	| IF Expr THEN Stat ELSE Stat  								{$$=insert_StatITE($2, $4, $6);}
	| IF Expr THEN Stat  										{$$=insert_StatIT($2, $4);}
	| WHILE Expr DO Stat 										{$$=insert_StatIWR($2, $4);}
	| REPEAT StatList UNTIL Expr 								{$$=insert_StatIRU($2, $4);}
	| VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC		{$$=insert_StatV($5, $8);}
	| ID ASSIGN Expr 											{$$=insert_Stat2($1, $3);}
	| WRITELN WritelnPList 										{$$=insert_WPL($2);}
	| WRITELN 													{$$=insert_WPL(NULL);}
	|															{$$=insert_Stat1(NULL);}
	;

WritelnPList:
	LBRAC Expr RBRAC WritelnPList2 								{$$=insert_WritelnPList($2, $4);}
	| LBRAC STRING RBRAC WritelnPList2						 	{$$=insert_WritelnPList2($2, $4);}
	;

WritelnPList2:
	COMMA STRING WritelnPList2 									{$$=insert_WritelnPList2($2, $3);}
	| COMMA Expr WritelnPList2 									{$$=insert_WritelnPList($2, $3);}
	|															{$$=insert_WritelnPList(NULL, NULL);}
	;

Expr:
	Expr PLUS Expr 												{$$=insert_ExprO($1, is_PLUS, $3);}
	| Expr MINUS Expr 											{$$=insert_ExprO($1, is_SUB, $3);}
	| Expr AND Expr 											{$$=insert_ExprO($1, is_AND, $3);}
	| Expr OR Expr 												{$$=insert_ExprO($1, is_OR, $3);}
	| Expr MULT Expr 											{$$=insert_ExprO($1, is_MULT, $3);}
	| Expr REALDIV Expr 										{$$=insert_ExprO($1, is_REALDIV, $3);}
	| Expr DIV Expr 											{$$=insert_ExprO($1, is_DIV, $3);}
	| Expr MOD Expr	 											{$$=insert_ExprO($1, is_MOD, $3);}
	| Expr GREATER Expr 										{$$=insert_ExprO($1, is_GREATER, $3);}
	| Expr LESS Expr 											{$$=insert_ExprO($1, is_LESS, $3);}
	| Expr GEQUAL Expr 											{$$=insert_ExprO($1, is_GEQUAL, $3);}
	| Expr EQUALS Expr 											{$$=insert_ExprO($1, is_EQUALS, $3);}
	| Expr DIFFERENT Expr 										{$$=insert_ExprO($1, is_DIFFERENT, $3);}
	| AND Expr 													{$$=insert_ExprO(NULL, is_AND, $2);}
	| MINUS Expr 												{$$=insert_ExprO(NULL, is_MINUS, $2);}
	| NOT Expr 													{$$=insert_ExprO(NULL, is_NOT, $2);}
	| LBRAC Expr RBRAC 											{$$=insert_Expr(is_EXO, $2);}
	| INTLIT 													{$$=insert_ExprI(is_INTLIT, $1, NULL);}
	| REALLIT 													{$$=insert_ExprI(is_REALLIT, $1, NULL);}
	| ID ParamList 												{$$=insert_ExprI(is_ID, $1, $2);}
	| ID 														{$$=insert_ExprI(is_ID, $1, NULL);}
	;

ParamList:
	LBRAC Expr ParamList2 RBRAC									{$$=insert_ParamList($2, $3);}
	;

ParamList2:
	COMMA Expr ParamList2										{$$=insert_ParamList($2, $3);}
	|															{$$=insert_ParamList(NULL, NULL);}
	;

%%
int yyerror (char *s)
{
	if(col-yyleng==0)
	{
        col++;
		printf ("Line %d, col %d: %s: %s\n", line, (col), s, yytext);
	} else {
		printf ("Line %d, col %d: %s: %s\n", line, (col-yyleng), s, yytext);
	}
	erros=1;
	return 1;
}

int main()
{
	yyparse();
	if(erros != 1)
		show_prog(myprogram);
	return 0;
}
