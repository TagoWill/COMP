numero				[0-9]+
caracter			[a-z]+
%%

"-"{numero}                        {printf(" Inteiro negativo");}
"-"{numero}"."{numero}		{printf(" Real negatico");}
{numero}                        {printf(" Interger ");}
({numero}+("."{numero}*)?|"."{numero}+)(e[+-]{numero}+)?		{printf(" float ");}
abc|ab+c|a?(bc)+		{printf(" Token! ");}
{numero}l			{printf(" long ");}
{numero}u			{printf(" unsigned int ");}
\"([^"\\]|\\.)*\"			{printf(" string ");}

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

