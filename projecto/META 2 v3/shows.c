#include "shows.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void espacamento(int tamanho){
	int i;
	for(i=0;i<tamanho;i++){
		printf("..");
	}
}

char *istoe(tipos_nos tipo){

	switch(tipo){
		case is_PROGRAM:
			return "Program";
		case is_VARPART:
			return "VarPart";
		case is_VARDECL:
			return "VarDecl";
		case is_FUNCPART:
			return "FuncPart";
		case is_FUNCDECL:
			return "FuncDecl";
		case is_FUNCPARAMS:
			return "FuncParams";
		case is_PARAMS:
			return "Params";
		case is_VARPARAMS:
			return "VarParams";
		case is_IFELSE:
			return "IfElse";
		case is_REPEAT:
			return "Repeat";
		case is_WHILE:
			return "While";
		case is_WRITELN:
			return "WriteLn";
		case is_STATLIST:
			return "StatList";
		case is_VALPARAM:
			return "ValParam";
		case is_CALL:
			return "Call";
		case is_ASSIGN:
			return "Assign";
		case is_PLUS:
			return "Plus";
		case is_MINUS:
			return "Minus";
		case is_AND:
			return "And";
		case is_OR:
			return "Or";
		case is_MULT:
			return "Mult";
		case is_DIV:
			return "Div";
		case is_MOD:
			return "Mod";
		case is_GREATER:
			return "Gt";
		case is_LESS:
			return "Lt";
		case is_GEQUAL:
			return "Geq";
		case is_LEQUAL:
			return "Leq";
		case is_EQUALS:
			return "Eq";
		case is_DIFFERENT:
			return "Neq";
		case is_NOT:
			return "Not";
		case is_INTLIT:
			return "IntLit";
		case is_REALLIT:
			return "RealLit";
		case is_ID:
			return "Id";
		case is_EXP:
			return "Exp";
		case is_SUB:
			return "Sub";
		case is_REALDIV:
			return "RealDiv";
		case is_ADD:
			return "Add";
		case is_STRING:
			return "String";

}

void show_prog(is_Nos *noactual, int tamanho){

	/*if(noactual != NULL){
		espacamento(tamanho);

		if(noactual->valor != NULL){
			printf("%s(%s)\n",istoe(noactual->queraioeisto) ,noactual->valor);
		}else{
			printf("%s\n", noactual->queraioeisto);
		}

		if(noactual->nofilho != NULL){
			show_prog(noactual->nofilho, tamanho+1);
		}
		if(noactual->nonext != NULL){
			show_prog(noactual->nonext, tamanho);
		}
	}*/
}
