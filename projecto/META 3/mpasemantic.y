%{
	#include "structures.h"
	#include "functions.h"
	#include "semantics.h"
	#include "symbol_table.h"
	#include "shows.h"
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	
	extern int lineaux;
	extern int colaux;
	extern char *yytext;
	extern int yyleng;
	int erros = 0;

	table *symtab=NULL;

	is_Nos* myprogram = NULL;
%}
%locations
%union {
	char *str;
	is_Nos* paratodos;
	
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

%right  ASSIGN
%left	GREATER LESS GEQUAL LEQUAL EQUALS DIFFERENT
%left	PLUS MINUS OR
%left 	MULT REALDIV DIV MOD AND
%right 	NOT 
%left	RBRAC LBRAC
%right  THEN ELSE

%type <paratodos> Prog
%type <paratodos> ProgHeading
%type <paratodos> ProgBlock
%type <paratodos> VarPart
%type <paratodos> FuncPart
%type <paratodos> StatPart
%type <paratodos> VarPart2
%type <paratodos> VarDeclaration
%type <paratodos> IDList
%type <paratodos> IDList2
%type <paratodos> FuncDeclaration
%type <paratodos> FuncHeading
%type <paratodos> FuncIdent
%type <paratodos> FormalParamList
%type <paratodos> FormalParams
%type <paratodos> FormalParams2
%type <paratodos> FuncBlock
%type <paratodos> CompStat
%type <paratodos> StatList
%type <paratodos> StatList2
%type <paratodos> Stat
%type <paratodos> WritelnPList
%type <paratodos> WritelnPList2
%type <paratodos> Expr
%type <paratodos> Expr2
%type <paratodos> Expr3
%type <paratodos> Expr4
%type <paratodos> ParamList
%type <paratodos> ParamList2

%%
Prog: 
	ProgHeading SEMIC ProgBlock DOT 							{$$=inserir_no(is_PROGRAM, inserir_irmao($1, $3),@1.first_column);	myprogram=$$;}
	;

ProgHeading:
	PROGRAM	ID LBRAC OUTPUT RBRAC 								{$$=inserir_valor(is_ID, $2, @2.first_column);}
	;

ProgBlock:
	VarPart FuncPart StatPart 									{$$=inserir_irmao(inserir_no(is_VARPART, $1,@1.first_column), inserir_irmao(inserir_no(is_FUNCPART,$2,@2.first_column), $3));}
	;

VarPart:
	VAR VarDeclaration SEMIC VarPart2 							{$$=inserir_irmao(inserir_no(is_VARDECL, $2,@2.first_column), $4);}
	|															{$$=NULL;}
	;

VarPart2:
	VarDeclaration SEMIC VarPart2 								{$$=inserir_irmao(inserir_no(is_VARDECL, $1,@1.first_column), $3);}
	|															{$$=NULL;}
	;

VarDeclaration:
	IDList COLON ID 											{$$=inserir_irmao($1, inserir_valor(is_ID, $3, @3.first_column));}
	;

IDList:
	ID IDList2 													{$$=inserir_irmao(inserir_valor(is_ID, $1, @1.first_column), $2);}
	;

IDList2:
	COMMA ID IDList2 											{$$=inserir_irmao(inserir_valor(is_ID, $2, @2.first_column), $3);}
	|															{$$=NULL;}
	;

FuncPart:
	FuncDeclaration SEMIC FuncPart 								{$$=inserir_irmao($1, $3);}
	| 															{$$=NULL;}
	;

FuncDeclaration:
	FuncHeading SEMIC FORWARD 									{$$=inserir_no(is_FUNCDECL, $1,@1.first_column);}
	| FuncIdent SEMIC FuncBlock 								{$$=inserir_no(is_FUNCDEF2, inserir_irmao($1, $3),@1.first_column);}
	| FuncHeading SEMIC FuncBlock 								{$$=inserir_no(is_FUNCDEF, inserir_irmao($1, $3),@1.first_column);}
	;

FuncHeading:
	FUNCTION ID FormalParamList COLON ID 						{$$=inserir_irmao(inserir_valor(is_ID,$2, @2.first_column), inserir_irmao(inserir_no(is_FUNCPARAMS, $3,@3.first_column), inserir_valor(is_ID, $5, @5.first_column)));}
	| FUNCTION ID COLON ID 										{$$=inserir_irmao(inserir_valor(is_ID,$2,@2.first_column), inserir_irmao(inserir_no(is_FUNCPARAMS, NULL,@1.first_column) , inserir_valor(is_ID, $4, @4.first_column)));}
	;

FuncIdent:
	FUNCTION ID 												{$$=inserir_valor(is_ID, $2,@2.first_column);}
	;

FormalParamList:
	LBRAC FormalParams RBRAC 									{$$=$2;}
	;

FormalParams:
	VAR IDList COLON ID FormalParams2							{$$ = inserir_irmao(inserir_no(is_VARPARAMS, inserir_irmao($2, inserir_valor(is_ID,$4,@4.first_column)),@2.first_column), $5);}
	| IDList COLON ID FormalParams2							{$$ = inserir_irmao(inserir_no(is_PARAMS, inserir_irmao($1, inserir_valor(is_ID,$3, @3.first_column)),@1.first_column), $4);}
	;

FormalParams2:
	SEMIC FormalParams 											{$$=$2;}
	|															{$$=NULL;}
	;

FuncBlock:
	VarPart StatPart 											{$$=inserir_irmao(inserir_no(is_VARPART,$1,@1.first_column), $2);}
	;

StatPart:
	CompStat 													{$$ = ($1 == NULL)?inserir_valor(is_STATLIST, NULL, @1.first_column):$1;}
	;

CompStat:
	BEG StatList END 											{$$=$2;}
	;

StatList:
	Stat StatList2 												{$$=($1 != NULL && $2 != NULL)?inserir_no(is_STATLIST, inserir_irmao($1,$2),@1.first_column):$1; }
	;

StatList2:
	SEMIC Stat StatList2 										{$$=inserir_irmao($2, $3);}
	|															{$$=NULL;}
	;

Stat:
	CompStat 													{$$=$1;}
	| IF Expr THEN Stat ELSE Stat  								{$$=inserir_no(is_IFELSE, inserir_irmao($2, inserir_irmao(($4 == NULL)?inserir_no(is_STATLIST, $4,@4.first_column):$4, ($6 == NULL)?inserir_no(is_STATLIST, $6,@6.first_column):$6)),@1.first_column);}
	| IF Expr THEN Stat  										{$$=inserir_no(is_IFELSE, inserir_irmao($2, ($4 == NULL)?inserir_irmao(inserir_no(is_STATLIST, NULL,@4.first_column),inserir_no(is_STATLIST,NULL,@1.first_column)):inserir_irmao($4,inserir_no(is_STATLIST,NULL,@1.first_column))),@1.first_column);}
	| WHILE Expr DO Stat 										{$$=inserir_no(is_WHILE, inserir_irmao($2, ($4 == NULL)?inserir_no(is_STATLIST,NULL,@4.first_column):$4), @1.first_column);}
	| REPEAT StatList UNTIL Expr 								{$$=inserir_no(is_REPEAT, inserir_irmao(($2==NULL)?inserir_no(is_STATLIST,NULL,@2.first_column):$2, $4),@1.first_column);}
	| VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC		{$$=inserir_no(is_VALPARAM, inserir_irmao($5, inserir_valor(is_ID,$8,@8.first_column)),@1.first_column);}
	| ID ASSIGN Expr 											{$$=inserir_no(is_ASSIGN, inserir_irmao(inserir_valor(is_ID, $1,@1.first_column), $3),@1.first_column);}
	| WRITELN WritelnPList 										{$$=inserir_no(is_WRITELN, $2,@1.first_column);}
	| WRITELN 													{$$=inserir_no(is_WRITELN, NULL,@1.first_column);}
	|															{$$=NULL;}
	;

WritelnPList:
	LBRAC Expr WritelnPList2 RBRAC								{$$=inserir_irmao($2, $3);}
	| LBRAC STRING WritelnPList2 RBRAC						 	{$$=inserir_irmao(inserir_valor(is_STRING, $2, @2.first_column), $3);}
	;

WritelnPList2:
	COMMA STRING WritelnPList2 									{$$=inserir_irmao(inserir_valor(is_STRING, $2, @2.first_column), $3);}
	| COMMA Expr WritelnPList2 									{$$=inserir_irmao($2, $3);}
	|															{$$=NULL;}
	;

Expr:
	Expr2 														{$$=$1;}
	| Expr2 GREATER Expr2 										{$$=inserir_no(is_GREATER, inserir_irmao($1, $3),@2.first_column);}
	| Expr2 LESS Expr2 											{$$=inserir_no(is_LESS, inserir_irmao($1, $3),@2.first_column);}
	| Expr2 GEQUAL Expr2 										{$$=inserir_no(is_GEQUAL, inserir_irmao($1, $3),@2.first_column);}
	| Expr2 EQUALS Expr2 										{$$=inserir_no(is_EQUALS, inserir_irmao($1, $3),@2.first_column);}
	| Expr2 LEQUAL Expr2 										{$$=inserir_no(is_LEQUAL, inserir_irmao($1, $3),@2.first_column);}
	| Expr2 DIFFERENT Expr2 									{$$=inserir_no(is_DIFFERENT, inserir_irmao($1, $3),@2.first_column);}
	;

Expr2:
	Expr3														{$$=$1;}
	| PLUS Expr3 												{$$=inserir_no(is_PLUS, $2,@1.first_column);}
	| MINUS Expr3 												{$$=inserir_no(is_MINUS, $2,@1.first_column);}
	| Expr2 MINUS Expr3 										{$$=inserir_no(is_SUB,inserir_irmao($1, $3),@2.first_column);}
	| Expr2 OR Expr3 											{$$=inserir_no(is_OR,inserir_irmao($1, $3),@2.first_column);}
	| Expr2 PLUS Expr3 											{$$=inserir_no(is_ADD,inserir_irmao($1, $3),@2.first_column);}
	;

Expr3:
	Expr4														{$$=$1;}
	| Expr3 MULT Expr4 											{$$=inserir_no(is_MULT,inserir_irmao($1, $3),@2.first_column);}
	| Expr3 REALDIV Expr4 										{$$=inserir_no(is_REALDIV,inserir_irmao($1, $3),@2.first_column);}
	| Expr3 DIV Expr4 											{$$=inserir_no(is_DIV,inserir_irmao($1, $3),@2.first_column);}
	| Expr3 AND Expr4 											{$$=inserir_no(is_AND,inserir_irmao($1, $3),@2.first_column);}
	| Expr3 MOD Expr4	 										{$$=inserir_no(is_MOD,inserir_irmao($1, $3),@2.first_column);}
	;


Expr4:
	LBRAC Expr RBRAC 											{$$=$2;}
	| NOT Expr4 												{$$=inserir_no(is_NOT, $2,@1.first_column);}
	| INTLIT 													{$$=inserir_valor(is_INTLIT, $1, @1.first_column);}
	| REALLIT 													{$$=inserir_valor(is_REALLIT, $1, @1.first_column);}
	| ID ParamList 												{$$=inserir_no(is_CALL, inserir_irmao(inserir_valor(is_ID, $1, @1.first_column), $2),@1.first_column);}
	| ID 														{$$=inserir_valor(is_ID, $1, @1.first_column);}
	;

ParamList:
	LBRAC Expr ParamList2 RBRAC									{$$=inserir_irmao($2, $3);}
	;

ParamList2:
	COMMA Expr ParamList2										{$$=inserir_irmao($2, $3);}
	|															{$$=NULL;}
	;

%%
int yyerror (char *s)
{

	printf ("Line %d, col %d: %s: %s\n", lineaux, colaux, s, yytext);

	erros=1;
	return 1;
}

int main(int argc, char *argv[])
{
	yyparse();
	int err = check_program(myprogram, NULL);
	if(erros != 1){
		if(argc == 2){
			if(strcmp("-t", argv[1])==0){
				show_prog(myprogram,0);
			}else if(strcmp("-s", argv[1])==0){
				imprimeTabelas(symtab);
			}
		}else if(argc == 3){
			if(strcmp("-t", argv[1])==0){
				if(strcmp("-s", argv[2])==0){
					show_prog(myprogram,0);
					printf("\n");
					imprimeTabelas(symtab);
				}
			}
			if(strcmp("-s", argv[1])==0){
				if(strcmp("-t", argv[2])==0){
					show_prog(myprogram,0);
					printf("\n");
					imprimeTabelas(symtab);
				}
			}
		}
	}
	return 0;
}
