#include "structures.h"
#include "symbol_table.h"


int check_program(is_Nos* noactual, char* param);
void checkAssign(is_Nos *noactual);
char *checkVarPart(is_Nos *noactual, char *param);
void checkFuncPart(is_Nos *noactual);
void checkFuncDeclaration(is_Nos *noactual);