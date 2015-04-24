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


		is_VARDECL, is_FUNCPART, is_FUNCDECL, is_FUNCDEF, is_FUNCPARAMS, is_PARAMS, 
	is_VARPARAMS, is_IFELSE, is-REPEAT, is_WHILE, is_WRITELN is_STATLIST, is_VALPARAM, is_CALL, is_ASSIGN, is_ID, 
	is_PLUS, is_MINUS, is_AND, is_OR, is_MULT, is_DIV, is_MOD, is_GREATER, is_LESS, is_GEQUAL, is_LEQUAL, 
	is_EQUALS, is_DIFFERENT, is_NOT, is_INTLIT, is_REALLIT, is_ID, is_EXP, is_SUB, is_REALDIV, is_ADD, is_STRING
	}

}

void show_prog(is_Nos *noactual, int tamanho){

	if(noactual != NULL){
		espacamento(tamanho);

		if(noactual->valor != NULL){
			printf("%s(%s)\n", /*FALTA*/ ,no->valor);
		}else{
			printf("%s\n", /*FALTA*/);
		}

		if(no->nofilho != NULL){
			show_prog(no->nofilho, tamanho+1);
		}
		if(no->nonext != NULL){
			show_prog(no->nonext, tamanho);
		}
	}
}


