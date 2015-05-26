#include "structures.h"
#include "codegen.h"

void generateCode(is_Node* noactual, char* param)
{
	LLVMModuleRef mod = NULL;

	if(noactual != NULL){
		switch(noactual->queraioeisto){
			case is_PROGRAM:
				mod = LLVMModuleCreateWithName("myprogram");
				generateCode(noactual->nofilho, param);
				generateCode(noactual->nonext, param);
				break;
			case is_VARDECL:
				genVarPart(noactual->nofilho, NULL);
				generateCode(noactual->nonext, NULL);
				break;
			case is_VARPARAMS:
				genVarPart(noactual->nofilho, "varparam");
				generateCode(noactual->nonext, param);
				break;
			case is_PARAMS:
				genVarPart(noactual->nofilho, "param");
				generateCode(noactual->nonext, param);
				break;
			case is_FUNCPART:
				genFuncPart(noactual->nofilho, NULL);
				generateCode(noactual->nonext, param);
				break;
			case is_ASSIGN:
				genAssign(noactual->nofilho);
				generateCode(noactual->nonext, param);
				break;
			case is_WRITELN:
				genWriteLn(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_IFELSE:
				genIfThen(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_WHILE:
				genWhile(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_REPEAT:
				genRepeat(noactual);
				generateCode(noactual->nonext, param);
				break;
			case is_VALPARAM:
				genValParam(noactual);
				generateCode(noactual->nonext, param);
			default:
				generateCode(noactual->nofilho, param);
				generateCode(noactual->nonext, param);
		}
	}

	if(mod!=NULL)
	{
		LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
  		LLVMDisposeMessage(error); // Handler == LLVMAbortProcessAction -> No need to check errors

  		LLVMExecutionEngineRef engine;
  		LLVMModuleProviderRef provider = LLVMCreateModuleProviderForExistingModule(mod);
  		error = NULL;
  		LLVMCreateJITCompiler(&engine, provider, &error);
  		if(error) {
    		fprintf(stderr, "%s\n", error);
    		LLVMDisposeMessage(error);
    		abort();
  		}

  		LLVMPassManagerRef pass = LLVMCreatePassManager();
  		LLVMAddTargetData(LLVMGetExecutionEngineTargetData(engine), pass);
  		LLVMAddConstantPropagationPass(pass);
  		LLVMAddInstructionCombiningPass(pass);
  		LLVMAddPromoteMemoryToRegisterPass(pass);
  		// LLVMAddDemoteMemoryToRegisterPass(pass); // Demotes every possible value to memory
  		LLVMAddGVNPass(pass);
  		LLVMAddCFGSimplificationPass(pass);
  		LLVMRunPassManager(pass, mod);
  		LLVMDumpModule(mod);

  		LLVMGenericValueRef exec_args[] = {LLVMCreateGenericValueOfInt(LLVMInt32Type(), 10, 0)};
  		LLVMGenericValueRef exec_res = LLVMRunFunction(engine, fac, 1, exec_args);
  		fprintf(stderr, "\n");
  		fprintf(stderr, "; Running program with JIT...\n");
  		fprintf(stderr, "; Result: %d\n", LLVMGenericValueToInt(exec_res, 0));

  		LLVMDisposePassManager(pass);
  		LLVMDisposeBuilder(builder);
  		LLVMDisposeExecutionEngine(engine);
  	}	
}

void genVarPart(is_Node* root, char *param)
{
	/* Funcao para ir buscar as variaveis e os seus tipos para depois converter para llvm */
}

void genFuncPart(is_Node* root, char *param)
{
	/* Funcao para ir buscar uma funcao pascal e converte-la para llvm */
	if(noactual != NULL)
	{
		LLVMTypeRef fac_args[] = { LLVMInt32Type() };
  		LLVMValueRef fac = LLVMAddFunction(mod, "fac", LLVMFunctionType(LLVMInt32Type(), fac_args, 1, 0));
  		LLVMSetFunctionCallConv(fac, LLVMCCallConv);
  		LLVMValueRef n = LLVMGetParam(fac, 0);
	}
}

void genAssign(is_Node* root);
{

}

void genWriteLn(is_Node* root);
{

}

void genIfThen(is_Node* root);
{
	/*LLVMBasicBlockRef entry = LLVMAppendBasicBlock(fac, "entry");
	LLVMBasicBlockRef iftrue = LLVMAppendBasicBlock(fac, "iftrue");
  	LLVMBasicBlockRef iffalse = LLVMAppendBasicBlock(fac, "iffalse");
	LLVMBasicBlockRef end = LLVMAppendBasicBlock(fac, "end");
  	LLVMBuilderRef builder = LLVMCreateBuilder();

  	LLVMPositionBuilderAtEnd(builder, entry);
  	LLVMValueRef If = LLVMBuildICmp(builder, LLVMIntEQ, n, LLVMConstInt(LLVMInt32Type(), 0, 0), "n == 0");
  	LLVMBuildCondBr(builder, If, iftrue, iffalse);

  	LLVMPositionBuilderAtEnd(builder, iftrue);
  	LLVMValueRef res_iftrue = LLVMConstInt(LLVMInt32Type(), 1, 0);
  	LLVMBuildBr(builder, end);

  	LLVMPositionBuilderAtEnd(builder, iffalse);
  	LLVMValueRef n_minus = LLVMBuildSub(builder, n, LLVMConstInt(LLVMInt32Type(), 1, 0), "n - 1");
  	LLVMValueRef call_fac_args[] = {n_minus};
  	LLVMValueRef call_fac = LLVMBuildCall(builder, fac, call_fac_args, 1, "fac(n - 1)");
  	LLVMValueRef res_iffalse = LLVMBuildMul(builder, n, call_fac, "n * fac(n - 1)");
  	LLVMBuildBr(builder, end);

  	LLVMPositionBuilderAtEnd(builder, end);
  	LLVMValueRef res = LLVMBuildPhi(builder, LLVMInt32Type(), "result");
  	LLVMValueRef phi_vals[] = {res_iftrue, res_iffalse};
  	LLVMBasicBlockRef phi_blocks[] = {iftrue, iffalse};
  	LLVMAddIncoming(res, phi_vals, phi_blocks, 2);
  	LLVMBuildRet(builder, res);*/
}

void genWhile(is_Node* root);
{
	/*LLVMBasicBlockRef entry_while = LLVMAppendBasicBlock(fac, "entry_while");
	LLVMBasicBlockRef end_do = LLVMAppendBasicBlock(fac, "end_do");
  	LLVMBuilderRef builder = LLVMCreateBuilder();

  	LLVMPositionBuilderAtEnd(builder, entry_while);
  	LLVMPositionBuilderAtEnd(builder, end_do);*/
}

void genRepeat(is_Node* root);
{
	/*LLVMBasicBlockRef entry_repeat = LLVMAppendBasicBlock(fac, "entry_repeat");
	LLVMBasicBlockRef end_while = LLVMAppendBasicBlock(fac, "end_while");
  	LLVMBuilderRef builder = LLVMCreateBuilder();

  	LLVMPositionBuilderAtEnd(builder, entry_repeat);
  	LLVMPositionBuilderAtEnd(builder, end_while);*/
}

void genValParam(is_Node* root);
{
	
}
