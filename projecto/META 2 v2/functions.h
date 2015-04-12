#include "structures.h"


is_Prog *insert_Prog(ProgHeading SEMIC ProgBlock DOT);

is_ProgHeading *insert_ProgHeading(PROGRAM ID LBRAC OUTPUT RBRAC);

is_ProgBlock *insert_ProgBlock(VarPart FuncPart StatPart);

is_VarPart *insert_VarPart(VAR VarDeclaration SEMIC VarPart2);

is_VarPart2 *insert_VarPart2(VarDeclaration SEMIC VarPart2);

is_VarDeclaration *insert_VarDeclaration(IDList COLON ID);

is_IDList *insert_IDList(ID IDList2);

is_IDList2 *insert_IDList2(COMMA ID IDList2);

is_FuncPart *insert_FuncPart(FuncDeclaration SEMIC FuncPart);

is_FuncDeclaration *insert_FuncDeclaration(FuncHeading SEMIC FORWARD		FuncIdent SEMIC FuncBlock 			FuncHeading SEMIC FuncBlock);

is_FuncHeading *insert_FuncHeading(FUNCTION ID FormalParamList COLON ID 			FUNCTION ID COLON ID);

is_FuncIdent *insert_FuncIdent(FUNCTION ID);

is_FormalParamList *insert_FormalParamList(LBRAC FormalParams2 FormalParams RBRAC);

is_FormalParams *insert_FormalParams(SEMIC FormalParams2 FormalParams);

is_FormalParams2 *insert_FormalParams2(VAR IDList COLON ID 					IDList COLON ID);

is_FuncBlock *insert_FuncBlock(VarPart StatPart);

is_StatPart *insert_StatPart(CompStat);

is_CompStat *insert_CompStat(BEG StatList END);

is_StatList *insert_StatList(Stat StatList2);

is_StatList2 *insert_StatList2(SEMIC Stat StatList2);

is_Stat *insert_Stat(CompStat 		Stat2 			WRITELN);

is_Stat2 *insert_Stat2(ID ASSIGN Expr);

is_StatITE *insert_StatITE(IF Expr THEN Stat ELSE Stat);

is_StatIWR *insert_StatIWR(IF Expr THEN Stat 			WHILE Expr DO Stat 			REPEAT StatList UNTIL Expr);

is_StatV *insert_StatV(VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC);

is_StatWR *insert_StatWR(WRITELN WritelnPList);

is_WritelnPList *insert_WritelnPList(LBRAC Expr RBRAC WritelnPList2 			LBRAC STRING RBRAC WritelnPList2);

is_WritelnPList2 *insert_WritelnPList2(COMMA STRING WritelnPList2 			COMMA Expr WritelnPList2);

is_Expr *insert_Expr(LBRAC Expr RBRAC 			INTLIT 				REALLIT 			ID);

is_ExprO *insert_ExprO(Expr PLUS Expr 	Expr MINUS Expr 		Expr AND Expr 		Expr OR Expr 			Expr MULT Expr 			Expr DIV Expr 		Expr MOD Expr 		xpr GREATER Expr 		Expr LESS Expr 			Expr GEQUAL Expr 		Expr EQUALS Expr 		Expr DIFFERENT Expr);

is_ExprA *insert_ExprAMN(AND Expr 		MINUS Expr 			NOT Expr);

is_ExprI *insert_ExprI(ID ParamList);

is_ParamList *insert_ParamList(LBRAC Expr ParamList2 RBRAC);

is_ParamList2 *insert_ParamList2(COMMA Expr ParamList2);

