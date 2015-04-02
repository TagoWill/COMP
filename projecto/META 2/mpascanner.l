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
":="					{col += yyleng; return(ASSIGN);}
begin					{col += yyleng; return(BEGIN)}
":"						{col += yyleng; return(COLON)}
","						{col += yyleng; return(COMMA)}
do						{col += yyleng; return(DO)}
"."						{col += yyleng; return(DOT)}
else					{col += yyleng; return(ELSE)}
end						{col += yyleng; return(END)}
forward					{col += yyleng; return(FORWARD)}
function				{col += yyleng; return(FUNCTION)}
if						{col += yyleng; return(IF)}
"("						{col += yyleng; return(LBRAC)}
not						{col += yyleng; return(NOT)}
output					{col += yyleng; return(OUTPUT)}
paramstr				{col += yyleng; return(PARAMSTR)}
program					{col += yyleng; return(PROGRAM)}
")"						{col += yyleng; return(RBRAC)}
repeat					{col += yyleng; return(REPEAT)}
";"						{col += yyleng; return(SEMIC)}
then					{col += yyleng; return(THEN)}
until					{col += yyleng; return(UNTIL)}
val						{col += yyleng; return(VAL)}
var						{col += yyleng; return(VAR)}
while					{col += yyleng; return(WHILE)}
writeln					{col += yyleng; return(WRITELN)}

{RESERVED}				{col += yyleng; return(RESERVED)}

and 					{col += yyleng; return(AND)}
or 						{col += yyleng; return(OR)}
"<"						{col += yyleng; return(GREATER)}
">"						{col += yyleng; return(LESS)}
"="						{col += yyleng; return(EQUALS)}
"<>"					{col += yyleng; return(DIFFERENT)}
"<="					{col += yyleng; return(GEQUAL)}
">="					{col += yyleng; return(LEQUAL)}
"+"	 					{col += yyleng; return(PLUS)}
"-"	 					{col += yyleng; return(MINUS)}
"*"						{col += yyleng; return(MULT)}
"/"						{col += yyleng; return(DIV)}
mod						{col += yyleng; return(MOD)}
div						{col += yyleng; return(DIV)}

{INTLIT}                {col += yyleng; yylval.value=atoi(yytext); return(INTLIT);}
{ID}					{col += yyleng; yylval.id=(char*)strdup(yytext); return(ID);}
({INTLIT}+("."{INTLIT}*)?|"."{INTLIT}+)([eE][+-]?{INTLIT}+)?	{col+=yyleng; yylval.value=atoi(yytext); return(REALLIT);}
'([^\n']|''|\\.)*'      {col+=yyleng; yylval.str=(char*)strdup(yytext); return(STRING);}
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

