%{
	#include <string.h>
	#include "estruturas.h"
	#include "y.tab.h"
%}
%{
	int col=1;
	int line=1;
	int colaux=0;
	int lineaux=0;
%}
HEXA				[0-9a-fA-F]+
INTLIT				[0-9]+
ID 				[a-zA-Z_$][a-zA-Z0-9_$]*
RESERVED	"abstract"|"continue"|"for"|"switch"|"assert"|"default"|"goto"|"package"|"synchronized"|"do"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"import"|"throws"|"case"|"enum"|"instanceof"|"transient"|"catch"|"extends"|"short"|"try"|"char"|"final"|"interface"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"null"|"--"|"++"
STARTCOMMENT			"/*"
ENDCOMMENT			"*/"
LINECOMMENT			"//".*
%X				comment
%%
"class"				{col += yyleng; return(CLASS);}
"public"			{col += yyleng; return(PUBLIC);}
"static"			{col += yyleng; return(STATIC);}
"void"				{col += yyleng; return(VOID);}
"String"			{col += yyleng; return(STRING);}
"int"				{col += yyleng; return(INT);}
"boolean"			{col += yyleng; return(BOOL);}
"true"				{col += yyleng; yylval.boole=(char*)strdup(yytext); return(BOOLLIT);}
"false"				{col += yyleng; yylval.boole=(char*)strdup(yytext); return(BOOLLIT);}
"new"				{col += yyleng; return(NEW);}
"if"				{col += yyleng; return(IF);}
"else"				{col += yyleng; return(ELSE);}
"while"				{col += yyleng; return(WHILE);}
".length"			{col += yyleng; return(DOTLENGTH);}
"Integer.parseInt"		{col += yyleng; return(PARSEINT);}
"System.out.println"		{col += yyleng; return(PRINT);}
"return"			{col += yyleng; return(RETURN);}

{RESERVED}			{col += yyleng; return(RESERVED);}

"("				{col += yyleng; return(OCURV);}
")"				{col += yyleng; return(CCURV);}
"{"				{col += yyleng; return(OBRACE);}
"}"				{col += yyleng; return(CBRACE);}
"["				{col += yyleng; return(OSQUARE);}
"]"				{col += yyleng; return(CSQUARE);}
"&&"				{col += yyleng; return(AND);}
"||"				{col += yyleng; return(OR);}
"<"				{col += yyleng; return(GREATER);}
">"				{col += yyleng; return(LESS);}
"<="				{col += yyleng; return(LEQUAL);}
">="				{col += yyleng; return(GEQUAL);}
"=="				{col += yyleng; return(EQUALS);}
"!="				{col += yyleng; return(DIFFERENT);}
"+"		 		{col += yyleng; return(PLUS);}
"-"				{col += yyleng; return(MINUS);}
"*"				{col += yyleng; return(MULT);}
"/"				{col += yyleng; return(DIV);}
"%"				{col += yyleng; return(MOD);}
"!"				{col += yyleng; return(NOT);}
"="				{col += yyleng; return(ASSIGN);}
";"				{col += yyleng; return(SEMIC);}
","				{col += yyleng; return(COMMA);}
"0x"{HEXA}			{col += yyleng; return(INTLIT);}
{INTLIT}            		{col += yyleng; yylval.value=atoi(yytext); return(INTLIT);}
{ID}				{col += yyleng; yylval.id=(char*)strdup(yytext); return(ID);}
"\n" 				{line++; col=1;}
"\t" 				{col += yyleng;}
" "				{col++;}
.				{printf("Line %d, col %d: illegal character ('%s')\n", line, col, yytext); col += yyleng;}

{LINECOMMENT}			;
{STARTCOMMENT}			{lineaux=line; colaux=col; BEGIN(comment);}
<comment><<EOF>>		{printf("Line %d, col %d: unterminated comment\n", lineaux, colaux); BEGIN 0;}
<comment>.			{col++;}
<comment>"\n"			{col=1; line++;}
<comment>{ENDCOMMENT}		{BEGIN 0; col+=yyleng;}						
%%
int yywrap()
{
	return 1;
}

