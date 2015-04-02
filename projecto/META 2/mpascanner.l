%{
	int col=1;
	int line=1;
	int colaux=0;
	int lineaux=0;
%}
%option case-insensitive
ID 				[a-zA-Z][a-zA-Z0-9]*
INTLIT			[0-9]+
RESERVED    abs|arctan|array|case|char|chr|const|cos|dispose|downto|eof|eoln|exp|file|for|get|goto|in|input|label|ln|maxint|new|nil|odd|of|ord|pack|packed|page|pred|procedure|put|read|readln|record|reset|rewrite|round|set|sin|sqr|sqrt|succ|text|to|trunc|type|unpack|with|write
STARTCOMMENT	"(*"
STARTCOMMENT2	"{"
ENDCOMMENT		"*)"
ENDCOMMENT2		"}"
LINECOMMENT		"//".*
%X				comment
%%
":="					{printf("ASSIGN\n"); col += yyleng;}
begin					{printf("BEGIN\n"); col += yyleng;}
":"						{printf("COLON\n"); col += yyleng;}
","						{printf("COMMA\n"); col += yyleng;}
do						{printf("DO\n"); col += yyleng;}
"."						{printf("DOT\n"); col += yyleng;}
else					{printf("ELSE\n"); col += yyleng;}
end						{printf("END\n"); col += yyleng;}
forward					{printf("FORWARD\n"); col += yyleng;}
function				{printf("FUNCTION\n"); col += yyleng;}
if						{printf("IF\n"); col += yyleng;}
"("						{printf("LBRAC\n"); col += yyleng;}
not						{printf("NOT\n"); col += yyleng;}
output					{printf("OUTPUT\n"); col += yyleng;}
paramstr				{printf("PARAMSTR\n"); col += yyleng;}
program					{printf("PROGRAM\n"); col += yyleng;}
")"						{printf("RBRAC\n"); col += yyleng;}
repeat					{printf("REPEAT\n"); col += yyleng;}
";"						{printf("SEMIC\n"); col += yyleng;}
then					{printf("THEN\n"); col += yyleng;}
until					{printf("UNTIL\n"); col += yyleng;}
val						{printf("VAL\n"); col += yyleng;}
var						{printf("VAR\n"); col += yyleng;}
while					{printf("WHILE\n"); col += yyleng;}
writeln					{printf("WRITELN\n"); col += yyleng;}

{RESERVED}				{printf("RESERVED\n"); col += yyleng;}

and 					{printf("OP1(%s)\n", yytext); col += yyleng;}
or 						{printf("OP1(%s)\n", yytext); col += yyleng;}
"<"						{printf("OP2(%s)\n", yytext); col += yyleng;}
">"						{printf("OP2(%s)\n", yytext); col += yyleng;}
"="						{printf("OP2(%s)\n", yytext); col += yyleng;}
"<>"					{printf("OP2(%s)\n", yytext); col += yyleng;}
"<="					{printf("OP2(%s)\n", yytext); col += yyleng;}
">="					{printf("OP2(%s)\n", yytext); col += yyleng;}
"+"	 					{printf("OP3(%s)\n", yytext); col += yyleng;}
"-"	 					{printf("OP3(%s)\n", yytext); col += yyleng;}
"*"						{printf("OP4(%s)\n", yytext); col += yyleng;}
"/"						{printf("OP4(%s)\n", yytext); col += yyleng;}
mod						{printf("OP4(%s)\n", yytext); col += yyleng;}
div						{printf("OP4(%s)\n", yytext); col += yyleng;}

{INTLIT}                {printf("INTLIT(%s)\n",yytext); col += yyleng;}
{ID}					{printf("ID(%s)\n",yytext); col += yyleng;}
({INTLIT}+("."{INTLIT}*)?|"."{INTLIT}+)([eE][+-]?{INTLIT}+)?	{printf("REALLIT\n"); col+=yyleng;}
'([^\n']|''|\\.)*'      {printf("STRING\n"); col+=yyleng;}
"\n" 					{line++; col=1;}
"\t" 					{col += yyleng;}
" "						{col++;}


{LINECOMMENT}			;
{STARTCOMMENT}			{lineaux=line; colaux=col; BEGIN(comment);}
<comment><<EOF>>		{printf("Line %d, col %d: unterminated comment\n", lineaux, colaux); BEGIN 0;}
<comment>.				{col++;}
<comment>"\n"			{col=1; line++;}
<comment>{ENDCOMMENT}	{BEGIN 0; col+=yyleng;}						
%%
int main()
{
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}

