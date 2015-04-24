#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef enum{
	VarPart, VarDecl, FuncPart, StatPart, FuncDecl, FuncDef, FuncDef2, FuncParams, Params, VarParams,
	IfElse, StatList, ValParam, Add, Call, RealDiv, Sub, 
	String, Assign, Colon, Comma, Dot, ObligatoryEasterEgg, Semic, Begins, Do, And, Or, Lt, Gt, Eq, Neq, Leq, Geq,
	Plus, Minus, Mul, Mod, Div, Else, End, Forward, Function, If, Lbrac, Rbrac, Not, 
	Output, Paramstr, Program, Repeat, Then, Until, Val, Var, While, Writeln, Reserved, Id, Intlit, Reallit, Null
}nodeType;

typedef struct node
{
	nodeType type;
	char *value;
	struct node *next;
	struct node *child;
} Node;

/*typedef struct tableElement
{
	char *id;
	nodeType type;
	int param;
	int ret;
	struct tableElement *next;
	struct tableElement *child;
} TableElement;
*/
#endif
