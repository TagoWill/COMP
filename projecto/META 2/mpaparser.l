%{
	#include "structures.h"
    #include "y.tab.h"
    int col = 1;
    int line = 1;
    int colaux = 0;
    int lineaux = 0;
    
%}

%option case-insensitive

ID                                  [a-zA-Z][a-zA-Z0-9]*
INTLIT								[0-9]+
EXPOENTE                            [eE][+-]?{INTLIT}+
REALLIT                             ({INTLIT}+"."{INTLIT}+){EXPOENTE}?|{INTLIT}+{EXPOENTE}?
RESERVED    abs|arctan|array|case|char|chr|const|cos|dispose|downto|eof|eoln|exp|file|for|get|goto|in|input|label|ln|maxint|new|nil|odd|of|ord|pack|packed|page|pred|procedure|put|read|readln|record|reset|rewrite|round|set|sin|sqr|sqrt|succ|text|to|trunc|type|unpack|with|write

ASSIGN                              ":="
BEGIN                               begin
COLON                               ":"
COMMA                               ","
DO                                  do
DOT                                 "."
ELSE                                else
END                                 end
FORWARD                             forward
FUNCTION                            function
IF                                  if
LBRAC                               "("
NOT                                 not
OUTPUT                              output
PARAMSTR                            paramstr
PROGRAM                             program
RBRAC                               ")"
REPEAT                              repeat
SEMIC                               ;
THEN                                then
UNTIL                               until
VAL                                 val
VAR                                 var
WHILE                               while
WRITELN                             writeln
BLANKSPACE                          " "
TAB                                 "\t"
NEWLINE                             "\n"
STARTCOMMENT                        "(*"|"{"
ENDCOMMENT                          "*)"|"}"
%X                                  comment

%%
{STARTCOMMENT}              {lineaux=line; colaux=col; col += yyleng; BEGIN(comment);}
<comment><<EOF>>            {printf("Line %d, col %d: unterminated comment\n", lineaux, colaux); BEGIN 0;}
<comment>{NEWLINE}			{col=1; line++;}
<comment>{ENDCOMMENT}		{BEGIN 0; col+=yyleng;}
<comment>.                  {col++;}
{ASSIGN}                                                        {col +=yyleng; return ASSIGN;}
{BEGIN}                                                         {col +=yyleng;return BEG;}
{COLON}                                                         {col +=yyleng;return COLON;}
{COMMA}                                                         {col +=yyleng;return COMMA;}
{DO}                                                            {col +=yyleng;return DO;}
{DOT}                                                           {col +=yyleng;return DOT;}
{ELSE}                                                          {col +=yyleng;return ELSE;}
{END}                                                           {col +=yyleng; return END;}
{FORWARD}                                                       {col +=yyleng;return FORWARD;}
{FUNCTION}                                                      {col +=yyleng;return FUNCTION;}
{IF}                                                            {col +=yyleng;return IF;}
{LBRAC}                                                         {col +=yyleng;return LBRAC;}
{NOT}                                                           {col +=yyleng;return NOT;}
{OUTPUT}                                                        {col +=yyleng;return OUTPUT;}
{PARAMSTR}                                                      {col +=yyleng;return PARAMSTR;}
{PROGRAM}                                                       {col +=yyleng; return PROGRAM;}
{RBRAC}                                                         {col +=yyleng;return RBRAC;}
{REPEAT}                                                        {col +=yyleng;return REPEAT;}
{SEMIC}                                                         {col +=yyleng;return SEMIC;}
{THEN}                                                          {col +=yyleng;return THEN;}
{UNTIL}                                                         {col +=yyleng;return UNTIL;}
{VAL}                                                           {col +=yyleng;return VAL;}
{VAR}                                                           {col +=yyleng;return VAR;}
{WHILE}                                                         {col +=yyleng;return WHILE;}
{WRITELN}                                                       {col +=yyleng;return WRITELN;}
and 															{col += yyleng; return(AND);}
or 																{col += yyleng; return(OR);}
"<"																{col += yyleng; return(GREATER);}
">"																{col += yyleng; return(LESS);}
"="																{col += yyleng; return(EQUALS);}
"<>"															{col += yyleng; return(DIFFERENT);}
"<="															{col += yyleng; return(GEQUAL);}
">="															{col += yyleng; return(LEQUAL);}
"+"	 															{col += yyleng; return(PLUS);}
"-"	 															{col += yyleng; return(MINUS);}
"*"																{col += yyleng; return(MULT);}
"/"																{col += yyleng; return(DIV);}
mod																{col += yyleng; return(MOD);}
div																{col += yyleng; return(DIV);}

{RESERVED}                                                      {col +=yyleng;yylval.str=(char*)strdup(yytext);return RESERVED;}

{INTLIT}                                                        {col+=yyleng;yylval.str=(char*)strdup(yytext);return INTLIT;}
{ID}                                                            {col += yyleng; yylval.str=(char*)strdup(yytext); return ID;}
{REALLIT}                                                       {col+=yyleng;yylval.str=(char*)strdup(yytext);return REALLIT;}
'([^\n']*('')*)*                               {printf("Line %d, col %d: unterminated string\n", line, col);}
'([^\n']|''|\\.)*('')*'                                         {col+=yyleng;yylval.str=(char*)strdup(yytext);return STRING;}
{TAB}                                                           {col += yyleng;}
{NEWLINE}                                                       {line++; col=1;}
{BLANKSPACE}                                                    {col++;}

.                   {printf("Line %d, col %d: illegal character ('%s')\n", line, col, yytext); col += yyleng;}

%%

int yywrap()
{
    return 1;
}

