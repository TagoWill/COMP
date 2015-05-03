#include "structures.h"
#include "shows.h"
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
				checkVarPart(noactual->nofilho, "varparam");
				check_program(noactual->nonext, param);
				break;
			case is_PARAMS:
				checkVarPart(noactual->nofilho, "param");
				check_program(noactual->nonext, param);
				break;
			case is_FUNCPART:
				checkFuncPart(noactual->nofilho, NULL);
				check_program(noactual->nonext, param);
				break;
			case is_ASSIGN:
				checkAssign(noactual->nofilho);
				check_program(noactual->nonext, param);
				break;
			default:
				check_program(noactual->nofilho, param);
				check_program(noactual->nonext, param);
		}
	}
	
	return errorcount;
}

char *checkExpr(is_Nos *noactual){
	if(noactual != NULL){
		table *aux;
		char *aux2, *aux3;
		switch(noactual->queraioeisto){
			case is_INTLIT: ;
				return "_integer_";
			case is_REALLIT: ;
				return "_real_";
			case is_ID: ;
				aux = NULL;
				aux = encontra_em_tudo(noactual->valor);
				if(aux != NULL){
					return aux->type;
				}else{
					erros = 1;
					printf("Line %d, col %d: Symbol %s not defined\n", noactual->lina, noactual->cola - strlen(noactual->valor), noactual->valor);
					return NULL;
				}
			case is_NOT: ;
				aux2 = checkExpr(noactual->nofilho);
				if(strcmp(aux2, "_boolean_")==0){
					return aux2;
				}else{
					erros = 1;
					printf("Line %d, col %d: Operator Not cannot be applied to type %s\n", noactual->lina, noactual->cola, aux2);
					return NULL;
				}

			case is_PLUS:
			case is_MINUS: ;
				aux2 = checkExpr(noactual->nofilho);
				if(strcmp(aux2, "_boolean_")==0){
					erros = 1;
					/*Linhas erradas*/
					printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto), aux2);
					return NULL;
				}else{
					return aux2;
				}
			
			case is_DIV:
			case is_MOD: ;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_integer_")==0 && strcmp(aux3, "_integer_")==0){
					return aux2;
				}else{
					/*LINHAS ERRADAS*/
					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}

			case is_MULT:
			case is_ADD:
			case is_SUB:
			case is_REALDIV: ;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0){
					return "_real_";
				}else{
					/*LINHAS ERRADAS*/
					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}
			
			case is_LESS:
			case is_GEQUAL:
			case is_LEQUAL:
			case is_GREATER: ;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0){
						return "_boolean_";
				}else{
					/*LINHAS ERRADAS*/
					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
					 noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}

			case is_DIFFERENT:
			case is_EQUALS: ;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL){
						return "_boolean_";
				}else{
					/*LINHAS ERRADAS*/
					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}


			case is_OR:
			case is_AND: ;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")==0 && strcmp(aux3, "_boolean_")==0){
						return "_boolean_";
				}else{
					/*LINHAS ERRADAS*/
					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}
			

		}
	}
}

void checkAssign(is_Nos *noactual){
	if(noactual != NULL){
		table *mexer = encontra_em_tudo(noactual->valor);
		if(mexer != NULL){
			if(mexer->isconstant == 0){
				char *aux = checkExpr(noactual->nonext);
				/*if(erros != 1 && aux != NULL){
					if(strcmp(mexer->type, aux)==0){
						printf("TUDO BEM\n");
					}else{
						erros = 1;
						printf("Line %d, col %d: Incompatible type in assigment to %s (got %s, expected %s)\n", 
							noactual->lina, noactual->cola, mexer->name, aux, mexer->type);
					}
				}*/
			}else{
				erros = 1;
				printf("Line %d, col %d: Variable identifier expected\n", noactual->lina, noactual->cola - strlen(noactual->valor));
			}
		}else{
			erros=1;
			printf("Line %d, col %d: Symbol %s not defined\n", noactual->lina, noactual->cola - strlen(noactual->valor), noactual->valor);
		}
	}
}

void checkFuncPart(is_Nos *noactual, char *param){
	if(noactual != NULL){
		
		checkFuncDeclaration(noactual->nofilho, param);
		
		checkFuncPart(noactual->nonext, param);
	}
}

void checkFuncDeclaration(is_Nos *noactual, char *param){
	if(noactual != NULL){
		table *original = symtab;
		table *procura = encontra_funcao_na_tabela(noactual->valor);

		if(procura == NULL){
			inserir_coisas(noactual->valor, "_function_", NULL);
		
			table *funcao = inserir_funcoes(noactual->valor, noactual->nonext->nonext->valor);
			symtab = funcao;
			check_program(noactual->nonext, param);
			symtab = original;
		}else{
			symtab = procura;
			check_program(noactual->nonext, param);
			symtab = original;
		}
	}
}

char *checkVarPart(is_Nos *noactual, char *param){
	if(noactual != NULL && erros != 1){
		if(noactual->nonext == NULL){
			
			table *aux = encontra_em_tudo(noactual->valor);
			if(aux!=NULL){
				if(strcmp(aux->type, "_type_")==0){
					return aux->valreturn;
				}else{
					erros =1;
				printf("Line %d, col %d: Type identifier expected\n", noactual->lina, noactual->cola);
				}
			}else{
				erros =1;
				printf("Line %d, col %d: Symbol %s not defined\n", noactual->lina, noactual->cola, noactual->valor);
			}
		}else{
			if(encontra_na_tabela(noactual->valor)==NULL){
				table *new = inserir_coisas(noactual->valor,NULL,param);
				char *tipo=checkVarPart(noactual->nonext, param);
				if(tipo != NULL){
					new->type = (char*)malloc(sizeof(char));
					strcpy(new->type, tipo);
				}
				return tipo;
			}else{
				erros = 1;
				printf("Line %d, col %d: Symbol %s already defined\n", noactual->lina, noactual->cola - strlen(noactual->valor), noactual->valor);
			}
		}
	}
	return NULL;
}