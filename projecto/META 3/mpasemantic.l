%{
    #include "structures.h"
    #include "y.tab.h"


    int yycolumn = 1;
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; yycolumn += yyleng;


    int col = 1;
    int line = 1;
    int colaux = 0;
    int lineaux = 0;
    
%}
%option yylineno
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
<comment><<EOF>>            {printf("Line %d, col %d: unterminated comment\n", lineaux, colaux);lineaux = line; colaux = col; BEGIN 0;}
<comment>{NEWLINE}			{col=1; line++;}
<comment>{ENDCOMMENT}		{BEGIN 0; col+=yyleng;}
<comment>.                  {col++;}
{ASSIGN}                                                        {lineaux = line; colaux = col;col +=yyleng; return ASSIGN;}
{BEGIN}                                                         {lineaux = line; colaux = col;col +=yyleng;return BEG;}
{COLON}                                                         {lineaux = line; colaux = col;col +=yyleng;return COLON;}
{COMMA}                                                         {lineaux = line; colaux = col;col +=yyleng;return COMMA;}
{DO}                                                            {lineaux = line; colaux = col;col +=yyleng;return DO;}
{DOT}                                                           {lineaux = line; colaux = col;col +=yyleng;return DOT;}
{ELSE}                                                          {lineaux = line; colaux = col;col +=yyleng;return ELSE;}
{END}                                                           {lineaux = line; colaux = col;col +=yyleng; return END;}
{FORWARD}                                                       {lineaux = line; colaux = col;col +=yyleng;return FORWARD;}
{FUNCTION}                                                      {lineaux = line; colaux = col;col +=yyleng;return FUNCTION;}
{IF}                                                            {lineaux = line; colaux = col;col +=yyleng;return IF;}
{LBRAC}                                                         {lineaux = line; colaux = col;col +=yyleng;return LBRAC;}
{NOT}                                                           {lineaux = line; colaux = col;col +=yyleng;return NOT;}
{OUTPUT}                                                        {lineaux = line; colaux = col;col +=yyleng;return OUTPUT;}
{PARAMSTR}                                                      {lineaux = line; colaux = col;col +=yyleng;return PARAMSTR;}
{PROGRAM}                                                       {lineaux = line; colaux = col;col +=yyleng;return PROGRAM;}
{RBRAC}                                                         {lineaux = line; colaux = col;col +=yyleng;return RBRAC;}
{REPEAT}                                                        {lineaux = line; colaux = col;col +=yyleng;return REPEAT;}
{SEMIC}                                                         {lineaux = line; colaux = col;col +=yyleng;return SEMIC;}
{THEN}                                                          {lineaux = line; colaux = col;col +=yyleng;return THEN;}
{UNTIL}                                                         {lineaux = line; colaux = col;col +=yyleng;return UNTIL;}
{VAL}                                                           {lineaux = line; colaux = col;col +=yyleng;return VAL;}
{VAR}                                                           {lineaux = line; colaux = col;col +=yyleng;return VAR;}
{WHILE}                                                         {lineaux = line; colaux = col;col +=yyleng;return WHILE;}
{WRITELN}                                                       {lineaux = line; colaux = col;col +=yyleng;return WRITELN;}
and 															{lineaux = line; colaux = col;col += yyleng; return(AND);}
or 																{lineaux = line; colaux = col;col += yyleng; return(OR);}
"<"																{lineaux = line; colaux = col;col += yyleng; return(LESS);}
">"																{lineaux = line; colaux = col;col += yyleng; return(GREATER);}
"="																{lineaux = line; colaux = col;col += yyleng; return(EQUALS);}
"<>"															{lineaux = line; colaux = col;col += yyleng; return(DIFFERENT);}
"<="															{lineaux = line; colaux = col;col += yyleng; return(LEQUAL);}
">="															{lineaux = line; colaux = col;col += yyleng; return(GEQUAL);}
"+"	 															{lineaux = line; colaux = col;col += yyleng; return(PLUS);}
"-"	 															{lineaux = line; colaux = col;col += yyleng; return(MINUS);}
"*"																{lineaux = line; colaux = col;col += yyleng; return(MULT);}
"/"																{lineaux = line; colaux = col;col += yyleng; return(REALDIV);}
mod																{lineaux = line; colaux = col;col += yyleng; return(MOD);}
div																{lineaux = line; colaux = col;col += yyleng; return(DIV);}

{RESERVED}                                                      {lineaux = line; colaux = col;col +=yyleng;yylval.str=(char*)strdup(yytext);return RESERVED;}

{INTLIT}                                                        {lineaux = line; colaux = col;col+=yyleng;yylval.str=(char*)strdup(yytext);return INTLIT;}
{ID}                                                            {lineaux = line; colaux = col;col += yyleng; yylval.str=(char*)strdup(yytext); return ID;}
{REALLIT}                                                       {lineaux = line; colaux = col;col+=yyleng;yylval.str=(char*)strdup(yytext);return REALLIT;}
'([^\n']*('')*)*                               					{printf("Line %d, col %d: unterminated string\n", line, col);lineaux = line; colaux = col;col+=yyleng;}
'([^\n']|''|\\.)*('')*'                                         {lineaux = line; colaux = col;col+=yyleng;yylval.str=(char*)strdup(yytext);return STRING;}
{TAB}                                                           {lineaux = line; colaux = col;col += yyleng;}
{NEWLINE}                                                       {yycolumn = 1;lineaux = line; colaux = col;line++; col=1;}
{BLANKSPACE}                                                    {lineaux = line; colaux = col;col++;}
<<EOF>>															{lineaux = line; colaux = col; return *yytext;}
.                   {printf("Line %d, col %d: illegal character ('%s')\n", line, col, yytext);lineaux = line; colaux = col; col += yyleng;}

%%

int yywrap()
{
    return 1;
}

