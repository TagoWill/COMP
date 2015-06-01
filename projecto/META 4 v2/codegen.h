#include "structures.h"

void generateCode(is_Nos* noactual, char* param, int tamanho);
void genVarPart(is_Nos* noactual, char *param, int tamanho);
void genFuncPart(is_Nos* noactual, char *param, int tamanho);
void genFuncDef(is_Nos* noactual, char *param, int tamanho);
void genAssign(is_Nos* noactual, int tamanho);
char* genExpr(is_Nos* noactual);
void genWriteLn(is_Nos* noactual, int tamanho);
void genIfThen(is_Nos* noactual);
void genWhile(is_Nos* noactual);
void genRepeat(is_Nos* noactual);
void genValParam(is_Nos* noactual);
void espacamento2(int tamanho);
