%{
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include "functions.h"

	int yylex();
	int yyerror(char *s);

	extern int line;
	extern int col;
	extern char *yytext;
	extern int yyleng;
	int yydebug=1;
	int error = 0;

	Node *tree = NULL;
	/*Alt1*/
%}

%union{
	char *string;
	float real;
	Node *nodeptr;
}

%token <string> STRING
%token ASSIGN
%token COLON
%token COMMA
%token DOT
%token SEMIC
%token BEGINS
%token DO

%token AND;
%token OR;

%token LT;
%token GT;
%token EQ;
%token NEQ;
%token LEQ;
%token GEQ;

%token PLUS;
%token MINUS;

%token MULT;
%token REALDIV;
%token MOD;
%token DIV;

%token ELSE
%token END
%token FORWARD
%token FUNCTION
%token IF
%token LBRAC
%token RBRAC
%token NOT
%token OUTPUT
%token PARAMSTR
%token PROGRAM
%token REPEAT
%token THEN
%token UNTIL
%token VAL
%token VAR
%token WHILE
%token WRITELN
%token RESERVED

%token <string> ID 
%token <string> INTLIT
%token <string> REALLIT

%start start

%type <nodeptr> start Prog ProgHeading ProgBlock VarPart VarPart2 VarDeclaration IDList IDList2 FuncPart FuncDeclaration FuncHeading FuncIdent

%type <nodeptr> FormalParamList FormalParms FormalParms2 FuncBlock StatPart CompStat StatList StatList2 Stat WritelnPList WritelnPList2 Expr SimpleExpr Term Factor ParamList ParamList2 

%right	ASSIGN
%left	EQ NEQ LT GT LEQ GEQ
%left 	PLUS MINUS OR
%left   MULT REALDIV DIV MOD AND
%right	NOT 
%left 	RBRAC LBRAC 
%right 	THEN ELSE

%%

start:			Prog 							{$$ = $1; tree = $$;}
	;

Prog:			ProgHeading SEMIC ProgBlock DOT				{$$ = addNode(Program,add($1,$3));}
	;

ProgHeading: 		PROGRAM ID LBRAC OUTPUT	RBRAC				{$$ = leaf(Id,$2);}
	;


ProgBlock: 		VarPart FuncPart StatPart 				{$$ = add(addNode(VarPart,$1),add(addNode(FuncPart,$2),
$3));}				
	;

VarPart: 		VAR VarDeclaration SEMIC VarPart2			{$$ = add(addNode(VarDecl,$2), $4);}
	|									{$$ = NULL;}
	;

VarPart2:		VarDeclaration SEMIC VarPart2				{$$ = add(addNode(VarDecl, $1), $3);}
	|									{$$ = NULL;}
	;

VarDeclaration:		IDList COLON ID 					{$$ = add($1,leaf(Id,$3));}
	;

IDList: 		ID IDList2						{$$ = add(leaf(Id,$1),$2);}
	;

IDList2: 		COMMA ID IDList2					{$$ = add(leaf(Id,$2),$3);}
	|		/*NULL*/						{$$ = NULL;}
	;

FuncPart: 		FuncDeclaration SEMIC FuncPart				{$$ = add($1,$3);}
	| 									{$$ = NULL;}
	;

FuncDeclaration: 	FuncHeading SEMIC FORWARD				{$$ = addNode(FuncDecl, $1);}
	|		FuncIdent SEMIC FuncBlock				{$$ = addNode(FuncDef2, add($1,$3));}
	|		FuncHeading SEMIC FuncBlock				{$$ = addNode(FuncDef, add($1,$3));}
	;

FuncHeading: 		FUNCTION ID FormalParamList COLON ID 			{$$ = add(leaf(Id,$2),add(addNode(FuncParams, $3),leaf(Id,$5)));}
	|		FUNCTION ID COLON ID					{$$ = add(leaf(Id,$2),add(leaf(FuncParams, NULL),leaf(Id,$4)));}
	;

FuncIdent:		FUNCTION ID 						{$$ = leaf(Id,$2);}
	;

FormalParamList: 	LBRAC FormalParms RBRAC					{$$ = $2;}
	;

FormalParms: 		VAR IDList COLON ID FormalParms2			{$$ = add(addNode(VarParams,add($2,leaf(Id,$4))), $5);}
	|		IDList COLON ID FormalParms2 				{$$ = add(addNode(Params,add($1,leaf(Id,$3))),$4);}
	;

FormalParms2: 		SEMIC FormalParms 					{$$ = $2;}
	| 		/*NULL*/						{$$ = NULL;}
	;

FuncBlock: 		VarPart StatPart					{$$ = add(addNode(VarPart, $1),$2);}
	;

StatPart: 		CompStat						{$$ = $1==NULL?leaf(StatList, NULL):$1;}
	;

CompStat: 		BEGINS StatList END					{$$ = $2;}
	;

StatList: 		Stat StatList2						{$$ = ($1!=NULL && $2 != NULL)?addNode(StatList,add($1,$2)):$1;}
	;									

StatList2:		SEMIC Stat StatList2					{$$ = add($2,$3);}
	|									{$$ = NULL;}
	;


Stat:			CompStat						{$$ = add($1,NULL);}
	|		IF Expr THEN Stat ELSE Stat 				{$$ = addNode(IfElse,add($2,add(($4==NULL/*||$4->next!=NULL*/)?addNode(StatList, $4):$4,($6==NULL/*||$6->next!=NULL*/)?addNode(StatList, $6):$6)));}
	|		IF Expr THEN Stat 					{$$ = addNode(IfElse,add($2,($4==NULL/*||$4->next!=NULL*/)?add(addNode(StatList,$4),leaf(StatList,NULL)):add($4, leaf(StatList, NULL))));}
	|		WHILE Expr DO Stat 					{$$ = addNode(While,add($2,($4==NULL/*||$4->next!=NULL*/)?addNode(StatList, $4):$4));}
	|		REPEAT StatList UNTIL Expr				{$$ = addNode(Repeat, add(($2==NULL/* || $2->next!=NULL*/)?addNode(StatList, $2):$2,$4));}
	|		VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC	{$$ = addNode(ValParam,add($5,leaf(Id,$8)));}
	| 		ID ASSIGN Expr						{$$ = addNode(Assign,add(leaf(Id,$1),$3));}
	| 		WRITELN WritelnPList					{$$ = addNode(Writeln,$2);}
	|		/*NULL*/						{$$ = NULL;}
	;

WritelnPList: 		LBRAC Expr WritelnPList2 RBRAC				{$$ = add($2,$3);}
	|		LBRAC STRING WritelnPList2 RBRAC			{$$ = add(leaf(String,$2),$3);}
	|									{$$ = NULL;}
	;

WritelnPList2:		COMMA Expr WritelnPList2				{$$ = add($2,$3);}
	|		COMMA STRING WritelnPList2				{$$ = add(leaf(String,$2),$3);}
	|		/*NULL*/						{$$ = NULL;}
	;

Expr:			SimpleExpr 						{$$ = $1;}		
	|		SimpleExpr EQ SimpleExpr				{$$ = addNode(Eq,add($1,$3));}
	|		SimpleExpr GT SimpleExpr				{$$ = addNode(Gt,add($1,$3));}
	|		SimpleExpr LT SimpleExpr				{$$ = addNode(Lt,add($1,$3));}
	|		SimpleExpr NEQ SimpleExpr				{$$ = addNode(Neq,add($1,$3));}
	|		SimpleExpr GEQ SimpleExpr				{$$ = addNode(Geq,add($1,$3));}
	|		SimpleExpr LEQ SimpleExpr				{$$ = addNode(Leq,add($1,$3));}
	;

SimpleExpr:		PLUS SimpleExpr						{$$ = addNode(Plus,$2);}
	|		MINUS SimpleExpr					{$$ = addNode(Minus,$2);}		
	|		SimpleExpr PLUS Term					{$$ = addNode(Add,add($1,$3));}		 
	|		SimpleExpr MINUS Term					{$$ = addNode(Sub,add($1,$3));}
	|		SimpleExpr OR Term					{$$ = addNode(Or,add($1,$3));}
	|		Term							{$$ = $1;}
	;

Term:			Factor 							{$$ = $1;}
	|		Term MULT Factor					{$$ = addNode(Mul,add($1,$3));}
	|		Term DIV Factor						{$$ = addNode(Div,add($1,$3));}
	|		Term REALDIV Factor					{$$ = addNode(RealDiv,add($1,$3));}
	|		Term MOD Factor						{$$ = addNode(Mod,add($1,$3));}
	|		Term AND Factor						{$$ = addNode(And,add($1,$3));}
	;
	
Factor:			ID ParamList 						{$$ = addNode(Call, add(leaf(Id,$1),$2));}		
	|		ID							{$$ = leaf(Id,$1);}
	|		INTLIT							{$$ = leaf(Intlit,$1);}
	|		REALLIT							{$$ = leaf(Reallit,$1);}
	|		LBRAC Expr RBRAC					{$$ = $2;}
	|		NOT Factor						{$$ = addNode(Not,$2);}
	;
			
ParamList2:		COMMA Expr ParamList2					{$$ = add($2,$3);}
	|									{$$ = NULL;}
	;

ParamList: 		LBRAC Expr ParamList2 RBRAC				{$$ = add($2,$3);}
	;


%%

int yyerror(char *s){
	printf("Line %d, col %d: %s: %s\n", line,(col-yyleng),s,yytext);
	error = 1;
	return 0;
}

int main(int argc, char *argv[]){
	int ast = 0, i;
	for(i=0;i<argc;i++){
		if(!strcmp(argv[i], "-t")){
			ast = 1;
		}
	}
	yyparse();

	if(error == 0){
		if(tree != NULL){
			if(ast == 1){
				printNode(tree,0);
			}
		}
	}
	return 0;
}

