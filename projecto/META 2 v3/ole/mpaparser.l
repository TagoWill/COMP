%X COMMENT

num					[0-9]+
char				[a-z]
exp					((?i:e)[+-]?{num})
%{
	#include <stdio.h>
	#include <string.h>
	/*alterd*/
	#include "structures.h"
	#include "y.tab.h"
	int line=1, col=1,comline,comcol;
%}

%option nounput

%%
"'"("''"|[^'\n])*"'"				{yylval.string=malloc(sizeof(char)*(yyleng+1));strcpy(yylval.string,yytext);col+=yyleng;return STRING;}
"'"("''"|[^'\n])*				{col+=yyleng;printf("Line %d, col %d: unterminated string\n",line,col);}
":="						{col+=yyleng;return ASSIGN;}
":"						{col+=yyleng;return COLON;}
","						{col+=yyleng;return COMMA;}
"."						{col+=yyleng;return DOT;}
";"						{col+=yyleng;return SEMIC;}
(?i:"begin")					{col+=yyleng;return BEGINS;}
(?i:"do")					{col+=yyleng;return DO;}

(?i:"and")					{col+=yyleng;return AND;}
(?i:"or")					{col+=yyleng;return OR;}

"<"						{col+=yyleng;return LT;}
">"						{col+=yyleng;return GT;}
"="						{col+=yyleng;return EQ;}
"<>"						{col+=yyleng;return NEQ;}
"<="						{col+=yyleng;return LEQ;}
">="						{col+=yyleng;return GEQ;}

"+"						{col+=yyleng;return PLUS;}
"-"						{col+=yyleng;return MINUS;}

"*"						{col+=yyleng;return MULT;}
"/"						{col+=yyleng;return REALDIV;}
(?i:"mod")					{col+=yyleng;return MOD;}
(?i:"div")					{col+=yyleng;return DIV;}

(?i:"else")					{col+=yyleng;return ELSE;}
(?i:"end")					{col+=yyleng;return END;}
(?i:"forward")					{col+=yyleng;return FORWARD;}
(?i:"function")					{col+=yyleng;return FUNCTION;}
(?i:"if")					{col+=yyleng;return IF;}
"("						{col+=yyleng;return LBRAC;}
")"						{col+=yyleng;return RBRAC;}
(?i:"not")					{col+=yyleng;return NOT;}
(?i:"output")					{col+=yyleng;return OUTPUT;}
(?i:"paramstr")					{col+=yyleng;return PARAMSTR;}
(?i:"program")					{col+=yyleng;return PROGRAM;}
(?i:"repeat")					{col+=yyleng;return REPEAT;}
(?i:"then")					{col+=yyleng;return THEN;}
(?i:"until")					{col+=yyleng;return UNTIL;}
(?i:"val")					{col+=yyleng;return VAL;}
(?i:"var")					{col+=yyleng;return VAR;}
(?i:"while")					{col+=yyleng;return WHILE;}
(?i:"writeln")					{col+=yyleng;return WRITELN;}
(?i:"abs"|"arctan"|"char"|"chr"|"cos"|"dispose"|"eof"|"eoln"|"exp"|"get"|"input"|"ln"|"maxint"|"new"|"odd"|"ord"|"pack"|"page"|"pred"|"put"|"read"|"readln"|"reset"|"rewrite"|"round"|"sin"|"sqr"|"sqrt"|"succ"|"text"|"trunc"|"unpack"|"write"|"array"|"case"|"const"|"downto"|"file"|"for"|"goto"|"in"|"label"|"nil"|"of"|"packed"|"procedure"|"record"|"set"|"to"|"type"|"with")			{col+=yyleng;return RESERVED;}

(?i:{char})(?i:{num}|{char})*	{yylval.string=malloc(sizeof(char)*(yyleng+1));strcpy(yylval.string,yytext);col+=yyleng;return ID;}
{num}				{yylval.string=malloc(sizeof(char)*(yyleng+1));strcpy(yylval.string,yytext);col+=yyleng;return INTLIT;}
{num}"."{num}{exp}?|{num}{exp} 	{yylval.string=malloc(sizeof(char)*(yyleng+1));strcpy(yylval.string,yytext);col+=yyleng;return REALLIT;}

"(*"|"{"					{BEGIN COMMENT; comline=line; comcol=col;col+=yyleng;}
<COMMENT>"\n"					{line +=1;col=1;}
<COMMENT>"*)"|"}"				{col+=yyleng; BEGIN 0;}
<COMMENT>.					{col += yyleng;}
<COMMENT><<EOF>>				{printf("Line %d, col %d: unterminated comment\n",comline,comcol);col+=yyleng; return 0;}
(" "|\t)+					{col+=yyleng;}
\n 						{line++; col=1;}

.						{printf("Line %d, col %d: illegal character ('%s')\n",line,col,yytext);col+=yyleng;}

<<EOF>>						{col+=yyleng;return 0;}

%%

int yywrap(){
	return 1;
}

