#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum{is_PROGRAM, is_VARPART, is_VARDECL, is_FUNCPART, is_FUNCDECL, is_FUNCDEF, is_FUNCPARAMS, is_PARAMS, 
	is_VARPARAMS, is_IFELSE, is_REPEAT, is_WHILE, is_WRITELN, is_STATLIST, is_VALPARAM, is_CALL, is_ASSIGN, 
	is_PLUS, is_MINUS, is_AND, is_OR, is_MULT, is_DIV, is_MOD, is_GREATER, is_LESS, is_GEQUAL, is_LEQUAL, 
	is_EQUALS, is_DIFFERENT, is_NOT, is_INTLIT, is_REALLIT, is_ID, is_EXP, is_SUB, is_REALDIV, is_ADD, is_STRING, 
	is_FUNCDEF2} tipos_nos;

typedef struct _a1
{
	tipos_nos queraioeisto;
	char *valor;
	struct _a1 *nofilho;
	struct _a1 *nonext;
} is_Nos;


#endif
