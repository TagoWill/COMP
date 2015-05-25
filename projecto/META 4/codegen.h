#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/Instructions.h>
#include <llvm/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/ModuleProvider.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

/*class NBlock;

class CodeGenBlock {
public:
    BasicBlock *block;
    std::map<std::string, Value*> locals;
};

class CodeGenerator {
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;

public:
    Module *module;
    CodeGenerator() { module = new Module("main", getGlobalContext()); }
    
    void generateCode(NBlock& root);
    GenericValue runCode();
    std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};*/

void generateCode(is_Node* root);
void genVarPart(is_Node* root, char *param);
void genFuncPart(is_Node* root, char *param);
void genAssign(is_Node* root);
void genWriteLn(is_Node* root);
void genIfThen(is_Node* root);
void genWhile(is_Node* root);
void genRepeat(is_Node* root);
void genValParam(is_Node* root);
void runCode();