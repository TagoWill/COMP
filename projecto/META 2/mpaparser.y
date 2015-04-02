%{
	#include <stdio.h>
	#include <string.h>
	#include "estruturas.h"
	#include "funcoes.h"
	
	extern int yylex(void);
	int yyerror(char *s);
	extern int line, col, yyleng;
	extern char* yytext;
	is_program* my_program = NULL;
%}

%union {
	int value;
	char* boole;
	char* id;

	is_program* st;
	is_program* prg;
	is_repfieldmethod* rfm;
	is_fielddecl* fdd;
	is_methoddecl* mdd;
	is_formalparams* flp;
	is_repcommatypeid* rcti;
	is_repvardecl* rvd;
	is_vardecl* vrd;
	is_repcommaid* rci;
	is_type* typ;
	is_rep_statement* rstt;
	is_statement* stt;
	is_expr* exp;
	is_expr2* exp2;
	is_args* arg;
	is_repcommaexpr* rarg;
}

%token CLASS
%token PUBLIC
%token STATIC
%token VOID
%token STRING
%token INT
%token BOOL
%token NEW
%token IF
%token ELSE
%token WHILE
%token DOTLENGTH
%token PARSEINT
%token PRINT
%token RETURN
%token OCURV
%token CCURV
%token OBRACE
%token CBRACE
%token OSQUARE
%token CSQUARE
%token NOT
%token ASSIGN
%token SEMIC
%token COMMA
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
%token <value> INTLIT
%token <id> ID
%token <boole> BOOLLIT

%type<st> Start
%type<prg> Program
%type<rfm> RepFieldMethod
%type<fdd> FieldDecl
%type<mdd> MethodDecl
%type<flp> FormalParams
%type<rcti> RepCommaTypeId
%type<rvd> RepVarDecl
%type<vrd> VarDecl
%type<rci> RepCommaId
%type<typ> Type
%type<rstt> RepStatement
%type<stt> Statement
%type<exp> Expr
%type<exp2> Expr2
%type<arg> Args
%type<rarg> RepCommaExpr

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
Start:		Program								{my_program=$$;}
		;

Program:	CLASS ID OBRACE RepFieldMethod CBRACE				{$$=insert_prg($2, $4);}
		;

RepFieldMethod:	FieldDecl RepFieldMethod					{$$=insert_rep_field($1, $2);}
		| MethodDecl RepFieldMethod					{$$=insert_rep_method($1, $2);}
		|								{$$=NULL;}
		;
				
FieldDecl:	STATIC VarDecl							{$$=insert_fielddecl($2);}
		;

MethodDecl:	PUBLIC STATIC Type ID OCURV FormalParams CCURV OBRACE RepVarDecl RepStatement CBRACE		{$$=insert_methodd_typein($3, $4, $6, $9, $10);}
		| PUBLIC STATIC Type ID OCURV CCURV OBRACE RepVarDecl RepStatement CBRACE			{$$=insert_methodd_typeout($3, $4, $8, $9);}
		| PUBLIC STATIC VOID ID OCURV FormalParams CCURV OBRACE RepVarDecl RepStatement CBRACE		{$$=insert_methodd_voidin($4, $6, $9, $10);}
		| PUBLIC STATIC VOID ID OCURV CCURV OBRACE RepVarDecl RepStatement CBRACE			{$$=insert_methodd_voidout($4, $8, $9);}
		;

FormalParams:	Type ID RepCommaTypeId		 				{$$=insert_formalparams1($1, $2, $3);}
		| STRING OSQUARE CSQUARE ID					{$$=insert_formalparams2($4);}
		;
				
RepCommaTypeId:	COMMA Type ID RepCommaTypeId					{$$=insert_rep_commatypeid($2, $3, $4);}
		|								{$$=NULL;}
		;

RepVarDecl:	VarDecl RepVarDecl						{$$=insert_rep_vardecl($1, $2);}
		|								{$$=NULL;}
		;
				
VarDecl:	Type ID RepCommaId SEMIC					{$$=insert_vardecl($1, $2, $3);}
		;

				
RepCommaId:	COMMA ID RepCommaId						{$$=insert_rep_commaid($2, $3);}
		|								{$$=NULL;}
		;
				
Type:		BOOL								{$$=insert_bool();}
		| INT								{$$=insert_int();}
		| INT OSQUARE CSQUARE						{$$=insert_int2();}
		| BOOL OSQUARE CSQUARE						{$$=insert_bool2();}
		;

RepStatement:	Statement RepStatement						{$$=insert_rep_statement($1, $2);}
		|								{$$=NULL;}
		;
				
				
Statement:	RETURN SEMIC							{$$=insert_return_statement();}
		| RETURN Expr SEMIC						{$$=insert_return_statement2($2);}
		| ID ASSIGN Expr SEMIC						{$$=insert_id_assign($1, $3);}
		| ID OSQUARE Expr CSQUARE ASSIGN Expr SEMIC			{$$=insert_id_assign2($1, $3, $6);}
		| OBRACE RepStatement CBRACE					{$$=insert_rep_statement2($2);}
		| IF OCURV Expr CCURV Statement					{$$=insert_if_expr($3, $5);}
		| IF OCURV Expr CCURV Statement ELSE Statement			{$$=insert_if_expr_else($3, $5, $7);}
		| WHILE OCURV Expr CCURV Statement				{$$=insert_while($3, $5);}
		| PRINT OCURV Expr CCURV SEMIC					{$$=insert_print($3);}
		;
				
Expr:		PLUS Expr %prec NOT						{$$=insert_plus(is_PLUS, $2);}
		| MINUS Expr %prec NOT						{$$=insert_minus(is_MINUS, $2);}
		| NOT Expr							{$$=insert_not(is_NOT, $2);}
		| NEW INT OSQUARE Expr CSQUARE					{$$=insert_new_int($4);}
		| NEW BOOL OSQUARE Expr CSQUARE					{$$=insert_new_bool($4);}
		| Expr AND Expr							{$$=insert_and($1, is_AND, $3);}
		| Expr OR Expr							{$$=insert_or($1, is_OR, $3);}
		| Expr EQUALS Expr						{$$=insert_equals($1, is_EQUALS, $3);}
		| Expr DIFFERENT Expr						{$$=insert_different($1, is_DIFFERENT, $3);}
		| Expr GREATER Expr						{$$=insert_greater($1, is_GREATER, $3);}
		| Expr LESS Expr						{$$=insert_less($1, is_LESS, $3);}
		| Expr LEQUAL Expr						{$$=insert_lequal($1, is_LEQUAL, $3);}
		| Expr GEQUAL Expr						{$$=insert_gequal($1, is_GEQUAL, $3);}
		| Expr PLUS Expr						{$$=insert_expr_plus($1, is_PLUS, $3);}	
		| Expr MINUS Expr						{$$=insert_expr_minus($1, is_MINUS, $3);}
		| Expr MULT Expr						{$$=insert_expr_mult($1, is_MULT, $3);}
		| Expr DIV Expr							{$$=insert_expr_div($1, is_DIV, $3);}
		| Expr MOD Expr							{$$=insert_expr_mod($1, is_MOD, $3);}
		| Expr2								{$$=insert_expr2($1);}
		;

Expr2:		ID OCURV Args CCURV						{$$=insert_ID3($1, $3);}
		| ID OCURV CCURV						{$$=insert_ID2($1);}
		| ID								{$$=insert_ID($1);}
		| INTLIT							{$$=insert_INTLIT($1);}
		| BOOLLIT							{$$=insert_BOOLIT($1);}
		| Expr2 OSQUARE Expr CSQUARE					{$$=insert_expr2_expr($1, $3);}
		| Expr DOTLENGTH						{$$=insert_dotlength($1);}
		| OCURV Expr CCURV						{$$=insert_OCURV_expr_CCURV($2);}
		| PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV			{$$=insert_parseint($3, $5);}
		;

Args:		Expr RepCommaExpr						{$$=insert_args($1, $2);}
		;

RepCommaExpr:	COMMA Expr RepCommaExpr						{$$=insert_repcommaexpr($2, $3);}
		|								{$$=NULL;}
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
	show_program(my_program);
	return 0;
}
