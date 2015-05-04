#include "structures.h"
#include "symbol_table.h"


int check_program(is_Nos* noactual, char* param);
char *checkExpr(is_Nos *noactual);
void checkValParam(is_Nos *noactual);
void checkRepeat(is_Nos *noactual);
void checkWhile(is_Nos *noactual);
void checkIfThen(is_Nos *noactual);
void checkWriteLn(is_Nos *noactual);
void checkAssign(is_Nos *noactual);
char *checkVarPart(is_Nos *noactual, char *param);
void checkFuncPart(is_Nos *noactual, char *param);
void checkFuncDeclaration(is_Nos *noactual, char *param);
