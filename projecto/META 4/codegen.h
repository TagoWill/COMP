#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/Scalar.h>
#include <stdlib.h>
#include <stdio.h>

void generateCode(is_Node* root);
void genVarPart(is_Node* root, char *param);
void genFuncPart(is_Node* root, char *param);
void genAssign(is_Node* root);
void genWriteLn(is_Node* root);
void genIfThen(is_Node* root);
void genWhile(is_Node* root);
void genRepeat(is_Node* root);
void genValParam(is_Node* root);