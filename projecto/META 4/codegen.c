#include "codegen.h"
#include "symbol_table.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern table* symtab;

int tempname = 1;
int temp_strname = 1;
int temp_compname = 1;

void generateCode(is_Nos* noactual, char* param, int tamanho)
{
	if(noactual != NULL){
		switch(noactual->queraioeisto){
			case is_PROGRAM:
				//printf("is_PROGRAM\n\t");
			generateCode(noactual->nofilho, param, tamanho);
			generateCode(noactual->nonext, param, tamanho);
				//printf("define i32 @main() {\n\t");
				//printf("ret i32 0\n}\n");
			break;
			case is_VARDECL:
				//printf("is_VARDECL\n\t");
			genVarPart(noactual->nofilho, NULL, tamanho);
			generateCode(noactual->nonext, NULL, tamanho);
			break;
			case is_VARPARAMS:
				//printf("is_VARPARAMS\n\t");
			genVarPart(noactual->nofilho, "varparam", tamanho);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_PARAMS:
				//printf("is_PARAMS\n\t");
			genVarPart(noactual->nofilho, "param", tamanho);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_FUNCPART:
				//printf("is_FUNCPART\n\t");
			//genFuncPart(noactual->nofilho, NULL, tamanho);
			if(strcmp(symtab->name, "program")==0){
				printf("@str.true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
   				printf("@str.false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
				printf("define i32 @main() {\n");
			}
			generateCode(noactual->nonext, param, tamanho+1);
			if(strcmp(symtab->name, "program")==0){
				printf("\tret i32 0\n}\n");
			}
			break;
			case is_ASSIGN:
				//printf("is_ASSIGN\n\t");
			genAssign(noactual->nofilho, tamanho);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_WRITELN:
				//printf("is_WRITELN\n");
			genWriteLn(noactual, tamanho);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_IFELSE:
				//printf("is_IFELSE\n");
			genIfThen(noactual);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_WHILE:
				//printf("is_WHILE\n");
			genWhile(noactual);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_REPEAT:
				//printf("is_REPEAT\n");
			genRepeat(noactual);
			generateCode(noactual->nonext, param, tamanho);
			break;
			case is_VALPARAM:
				//printf("is_VALPARAM\n");
			genValParam(noactual);
			generateCode(noactual->nonext, param, tamanho);
			default:
			generateCode(noactual->nofilho, param, tamanho);
			generateCode(noactual->nonext, param, tamanho);
		}
	}
}


void genVarPart(is_Nos* noactual, char *param, int tamanho)
{
	/* Funcao para ir buscar as variaveis e os seus tipos para depois converter para llvm */
	if(noactual != NULL){
		table *aux = encontra_na_tabela(noactual->valor);
		if(aux!=NULL){
			espacamento2(tamanho);
			if(strcmp(symtab->name, "program")==0)
			{
				if(strcmp(aux->type, "_integer_")==0){
					printf("@%s = global i32 0\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_real_")==0){
					printf("@%s = global double 0.0\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_boolean_")==0){
					printf("@%s = constant i1 0\n", noactual->valor);
				}
			} else {
				if(strcmp(aux->type, "_integer_")==0){
					printf("%%%s = alloca i32\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_real_")==0){
					printf("%%%s = alloca double\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_boolean_")==0){
					printf("%%%s = alloca i1\n", noactual->valor);
				}
			}	
		}
		genVarPart(noactual->nonext, NULL, tamanho);
	}
}

void genFuncPart(is_Nos* noactual, char *param, int tamanho)
{
	/* Funcao para ir buscar uma funcao pascal e converte-la para llvm */
	if(noactual != NULL){
		if(noactual->queraioeisto == is_FUNCDEF){
			// declaracao e corpo
			genFuncDef(noactual->nofilho, param, tamanho);
		}
		if(noactual->queraioeisto == is_FUNCDEF2){
			// só o corpo da funcao	
			//genFuncDef2(noactual->nofilho, param);
		}
		if(noactual->queraioeisto == is_FUNCDECL){
			// so a declaracao
			//genFuncDecl(noactual->nofilho, param);
		}
		printf("\n");
		genFuncPart(noactual->nonext, param, tamanho);
	}
}

void genFuncDef(is_Nos* noactual, char *param, int tamanho)
{
	table *original = symtab;
	table *aux = encontra_funcao_em_tudo(noactual->valor);
	if(aux!=NULL)
	{
		symtab = aux;
		if(strcmp(aux->type, "_integer_")==0)
		{
			printf("define i32 @%s() {\n", noactual->valor);
			generateCode(noactual->nonext, param, tamanho+1);
		}
		else if(strcmp(aux->type, "_real_")==0)
		{
			printf("define double @%s() {\n", noactual->valor);
			generateCode(noactual->nonext, param, tamanho+1);
		} 
		else if(strcmp(aux->type, "_boolean_")==0)
		{
			printf("define i1 @%s() {\n", noactual->valor);
			generateCode(noactual->nonext, param, tamanho+1);
		}
		symtab = original;
		printf("}\n");
	}
}

void genAssign(is_Nos* noactual, int tamanho)
{
	if(noactual != NULL){
		espacamento2(tamanho);
		table *mexer = encontra_em_tudo(noactual->valor);
		if(strcmp(symtab->name, "program")==0)
		{	
			// se variavel e global
			if(mexer != NULL && strcmp(mexer->type, "_integer_")==0){
				char *expr = genExpr(noactual->nonext);
				espacamento2(tamanho);
				switch(noactual->nonext->queraioeisto){
					case is_INTLIT:
						printf("store i32 %s", noactual->nonext->valor);
						break;
					case is_ID:
						if(strcmp(symtab->name, "program")==0){
							if(strcmp(expr,"_integer_")==0){
								printf("%%%d = load i32* @%s\n", tempname,noactual->nonext->valor);
								tempname++;
								printf("store i32 %%%d", tempname-1);
							}
						}else{
							printf("store i32 %%%s", noactual->nonext->valor);
						}
						break;
					default:
						printf("store i32 %%%d", tempname-1);
				}

				printf(", i32* @%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_real_")==0){
				char *expr = genExpr(noactual->nonext);
				if(strcmp(expr,"_integer_")==0){
					//ISTO N ESTA BEM
					printf("%%%d = load i32* @%s\n", tempname,noactual->nonext->valor);
					tempname++;
					printf("%%%d = sitofp i32 %%%d to double\n", tempname, tempname-1);
					tempname++;
					printf("store double %%%d", tempname-1);
				}else if(strcmp(expr,"_real_")==0){
					switch(noactual->nonext->queraioeisto){
					case is_INTLIT:
					case is_REALLIT:
						printf("store double %s", noactual->nonext->valor);
						break;
					case is_ID:
						if(strcmp(symtab->name, "program")==0){
							if(strcmp(expr,"_real_")==0){
								printf("%%%d = load double* @%s\n", tempname,noactual->nonext->valor);
								tempname++;
								printf("store double %%%d", tempname-1);
							}
						}else{
							printf("store double %%%s", noactual->nonext->valor);
						}
						break;
					}
				}
				printf(", double* @%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_boolean_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store i1 ");
				if(strcmp(expr,"_boolean_")==0){
					printf("%s", noactual->nonext->valor);
				}else{	
					if(strcmp(symtab->name, "program")==0){
						printf("%s", expr);
					}else{
						printf("%s", expr);
					}
				}
				printf(", i1* @%s\n", noactual->valor);
			}
		} else {
		// se variavel e local
			if(mexer != NULL && strcmp(mexer->type, "_integer_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store ");
				if(strcmp(expr,"_integer_")==0){
					printf("i32 ");
				}
				switch(noactual->nonext->queraioeisto){
					case is_INTLIT:
						printf("%s", noactual->nonext->valor);
						break;
					case is_ID:
						if(strcmp(symtab->name, "program")==0){
							printf("@%s", noactual->nonext->valor);
						}else{
							printf("%%%s", noactual->nonext->valor);
						}
						break;
				}
				printf(", i32* %%%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_real_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store ");
				if(strcmp(expr,"_integer_")==0){
					printf("i32 ");
				}else if(strcmp(expr,"_real_")==0){
					printf("double ");
				}
				switch(noactual->nonext->queraioeisto){
					case is_INTLIT:
					case is_REALLIT:
						printf("%s", noactual->nonext->valor);
						break;
					case is_ID:
						if(strcmp(symtab->name, "program")==0){
							printf("@%s", noactual->nonext->valor);
						}else{
							printf("%%%s", noactual->nonext->valor);
						}
						break;
				}
				printf(", double* %%%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_boolean_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store i1 ");
				if(strcmp(expr,"_string_")==0){
					printf("%s", noactual->nonext->valor);
				}else{
					if(strcmp(symtab->name, "program")==0){
						printf("%s", expr);
					}else{
						printf("%s", expr);
					}
				}
				printf(", i1* %%%s\n", noactual->valor);	
			}
		}
	}
}

char* genExpr(is_Nos* noactual)
{
	if(noactual != NULL){
		is_Nos *contadordevariaveis;
		table *aux;
		char *aux2, *aux3;
		int numero1;
		int numero2, fixa1=0,fixa2=0;
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
				}
				return NULL;

			case is_NOT: ;
				aux2 = genExpr(noactual->nofilho);
				if(aux2 != NULL){
					if(strcmp(aux2, "_boolean_")==0){
						// FALTA AQUI O NOT
						return aux2;
					}
				}
				return NULL;

			case is_PLUS:
			case is_MINUS: ;
				char * operador;
				aux2 = genExpr(noactual->nofilho);
				if(aux2 != NULL){
					if(strcmp(aux2, "_boolean_")==0 || strcmp(aux2, "_type_")==0){
						return NULL;
					}else{
						switch(noactual->queraioeisto){
							case is_PLUS:
								//printf("%%%d add = i32 %%0, 1\n", tempname);
								break;
							case is_MINUS:
								//printf("%%%d sub = i32 %%0, 1\n", tempname);
								break;
						}
						return aux2;
					}
				}
				return NULL;

			case is_DIV:
			case is_MOD: ;
				aux2 = genExpr(noactual->nofilho);
				numero1 = tempname-1;
				aux3 = genExpr(noactual->nofilho->nonext);
				numero2 = tempname-1;
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_integer_")==0 && strcmp(aux3, "_integer_")==0){
					switch(noactual->queraioeisto){
						case is_DIV:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = udiv i32 %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = udiv i32 %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
							break;
						case is_MOD:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = urem i32 %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = urem i32 %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
							break;
					}
					return aux2;
				}
				return NULL;

			case is_MULT:
			case is_ADD:
			case is_SUB: ;
				aux2 = genExpr(noactual->nofilho);
				numero1 = tempname-1;
				aux3 = genExpr(noactual->nofilho->nonext);
				numero2 = tempname-1;
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0
																	&& strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
					if(strcmp(aux2, "_integer_")==0 && strcmp(aux3, "_integer_")==0){
						switch(noactual->queraioeisto){
							case is_ADD:
							if(noactual->nofilho->queraioeisto == is_ID){
							if(strcmp(symtab->name, "program")==0){
									table *paraverificar = encontra_na_tabela(noactual->nofilho->valor);
									if(paraverificar!= NULL){
										printf("%%%d = load i32, i32* @%s\n", tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}
									else{
										printf("%%%d = load i32, i32* %%%s\n", tempname,noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}
								}else{
									table *paraverificar = encontra_na_tabela(noactual->nofilho->valor);
									if(paraverificar == NULL){
										printf("%%%d = load i32, i32* @%s\n",tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}else{
										printf("%%%d = load i32, i32* %%%s\n",tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}

								}
							}
							if(noactual->nofilho->nonext->queraioeisto == is_ID){
							if(strcmp(symtab->name, "program")==0){
									table *paraverificar = encontra_na_tabela(noactual->nofilho->nonext->valor);
									if(paraverificar!= NULL){
										printf("%%%d = load i32, i32* @%s\n", tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}
									else{
										printf("%%%d = load i32, i32* %%%s\n", tempname,noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}
								}else{
									table *paraverificar = encontra_na_tabela(noactual->nofilho->nonext->valor);
									if(paraverificar == NULL){
										printf("%%%d = load i32, i32* @%s\n",tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}else{
										printf("%%%d = load i32, i32* %%%s\n",tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}

								}
							}
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = add i32 %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else if(noactual->nofilho->queraioeisto == is_ID){
								printf("%%%d = add i32 %%%d,", tempname, fixa1);
								tempname++;
							}else{
								printf("%%%d = add i32 %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else if(noactual->nofilho->nonext->queraioeisto == is_ID){
								printf(" %%%d\n", fixa2);
							}else{
								printf(" %%%d\n", numero2);
							}
								break;
							case is_SUB:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = sub i32 %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = sub i32 %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}

								break;
							case is_MULT:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = mul i32 %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = mul i32 %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
								break;
						}
						return "_integer_";
					}else{
						switch(noactual->queraioeisto){
							case is_ADD:
							if(noactual->nofilho->queraioeisto == is_ID){
							if(strcmp(symtab->name, "program")==0){
									table *paraverificar = encontra_na_tabela(noactual->nofilho->valor);
									if(paraverificar!= NULL){
										printf("%%%d = load double, double* @%s\n", tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}
									else{
										printf("%%%d = load double, double* %%%s\n", tempname,noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}
								}else{
									table *paraverificar = encontra_na_tabela(noactual->nofilho->valor);
									if(paraverificar == NULL){
										printf("%%%d = load double, double* @%s\n",tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}else{
										printf("%%%d = load double, double* %%%s\n",tempname, noactual->nofilho->valor);
										fixa1 = tempname;
										tempname++;
									}

								}
							}
							if(noactual->nofilho->nonext->queraioeisto == is_ID){
							if(strcmp(symtab->name, "program")==0){
									table *paraverificar = encontra_na_tabela(noactual->nofilho->nonext->valor);
									if(paraverificar!= NULL){
										printf("%%%d = load double, double* @%s\n", tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}
									else{
										printf("%%%d = load double, double* %%%s\n", tempname,noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}
								}else{
									table *paraverificar = encontra_na_tabela(noactual->nofilho->nonext->valor);
									if(paraverificar == NULL){
										printf("%%%d = load double, double* @%s\n",tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}else{
										printf("%%%d = load double, double* %%%s\n",tempname, noactual->nofilho->nonext->valor);
										fixa2 = tempname;
										tempname++;
									}

								}
							}
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = add double %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else if(noactual->nofilho->queraioeisto == is_ID){
								printf("%%%d = add double %%%d,", tempname, fixa1);
								tempname++;
							}else{
								printf("%%%d = add double %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else if(noactual->nofilho->nonext->queraioeisto == is_ID){
								printf(" %%%d\n", fixa2);
							}else{
								printf(" %%%d\n", numero2);
							}
								break;
							case is_SUB:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = sub double %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = sub double %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
								break;
							case is_MULT:
							if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = mul double %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = mul double %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
								break;
						}
						return "_real_";
					}
				}
				return NULL;

			case is_REALDIV: ;
				aux2 = genExpr(noactual->nofilho);
				numero1 = tempname-1;
				aux3 = genExpr(noactual->nofilho->nonext);
				numero2 = tempname-1;
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0
									&& strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
					if(noactual->nofilho->queraioeisto == is_INTLIT || noactual->nofilho->queraioeisto == is_REALLIT){
								printf("%%%d = fdiv double %s,", tempname, noactual->nofilho->valor);
								tempname++;
							}else{
								printf("%%%d = fdiv double %%%d,", tempname, numero1);
								tempname++;
							}
							if(noactual->nofilho->nonext->queraioeisto == is_INTLIT || noactual->nofilho->nonext->queraioeisto == is_REALLIT){
								printf(" %s\n", noactual->nofilho->nonext->valor);
							}else{
								printf(" %%%d\n", numero2);
							}
					return "_real_";
				}
				return NULL;

			case is_LESS:
			case is_GEQUAL:
			case is_LEQUAL:
			case is_GREATER: ;
				aux2 = genExpr(noactual->nofilho);
				aux3 = genExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0
										&& strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
					switch(noactual->queraioeisto){
						case is_LESS:
							printf("%%%d slt = i1 %%1, 1\n", tempname);
							tempname++;
							break;
						case is_GEQUAL:
							printf("%%%d sge = i1 %%1, 1\n", tempname);
							tempname++;
							break;
						case is_LEQUAL:
							printf("%%%d sle = i1 %%1, 1\n", tempname);
							tempname++;
							break;
						case is_GREATER:
							printf("%%%d sgt = i1 %%1, 1\n", tempname);
							tempname++;
							break;
					}
					return "_boolean_";
				}else{
					if(strcmp(aux2, "_boolean_")==0 && strcmp(aux3, "_boolean_")==0 && strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
						switch(noactual->queraioeisto){
							case is_LESS:
								printf("%%%d slt = i1 %%1, 1\n", tempname);
								tempname++;
								break;
							case is_GEQUAL:
								printf("%%%d sge = i1 %%1, 1\n", tempname);
								tempname++;
								break;
							case is_LEQUAL:
								printf("%%%d sle = i1 %%1, 1\n", tempname);
								tempname++;
								break;
							case is_GREATER:
								printf("%%%d sgt = i1 %%1, 1\n", tempname);
								tempname++;
								break;
						}
						return "_boolean_";
					}
				}
				return NULL;

			case is_DIFFERENT:
			case is_EQUALS: ;
				aux2 = genExpr(noactual->nofilho);
				aux3 = genExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")!=0 && strcmp(aux3, "_boolean_")!=0
										&& strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
					switch(noactual->queraioeisto){
						case is_DIFFERENT:
							printf("%%cmp%d = icmp ne i1 %%0, 0", temp_compname);
							temp_compname++;
							break;
						case is_EQUALS:
							printf("%%cmp%d = icmp eq i1 %%0, 0", temp_compname);
							temp_compname++;
							break;
					}
					return "_boolean_";
				}else{
					if(strcmp(aux2, "_boolean_")==0 && strcmp(aux3, "_boolean_")==0 && strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
						switch(noactual->queraioeisto){
							case is_DIFFERENT:
								printf("%%cmp%d = icmp ne i1 %%0, 0", temp_compname);
								temp_compname++;
								break;
							case is_EQUALS:
								printf("%%cmp%d = icmp eq i1 %%0, 0", temp_compname);
								temp_compname++;
								break;
						}
						return "_boolean_";
					}
				}
				return NULL;

			case is_OR:
			case is_AND: ;
				aux2 = genExpr(noactual->nofilho);
				aux3 = genExpr(noactual->nofilho->nonext);
				if(aux2 != NULL && aux3 != NULL && strcmp(aux2, "_boolean_")==0 && strcmp(aux3, "_boolean_")==0
						&& strcmp(aux2, "_type_")!=0 && strcmp(aux3, "_type_")!=0){
					switch(noactual->queraioeisto){
						case is_OR:
							printf("%%cmp%d = or i1 %%0, 0", temp_compname);
							temp_compname++;
							break;
						case is_AND:
							printf("%%cmp%d = and i1 %%0, 0", temp_compname);
							temp_compname++;
							break;
					}
					return "_boolean_";
				}
				return NULL;
			
			/*case is_CALL: ;
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
									if(aux2 != NULL){
										return aux->type;
									}
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

		}*/






		}
	}
}

void genWriteLn(is_Nos* noactual, int tamanho)
{
	if(noactual != NULL){
		int i = strlen(noactual->valor);
		printf("@.str%d = private unnamed_addr constant ", temp_strname);
		printf("[%d x i8] c\"%s\"\n", i+1, noactual->valor);
		printf("declare i32 @puts(i8* nocapture) nounwind\n");


		espacamento2(tamanho);
		printf("%%cast210 = getelementptr [%d x i8]* @.str%d, i64 0, i64 0\n", i+1, temp_strname);
		espacamento2(tamanho);
		printf("call i32 @puts(i8* %%cast210)\n");
		genWriteLn(noactual->nonext, tamanho);
	}
}

void genIfThen(is_Nos* noactual)
{
	
}

void genWhile(is_Nos* noactual)
{
	
}

void genRepeat(is_Nos* noactual)
{
	
}

void genValParam(is_Nos* noactual)
{

}
/* Funcao que introduz o espacamento correcto (em pontos) na impressao do código - Faz parte do show_prog */
void espacamento2(int tamanho){
	int i;
	for(i=0;i<tamanho;i++){
		printf("\t");
	}
}

