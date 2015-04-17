%{
	#include "structures.h"
	#include "functions.h"
	#include "shows.h"
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	
	extern int lineaux;
	extern int colaux;
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
%left	PLUS MINUS OR
%left	GREATER LESS GEQUAL LEQUAL EQUALS DIFFERENT
%right 	NOT ASSIGN

%nonassoc	THEN
%nonassoc   ELSE

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
%type <exo> Expr2
%type <exo> Expr3
%type <exo> Expr4
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
	|															{$$=NULL;}
	;

VarPart2:
	VarDeclaration SEMIC VarPart2 								{$$=insert_VarPart($1, $3);}
	|															{$$=NULL;}
	;

VarDeclaration:
	IDList COLON ID 											{$$=insert_VarDeclaration($1, $3);}
	;

IDList:
	ID IDList2 													{$$=insert_IDList($1, $2);}
	;

IDList2:
	COMMA ID IDList2 											{$$=insert_IDList($2, $3);}
	|															{$$=NULL;}
	;

FuncPart:
	FuncDeclaration SEMIC FuncPart 								{$$=insert_FuncPart($1, $3);}
	| 															{$$=NULL;}
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
	| 															{$$=NULL;}
	;

FormalParams2:
	VAR IDList COLON ID 										{$$=insert_FormalParams($2, $4);}
	| IDList COLON ID 											{$$=insert_FormalParams($1, $3);}
	;

FuncBlock:
	VarPart StatPart 											{$$=insert_FuncBlock($1, $2);}
	;

StatPart:
	CompStat 													{if($1==NULL){$$=NULL;}else{$$=insert_StatPart($1);}}
	;

CompStat:
	BEG StatList END 											{if($2==NULL){$$=NULL;}else{$$=insert_CompStat($2);}}
	;

StatList:
	Stat StatList2 												{if($1 == NULL && $2 == NULL){$$ = NULL;}else{$$=insert_StatList($1, $2);}}
	;

StatList2:
	SEMIC Stat StatList2 										{if($2 == NULL && $3 == NULL){$$=NULL;}else{$$=insert_StatList($2, $3);}}
	|															{$$=NULL;}
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
	|															{$$=NULL;}
	;

WritelnPList:
	LBRAC Expr WritelnPList2 RBRAC								{$$=insert_WritelnPList($2, $3);}
	| LBRAC STRING WritelnPList2 RBRAC						 	{$$=insert_WritelnPList2($2, $3);}
	;

WritelnPList2:
	COMMA STRING WritelnPList2 									{$$=insert_WritelnPList2($2, $3);}
	| COMMA Expr WritelnPList2 									{$$=insert_WritelnPList($2, $3);}
	|															{$$=NULL;}
	;

Expr:
	Expr2 														{$$=insert_Expr(is_EXO, $1);}
	| Expr2 GREATER Expr2 										{$$=insert_ExprO($1, is_GREATER, $3);}
	| Expr2 LESS Expr2 											{$$=insert_ExprO($1, is_LESS, $3);}
	| Expr2 GEQUAL Expr2 										{$$=insert_ExprO($1, is_GEQUAL, $3);}
	| Expr2 EQUALS Expr2 										{$$=insert_ExprO($1, is_EQUALS, $3);}
	| Expr2 LEQUAL Expr2 										{$$=insert_ExprO($1, is_LEQUAL, $3);}
	| Expr2 DIFFERENT Expr2 									{$$=insert_ExprO($1, is_DIFFERENT, $3);}
	;

Expr2:
	Expr3														{$$=insert_Expr(is_EXO, $1);}
	| PLUS Expr3 												{$$=insert_ExprO(NULL, is_PLUS, $2);}
	| MINUS Expr3 												{$$=insert_ExprO(NULL, is_MINUS, $2);}
	| Expr2 MINUS Expr3 										{$$=insert_ExprO($1, is_SUB, $3);}
	| Expr2 AND Expr3 											{$$=insert_ExprO($1, is_AND, $3);}
	| Expr2 OR Expr3 											{$$=insert_ExprO($1, is_OR, $3);}
	| Expr2 PLUS Expr3 											{$$=insert_ExprO($1, is_PLUS, $3);}
	;

Expr3:
	Expr4														{$$=insert_Expr(is_EXO, $1);}
	| Expr3 MULT Expr4 											{$$=insert_ExprO($1, is_MULT, $3);}
	| Expr3 REALDIV Expr4 										{$$=insert_ExprO($1, is_REALDIV, $3);}
	| Expr3 DIV Expr4 											{$$=insert_ExprO($1, is_DIV, $3);}
	| Expr3 MOD Expr4	 										{$$=insert_ExprO($1, is_MOD, $3);}
	;


Expr4:
	LBRAC Expr RBRAC 											{$$=insert_Expr(is_EXO, $2);}
	| NOT Expr4 												{$$=insert_ExprO(NULL, is_NOT, $2);}
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
	|															{$$=NULL;}
	;

%%
int yyerror (char *s)
{

	printf ("Line %d, col %d: %s: %s\n", lineaux, colaux, s, yytext);

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
