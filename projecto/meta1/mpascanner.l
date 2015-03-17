%{
    int col = 1;
    int line = 1;
    int colaux = 0;
    int lineaux = 0;
    
%}

%option case-insensitive

ID                                  [a-zA-Z][a-zA-Z0-9]*
INTLIT								[0-9]+
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
OP1                                 and|or
OP2                                 "<"|">"|"="|"<>"|"<="|">="
OP3                                 "+"|"-"
OP4                                 "*"|"/"|mod|div

BLACKSPACE                          " "
TAB                                 "\t"
NEWLINE                             "\n"

STARTCOMMENT                        "(*"|"{"
ENDCOMMENT                          "*)"|"}"
%X                                  comment

%%

{STARTCOMMENT}              {lineaux=line; colaux=col; col += yyleng; BEGIN(comment);}
<comment><<EOF>>            {printf("Line %d, col %d: unterminated comment\n", lineaux, colaux); BEGIN 0;}
<comment>.                  {col++;}
<comment>{NEWLINE}			{col=1; line++;}
<comment>{ENDCOMMENT}		{BEGIN 0; col+=yyleng;}
{ASSIGN}                                                        {printf("ASSIGN\n"); col +=yyleng;}
{BEGIN}                                                         {printf("BEGIN\n"); col +=yyleng;}
{COLON}                                                         {printf("COLON\n"); col +=yyleng;}
{COMMA}                                                         {printf("COMMA\n"); col +=yyleng;}
{DO}                                                            {printf("DO\n"); col +=yyleng;}
{DOT}                                                           {printf("DOT\n"); col +=yyleng;}
{ELSE}                                                          {printf("ELSE\n"); col +=yyleng;}
{END}                                                           {printf("END\n"); col +=yyleng;}
{FORWARD}                                                       {printf("FORWARD\n"); col +=yyleng;}
{FUNCTION}                                                      {printf("FUNCTION\n"); col +=yyleng;}
{IF}                                                            {printf("IF\n"); col +=yyleng;}
{LBRAC}                                                         {printf("LBRAC\n"); col +=yyleng;}
{NOT}                                                           {printf("NOT\n"); col +=yyleng;}
{OUTPUT}                                                        {printf("OUTPUT\n"); col +=yyleng;}
{PARAMSTR}                                                      {printf("PARAMSTR\n"); col +=yyleng;}
{PROGRAM}                                                       {printf("PROGRAM\n"); col +=yyleng;}
{RBRAC}                                                         {printf("RBRAC\n"); col +=yyleng;}
{REPEAT}                                                        {printf("REPEAT\n"); col +=yyleng;}
{SEMIC}                                                         {printf("SEMIC\n"); col +=yyleng;}
{THEN}                                                          {printf("THEN\n"); col +=yyleng;}
{UNTIL}                                                         {printf("UNTIL\n"); col +=yyleng;}
{VAL}                                                           {printf("VAL\n"); col +=yyleng;}
{VAR}                                                           {printf("VAR\n"); col +=yyleng;}
{WHILE}                                                         {printf("WHILE\n"); col +=yyleng;}
{WRITELN}                                                       {printf("WRITELN\n"); col +=yyleng;}
{OP1}                                                           {printf("OP1\n"); col +=yyleng;}
{OP2}                                                           {printf("OP2\n"); col +=yyleng;}
{OP3}                                                           {printf("OP3\n"); col +=yyleng;}
{OP4}                                                           {printf("OP4\n"); col +=yyleng;}

{RESERVED}                                                      {printf("RESERVED\n"); col +=yyleng;}

{INTLIT}                                                        {printf("INTLIT(%s)\n", yytext); col+=yyleng;}
{ID}                                                            {printf("ID(%s)\n", yytext); col+=yyleng;}
({INTLIT}+("."{INTLIT}*)?|"."{INTLIT}+)([eE][+-]?{INTLIT}+)?	{printf("REALLIT\n"); col+=yyleng;}
'([^\n']|''|\\.)*'                                              {printf("STRING\n"); col+=yyleng;}


{TAB}                                                             {col += yyleng;}
{NEWLINE}                                                         {line++; col=1;}
{BLACKSPACE}                                                      {col++;}


.                   {printf("Line %d, col %d: illegal character ('%s')\n", line, col, yytext); col += yyleng;}

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

