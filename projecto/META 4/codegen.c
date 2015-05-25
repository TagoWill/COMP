#include "structures.h"
#include "codegen.h"

void generateCode(is_Node* noactual, char* param)
{	
	//std::cout << "Generating code...\n";
	
	/* Create the top level interpreter function to call as entry */
	vector<const Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);
	
	/* Push a new variable/block context */
	pushBlock(bblock);
	root.codeGen(*this); /* emit bytecode for the toplevel block */
	ReturnInst::Create(getGlobalContext(), bblock);
	popBlock();
	
	/* Print the bytecode in a human-readable format 
	   to see if our program compiled properly
	 */
	//std::cout << "Code is generated.\n";
	PassManager pm;
	pm.add(createPrintModulePass(&outs()));
	pm.run(*module);


	if(noactual != NULL){
		switch(noactual->queraioeisto){
			case is_PROGRAM:
				//
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
}

void genVarPart(is_Node* root, char *param)
{

}

void genFuncPart(is_Node* root, char *param);
{

}

void genAssign(is_Node* root);
{

}

void genWriteLn(is_Node* root);
{

}

void genIfThen(is_Node* root);
{

}

void genWhile(is_Node* root);
{

}

void genRepeat(is_Node* root);
{

}

void genValParam(is_Node* root);
{
	
}

/* Executes the AST by running the main function */
GenericValue runCode() {
	//std::cout << "Running code...\n";
	ExistingModuleProvider *mp = new ExistingModuleProvider(module);
	ExecutionEngine *ee = ExecutionEngine::create(mp, false);
	vector<GenericValue> noargs;
	GenericValue v = ee->runFunction(mainFunction, noargs);
	//std::cout << "Code was run.\n";
	return v;
}
