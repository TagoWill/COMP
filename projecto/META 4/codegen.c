#include "codegen.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void generateCode(is_Nos* noactual, char* param)
{
	if(noactual != NULL){
		switch(noactual->queraioeisto){
			case is_PROGRAM:
				//printf("is_PROGRAM\n");
				printf("define i32 @main() {\n");
				generateCode(noactual->nofilho, param);
				generateCode(noactual->nonext, param);
				printf("}\n");
				break;
			case is_VARDECL:
				printf("is_VARDECL\n");
				genVarPart(noactual->nofilho, NULL);
				generateCode(noactual->nonext, NULL);
				break;
			case is_VARPARAMS:
				printf("is_VARPARAMS\n");
				genVarPart(noactual->nofilho, "varparam");
				generateCode(noactual->nonext, param);
				break;
			case is_PARAMS:
				printf("is_PARAMS\n");
				genVarPart(noactual->nofilho, "param");
				generateCode(noactual->nonext, param);
				break;
			case is_FUNCPART:
				printf("is_FUNCPART\n");
				genFuncPart(noactual->nofilho, NULL);
				generateCode(noactual->nonext, param);
				break;
			case is_ASSIGN:
				printf("is_ASSIGN\n");
				genAssign(noactual->nofilho);
				generateCode(noactual->nonext, param);
				break;
			case is_WRITELN:
				printf("is_WRITELN\n");
				genWriteLn(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_IFELSE:
				printf("is_IFELSE\n");
				genIfThen(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_WHILE:
				printf("is_WHILE\n");
				genWhile(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_REPEAT:
				printf("is_REPEAT\n");
				genRepeat(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_VALPARAM:
				printf("is_VALPARAM\n");
				genValParam(noactual);
				generateCode(noactual->nonext, param);
			default:
				generateCode(noactual->nofilho, param);
				generateCode(noactual->nonext, param);
		}
	}
}

void genVarPart(is_Nos* root, char *param)
{
	/* Funcao para ir buscar as variaveis e os seus tipos para depois converter para llvm */
	printf("%%%s = alloca i32\n", root->valor);
}

void genFuncPart(is_Nos* root, char *param)
{
	/* Funcao para ir buscar uma funcao pascal e converte-la para llvm */
	printf("define tipo nome da funcao() {");
}

void genAssign(is_Nos* root)
{

}

void genWriteLn(is_Nos* root)
{

}

void genIfThen(is_Nos* root)
{
	
}

void genWhile(is_Nos* root)
{
	
}

void genRepeat(is_Nos* root)
{
	
}

void genValParam(is_Nos* root)
{

}
