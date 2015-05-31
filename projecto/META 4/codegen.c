#include "codegen.h"
#include "symbol_table.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

extern table* symtab;

int ismain = 1;

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
				printf("is_VARPARAMS\n\t");
				genVarPart(noactual->nofilho, "varparam", tamanho);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_PARAMS:
				printf("is_PARAMS\n\t");
				genVarPart(noactual->nofilho, "param", tamanho);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_FUNCPART:
				//printf("is_FUNCPART\n\t");
				genFuncPart(noactual->nofilho, NULL, tamanho);
				if(ismain == 0){
					printf("define i32 @main() {\n");
				}
				generateCode(noactual->nonext, param, tamanho+1);
				if(ismain == 0){
					printf("\tret i32 0\n}\n");
				}
				break;
			case is_ASSIGN:
				//printf("is_ASSIGN\n\t");
				genAssign(noactual->nofilho, tamanho);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_WRITELN:
				printf("is_WRITELN\n");
				genWriteLn(noactual);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_IFELSE:
				printf("is_IFELSE\n");
				genIfThen(noactual);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_WHILE:
				printf("is_WHILE\n");
				genWhile(noactual);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_REPEAT:
				printf("is_REPEAT\n");
				genRepeat(noactual);
				generateCode(noactual->nonext, param, tamanho);
				break;
			case is_VALPARAM:
				printf("is_VALPARAM\n");
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
					printf("@%s = alloca i32\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_real_")==0){
					printf("@%s = alloca double\n", noactual->valor);
				}
				else if(strcmp(aux->type, "_boolean_")==0){
					printf("@%s = alloca i1\n", noactual->valor);
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
	ismain = 1;
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
	ismain = 0;
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
			printf("define i32 %s() {\n", noactual->valor);
			generateCode(noactual->nonext, param, tamanho+1);
		}
		else if(strcmp(aux->type, "_real_")==0)
		{
			printf("define double %s() {\n", noactual->valor);
			generateCode(noactual->nonext, param, tamanho+1);
		} 
		else if(strcmp(aux->type, "_boolean_")==0)
		{
			printf("define i1 %s() {\n", noactual->valor);
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
				printf("store i32 ");
				if(strcmp(expr,"_integer_")==0 || strcmp(expr,"_real_")==0){
					printf("%s", noactual->nonext->valor);
				}else{	
					if(strcmp(symtab->name, "program")==0){
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
					}
				}
				printf(", i32* @%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_real_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store double ");
				if(strcmp(expr,"_integer_")==0 || strcmp(expr,"_real_")==0){
					printf("%s", noactual->nonext->valor);
				}else{	
					if(strcmp(symtab->name, "program")==0){
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
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
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
					}
				}
				printf(", i1* @%s\n", noactual->valor);
			}
		} else {
		// se variavel e local
			if(mexer != NULL && strcmp(mexer->type, "_integer_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store i32 ");
				if(strcmp(expr,"_integer_")==0 || strcmp(expr,"_real_")==0){
					printf("%s", noactual->nonext->valor);
				}else{
					if(strcmp(symtab->name, "program")==0){
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
					}
				}
				printf(", i32* %%%s\n", noactual->valor);
			}
			else if(mexer != NULL && strcmp(mexer->type, "_real_")==0){
				char *expr = genExpr(noactual->nonext);
				printf("store double ");
				if(strcmp(expr,"_integer_")==0 || strcmp(expr,"_real_")==0){
					printf("%s", noactual->nonext->valor);
				}else{
					if(strcmp(symtab->name, "program")==0){
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
					}
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
						printf("@%s", expr);
					}else{
						printf("%%%s", expr);
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
					return aux->name;
				}
			return NULL;
		}
	}
}

void genWriteLn(is_Nos* noactual)
{

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
