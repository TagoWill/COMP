#include "structures.h"
#include "semantics.h"
#include "symbol_table.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

extern table* symtab;
extern int lineaux;
extern int colaux;
extern int erros;

int check_program(is_Nos* noactual, char* param)
{



	int errorcount=0;
	if(noactual != NULL && erros == 0){
		switch(noactual->queraioeisto){
		
			case is_PROGRAM:
				cria();
				check_program(noactual->nofilho, param);
				check_program(noactual->nonext, param);
				break;
			case is_VARDECL:
				checkVarPart(noactual->nofilho, NULL);
				check_program(noactual->nonext, NULL);
				break;
			case is_VARPARAMS:
				checkVarPart(noactual->nofilho, param);
				check_program(noactual->nonext, param);
				break;
			case is_PARAMS:
				checkVarPart(noactual->nofilho, param);
				check_program(noactual->nonext, param);
				break;
			case is_FUNCPART:
				checkFuncPart(noactual->nofilho);
				check_program(noactual->nonext, param);
				break;
			case is_ASSIGN:
				checkAssign(noactual->nofilho);
				check_program(noactual->nonext, param);
			default:
				check_program(noactual->nofilho, param);
				check_program(noactual->nonext, param);
		}
	}
	
	return errorcount;
}

void checkAssign(is_Nos *noactual){
	/*if(noactual != NULL){
		table *mexer = encontra_na_tabela(noactual->valor);
		if(mexer != NULL){
			printf("debug - %s %s %d\n", mexer->name, mexer->type, mexer->isconstant);
			if(mexer->isconstant == 0){
				printf("lol\n");
			}else{
				erros = 1;
				printf("ERRO NO POSSO FAZER ISSO\n");
			}
		}
	}*/
}

void checkFuncPart(is_Nos *noactual){
	if(noactual != NULL){
		
		checkFuncDeclaration(noactual->nofilho);

		checkFuncPart(noactual->nonext);
	}
}

void checkFuncDeclaration(is_Nos *noactual){
	if(noactual != NULL){
		table *original = symtab;
		inserir_coisas(noactual->valor, "_function_", NULL);
		
		table *funcao = inserir_funcoes(noactual->valor, noactual->nonext->nonext->valor);
		symtab = funcao;
		check_program(noactual->nonext,"param");
		symtab = original;
	}
}

char *checkVarPart(is_Nos *noactual, char *param){
	if(noactual != NULL && erros == 0){
		if(noactual->nonext == NULL){
			if(encontra_na_tabela_outer(noactual->valor)!=NULL){
				if(strcmp(noactual->valor, "integer")==0){
					return "_integer_";
				}
				if(strcmp(noactual->valor, "real")==0){
					return "_real_";
				}
				if(strcmp(noactual->valor, "boolean")==0){
					return "_boolean_";
				}
				else{
					return noactual->valor;
					/*erros =1;
					printf("Line <linha>, col <coluna>: Type identifier expected\n");*/
				}
			}else{
				erros =1;
				printf("Line <linha>, col <coluna>: Type identifier expected\n");
			}
		}else{
			if(encontra_na_tabela(noactual->valor)==NULL){
				table *new = inserir_coisas(noactual->valor,NULL,param);
				char *tipo=checkVarPart(noactual->nonext, param);
				if(tipo != NULL){
					new->type = (char*)malloc(sizeof(char));
					strcpy(new->type, tipo);
				}else{
					new->type = NULL;
				}
				return tipo;
			}else{
				erros = 1;
				printf("Line <linha>, col <coluna>: Symbol %s already defined\n", noactual->valor);
			}
		}
	}
	return NULL;
}
