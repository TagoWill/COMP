#include "functions.h"
#include "structures.h"

Node *newNode(){
	Node* novo = malloc(sizeof(Node));
	novo->type = Null;
	novo->value = NULL;
	novo->next = NULL;
	novo->child = NULL;

	return novo;
}

Node *leaf(nodeType type, char *value){
	Node* novo = newNode();
	novo->type = type;
	novo->value = value;

	return novo;
}

Node *addNode(nodeType type, Node *child){
	Node* novo = newNode();
	novo->type = type;
	novo->child = child;

	return novo;
}

Node *add(Node *no1, Node *no2){
	Node *current = no1;
	if(no1==NULL){
		return no2;
	}
	while(current->next!=NULL){
		current=current->next;
	}
	current->next = no2;

	return no1;
}

void printNode(Node *no, int depth){
	register int i;

	if(no == NULL) return;

	for(i=0; i<depth;i++) printf("..");

	if(no -> value != NULL) printf("%s(%s)\n", figureOutAST(no -> type), no-> value );
	else printf("%s\n", figureOutAST(no->type));

	if(no->child != NULL) printNode(no->child, depth+1);
	if(no->next != NULL) printNode(no->next, depth);

}



char *figureOutAST(nodeType type){
	switch(type){
		case String:
			return "String";
		case Assign:
			return "Assign";
		case Colon:
			return "Colon";
		case Comma:
			return "Comma";
		case Dot:
			return "Dot";
		case Semic:
			return "Semic";
		case Begins:
			return "Begin";
		case Do:
			return "Do";
		case And:
			return "And";
		case Or:
			return "Or";
		case Lt:
			return "Lt";
		case Gt:
			return "Gt";
		case Eq:
			return "Eq";
		case Neq:
			return "Neq";
		case Leq:
			return "Leq";
		case Geq:
			return "Geq";
		case Plus:
			return "Plus";
		case Minus:
			return "Minus";
		case Add:
			return "Add";
		case Mul:
			return "Mul";
		case RealDiv:
			return "RealDiv";
		case Mod:
			return "Mod";
		case Div:
			return "Div";
		case Else:
			return "Else";
		case End:
			return "End";
		case Forward:
			return "Forward";
		case Function:
			return "Function";
		case If:
			return "If";
		case Lbrac:
			return "Lbrac";
		case Rbrac:
			return "Rbrac";
		case Not:
			return "Not";
		case Output:
			return "Output";
		case Paramstr:
			return "Paramstr";
		case Program:
			return "Program";
		case Repeat:
			return "Repeat";
		case Then:
			return "Then";
		case Until:
			return "Until";
		case Val:
			return "Val";
		case Var:
			return "Var";
		case While:
			return "While";
		case Writeln:
			return "WriteLn";
		case Reserved:
			return "Reserved";
		case Call:
			return "Call";
		case Id:
			return "Id";
		case Intlit:
			return "IntLit";
		case Reallit:
			return "RealLit";
		case VarPart:
			return "VarPart";
		case VarDecl:
			return "VarDecl";
		case FuncPart:
			return "FuncPart";
		case FuncDecl:
			return "FuncDecl";
		case StatPart:
			return "StatPart";
		case StatList:
			return "StatList";
		case IfElse:
			return "IfElse";
		case ValParam:
			return "ValParam";
		case Sub:
			return "Sub";
		case FuncDef:
			return "FuncDef";
		case FuncDef2:
			return "FuncDef2";
		case FuncParams:
			return "FuncParams";
		case VarParams:
			return "VarParams";
		case Params:
			return "Params";
		case Null:
			return "Null";
		default:
			return "Not Defined";
	}
	return "";
}
