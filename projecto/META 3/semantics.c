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
	if(noactual != NULL && erros != 1){
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
			case is_WRITELN:
			checkWriteLn(noactual);
			check_program(noactual->nonext, param);
			break;
			case is_IFELSE:
			checkIfThen(noactual);
			check_program(noactual->nonext, param);
			break;
			case is_WHILE:
			checkWhile(noactual);
			check_program(noactual->nonext, param);
			break;
			case is_REPEAT:
			checkRepeat(noactual);
			check_program(noactual->nonext, param);
			break;
			case is_VALPARAM:
			checkValParam(noactual);
			check_program(noactual->nonext, param);
			default:
			check_program(noactual->nofilho, param);
			check_program(noactual->nonext, param);
		}
	}

	return errorcount;
}

char *checkExpr(is_Nos *noactual){
	if(noactual != NULL){
		is_Nos *contadordevariaveis;
		table *aux;
		char *aux2, *aux3;
		switch(noactual->queraioeisto){
			case is_STRING: ;
			return "_string_";
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
				printf("Line %d, col %d: Symbol %s not defined\n", noactual->lina, noactual->cola, noactual->valor);
				return NULL;
			}
			return NULL;

			case is_NOT: ;
			if(erros != 1){
				aux2 = checkExpr(noactual->nofilho);
				if(strcmp(aux2, "_boolean_")==0){
					return aux2;
				}else{
					erros = 1;
					printf("Line %d, col %d: Operator Not cannot be applied to type %s\n", noactual->lina, noactual->cola, aux2);
					return NULL;
				}
			}
			return NULL;

			case is_PLUS:
			case is_MINUS: ;
			if(erros != 1){
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
			}
			return NULL;

			case is_DIV:
			case is_MOD: ;
			if(erros != 1){
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_integer_")==0 && strcmp(aux3, "_integer_")==0){
					return aux2;
				}else{

					erros = 1;
					printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
						noactual->lina, noactual->cola, istoe(noactual->queraioeisto),aux2, aux3);
					return NULL;
				}
			}
			return NULL;

			case is_MULT:
			case is_ADD:
			case is_SUB: ;
			if(erros != 1){
				char *operador;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(erros != 1){
					if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0){
						if(strcmp(aux2, "_integer_")==0 && strcmp(aux3, "_integer_")==0){
							return "_integer_";
						}else{
							return "_real_";
						}
					}else{
							/*LINHAS ERRADAS*/
						erros = 1;
						switch(noactual->queraioeisto){
							case is_ADD:
								operador = "+";
								break;
							case is_SUB:
								operador = "-";
								break;
							default:
								operador = istoe(noactual->queraioeisto);
						}
						printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
							noactual->lina, noactual->cola, operador, aux2, aux3);
						return NULL;
					}
				}
			}
			return NULL;

			case is_REALDIV: ;
			if(erros != 1){
				char *operador;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(erros != 1){
					if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0){
						return "_real_";
					}else{
							switch(noactual->queraioeisto){
							case is_REALDIV:
								operador = "/";
								break;
							default:
								operador = istoe(noactual->queraioeisto);
						}
						erros = 1;
						printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
							noactual->lina, noactual->cola, operador,aux2, aux3);
						return NULL;
					}
				}
			}
			return NULL;

			case is_LESS:
			case is_GEQUAL:
			case is_LEQUAL:
			case is_GREATER: ;
			if(erros != 1){
				char *operador;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(erros != 1){
					if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0){
						return "_boolean_";
					}else{
							
						switch(noactual->queraioeisto){
							case is_LESS:
								operador = "<";
								break;
							case is_GEQUAL:
								operador = ">=";
								break;
							case is_LEQUAL:
								operador = "<=";
								break;
							case is_GREATER:
								operador = ">";
								break;
							default:
								operador = istoe(noactual->queraioeisto);
						}
						erros = 1;
						printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",
							noactual->lina, noactual->cola, operador,aux2, aux3);
						return NULL;
					}
				}
			}
			return NULL;

			case is_DIFFERENT:
			case is_EQUALS: ;
			if(erros != 1){
				char *operador;
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(erros != 1){
					if(aux2 != NULL && aux3 != NULL){
						return "_boolean_";
					}else{
							switch(noactual->queraioeisto){
							case is_DIFFERENT:
								operador = "<>";
								break;
							case is_EQUALS:
								operador = "=";
								break;
							default:
								operador = istoe(noactual->queraioeisto);
						}
						erros = 1;
						printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", 
							noactual->lina, noactual->cola, operador,aux2, aux3);
						return NULL;
					}
				}
			}
			return NULL;

			case is_OR:
			case is_AND: ;
			if(erros != 1){
				aux2 = checkExpr(noactual->nofilho);
				aux3 = checkExpr(noactual->nofilho->nonext);
				if(erros != 1){
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
			return NULL;
			case is_CALL: ;
			if(erros != 1){
				aux = encontra_em_tudo(noactual->nofilho->valor);
				if(aux != NULL && strcmp(aux->type, "_function_")==0){
					aux = encontra_funcao_em_tudo(aux->name);
					if(aux != NULL){
						int contador1 =0, contador2 = 0;
						table *vervariaveis;
						for(vervariaveis=aux->variaveis;vervariaveis!=NULL;vervariaveis=vervariaveis->next){
							if(vervariaveis->valreturn != NULL){
								contador1++;
							}else{
								break;
							}
						}
						for(contadordevariaveis=noactual->nofilho->nonext;contadordevariaveis!=NULL;contadordevariaveis=contadordevariaveis->nonext){
							contador2++;
						}
						if(contador1 == contador2){
							contadordevariaveis=noactual->nofilho->nonext;
							contador1=0;
							for(vervariaveis=aux->variaveis;vervariaveis!=NULL;vervariaveis=vervariaveis->next){
								if(vervariaveis->valreturn != NULL){
									aux2 = checkExpr(contadordevariaveis);
									contador1++;
									if(strcmp(aux2, vervariaveis->type)!=0){
										erros=1;
										printf("Line %d, col %d: Incompatible type for argument %d in call to function %s (got %s, expected %s\n", 
											noactual->lina, noactual->cola, contador1, aux->name, aux2, vervariaveis->type);
										return NULL;
									}
									contadordevariaveis=contadordevariaveis->nonext;
								}else{
									break;
								}
							}
						}else{
							erros=1;
							printf("Line %d, col %d: Wrong number of arguments in call to function %s (got %d, expected %d)\n",
								noactual->lina, noactual->cola, aux->name, contador2, contador1);
							return NULL;
						}
					}else{
						printf("debug - NAO E SUPOSTO\n");
					}
					return aux->type;
				}else{
					erros=1;
					printf("Line %d, col %d: Symbol %s not defined\n", 
						noactual->lina, noactual->cola, noactual->nofilho->valor);
					return NULL;
				}
			}
			return NULL;

			default :
				return "ERRO";

		}
	}
}

void checkValParam(is_Nos *noactual){
	if(noactual!= NULL && erros!=1){
		char *aux = checkExpr(noactual->nofilho);
		table *aux2 = encontra_em_tudo(noactual->nofilho->nonext->valor);
		if(erros != 1){
			if(aux != NULL && aux2 != NULL){
				if(strcmp(aux, aux2->type)!=0 || strcmp(aux, "_boolean_")==0 || strcmp(aux2->type, "_boolean_")==0){
					if(strcmp(aux, "_boolean_")==0 && strcmp(aux2->type, "_boolean_")!=0){
						erros=1;
						printf("Line %d, col %d: Incompatible type in val-paramstr statement (got %s, expected %s)\n",
						noactual->lina, noactual->cola, aux, aux2->type);
					}else if(strcmp(aux, "_boolean_")==0 && strcmp(aux2->type, "_boolean_")==0){
						erros=1;
						printf("Line %d, col %d: Incompatible type in val-paramstr statement (got %s, expected _real_)\n",
						noactual->lina, noactual->cola, aux);
					}else{
						erros=1;
						printf("Line %d, col %d: Incompatible type in val-paramstr statement (got %s, expected %s)\n",
						noactual->lina, noactual->cola, aux2->type, aux);
					}
					
				}
			}else{
				erros =1;
				printf("Line %d, col %d: Symbol %s not defined\n", 
					noactual->nofilho->nonext->lina, noactual->nofilho->nonext->cola, noactual->nofilho->nonext->valor);
			}
		}
	}
}

void checkRepeat(is_Nos *noactual){
	if(noactual!= NULL && erros!=1){
		check_program(noactual->nofilho, NULL);
		if(erros!=1){
			char *aux = checkExpr(noactual->nofilho->nonext);
			if(erros != 1 && aux != NULL && strcmp(aux, "_boolean_")!=0){
				erros=1;
				printf("Line %d, col %d: Incompatible type in repeat-until statement (got %s, expected _boolean_)\n",
					noactual->nofilho->lina, noactual->nofilho->cola, aux);
			}
		}
	}
}

void checkWhile(is_Nos *noactual){
	if(noactual!= NULL && erros!=1){
		char *aux = checkExpr(noactual->nofilho);
		if(erros != 1){
			if(aux != NULL && strcmp(aux, "_boolean_")!=0){
				erros=1;
				printf("Line %d, col %d: Incompatible type in while statement (got %s, expected _boolean_)\n",
					noactual->nofilho->lina, noactual->nofilho->cola, aux);
			}
			check_program(noactual->nofilho->nonext, NULL);
		}
	}
}

void checkIfThen(is_Nos *noactual){
	if(noactual!= NULL && erros!=1){
		char *aux = checkExpr(noactual->nofilho);
		if(erros != 1){
			if(aux != NULL && strcmp(aux, "_boolean_")!=0){
				erros=1;
				printf("Line %d, col %d: Incompatible type in if statement (got %s, expected _boolean_)\n",
					noactual->nofilho->lina, noactual->nofilho->cola, aux);
			}
			check_program(noactual->nofilho->nonext, NULL);
			check_program(noactual->nofilho->nonext->nonext, NULL);
		}
	}
}

void checkWriteLn(is_Nos *noactual){
	if(noactual != NULL && erros!=1){
		char *aux;
		aux = checkExpr(noactual->nofilho);
		if(erros != 1){
			if(aux != NULL){
				if(strcmp(aux, "_type_")==0){
					erros=1;
					printf("Line %d, col %d: Cannot write values of type %s\n",
						noactual->nofilho->lina, noactual->nofilho->cola, aux);
				}
			}
			checkWriteLn(noactual->nonext);
		}
	}
}

void checkAssign(is_Nos *noactual){
	if(noactual != NULL){
		table *verifica;
		table *mexer = encontra_em_tudo(noactual->valor);
		if(mexer != NULL && strcmp(mexer->type, "_function_")==0){
			verifica = encontra_para_return(mexer->name);
			if(verifica != NULL){
				mexer = verifica;
			}
		}
		if(mexer != NULL){
			if(mexer->isconstant == 0){
				char *aux = checkExpr(noactual->nonext);
				if(erros != 1){
				if(aux != NULL){
					if(strcmp(mexer->type, aux)!=0){
						/*ISTO AINDA N ESTA BEM*/
						if(strcmp(mexer->type, "_boolean_")==0 || strcmp(aux,"_boolean_")==0){
							erros = 1;
							printf("Line %d, col %d: Incompatible type in assigment to %s (got %s, expected %s)\n", 
								noactual->nonext->lina, noactual->nonext->cola, mexer->name, aux, mexer->type);
						}
					}
				}
			}
			}else{
				erros = 1;
				printf("Line %d, col %d: Variable identifier expected\n", 
					noactual->lina, noactual->cola);
			}
		}else{
			erros=1;
			printf("Line %d, col %d: Symbol %s not defined\n", 
				noactual->lina, noactual->cola, noactual->valor);
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
	if(noactual != NULL && erros != 1){
		table *original = symtab;
		table *procura = encontra_funcao_na_tabela(noactual->valor);

		if(procura == NULL){
			inserir_coisas(noactual->valor, "_function_", NULL);

			table *verifica = encontra_em_tudo(noactual->nonext->nonext->valor);
			if(strcmp(verifica->type, "_type_")==0){
				
				table *funcao = inserir_funcoes(noactual->valor, noactual->nonext->nonext->valor);
				symtab = funcao;
				check_program(noactual->nonext, param);
				symtab = original;
			}else{
				erros =1;
				printf("Line %d, col %d: Type identifier expected\n", noactual->lina, noactual->cola);
			}
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
					printf("Line %d, col %d: Type identifier expected\n", 
						noactual->lina, noactual->cola);
				}
			}else{
				erros =1;
				printf("Line %d, col %d: Symbol %s not defined\n", 
					noactual->lina, noactual->cola, noactual->valor);
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
				printf("Line %d, col %d: Symbol %s already defined\n", 
					noactual->lina, noactual->cola, noactual->valor);
			}
		}
	}
	return NULL;
}