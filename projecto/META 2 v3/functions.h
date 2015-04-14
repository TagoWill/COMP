#include "structures.h"


is_Prog *insert_Prog(is_ProgHeading *iph, is_ProgBlock *ipb);

is_ProgHeading *insert_ProgHeading(char *valor);

is_ProgBlock *insert_ProgBlock(is_VarPart_List *ivp, is_FuncPart_List *ifpl, is_StatPart *isp);

is_VarPart_List *insert_VarPart(is_VarDeclaration *ivd, is_VarPart_List *list);

is_VarDeclaration *insert_VarDeclaration(is_IDList_List *iIDlist, char *value);

is_IDList_List *insert_IDList(char *value, is_IDList_List *list);

is_FuncPart_List *insert_FuncPart(is_FuncDeclaration *ifd, is_FuncPart_List *list);

is_FuncDeclaration *insert_FuncDeclarationH(is_FuncHeading *ifh,is_FuncBlock *ifb);

is_FuncDeclaration *insert_FuncDeclarationI(is_FuncIdent *ifi,is_FuncBlock *ifb);

is_FuncHeading *insert_FuncHeading(char *value1, is_FormalParamList * ifpl, char *value2);

is_FuncIdent *insert_FuncIdent(char *value);

is_FormalParamList *insert_FormalParamList(is_FormalParams *ifp,is_FormalParamList *list);

is_FormalParams *insert_FormalParams(is_IDList_List *list, char *value);

is_FuncBlock *insert_FuncBlock(is_VarPart_List *vp, is_StatPart *sp);

is_StatPart *insert_StatPart(is_CompStat *ics);

is_CompStat *insert_CompStat(is_StatList_List *isl);

is_StatList_List *insert_StatList(is_Stat *is, is_StatList_List *list);
/*
is_Stat *insert_Stat(CompStat 		Stat2 			WRITELN);

is_Stat2 *insert_Stat2(ID ASSIGN Expr);

is_StatITE *insert_StatITE(IF Expr THEN Stat ELSE Stat);

is_StatIWR *insert_StatIWR(IF Expr THEN Stat 			WHILE Expr DO Stat 			REPEAT StatList UNTIL Expr);

is_StatV *insert_StatV(VAL LBRAC PARAMSTR LBRAC Expr RBRAC COMMA ID RBRAC);

is_StatWR *insert_StatWR(WRITELN WritelnPList);

is_WritelnPList *insert_WritelnPList(LBRAC Expr RBRAC WritelnPList2 			LBRAC STRING RBRAC WritelnPList2);

is_WritelnPList2 *insert_WritelnPList2(COMMA STRING WritelnPList2 			COMMA Expr WritelnPList2);

is_ExprA *insert_ExprAMN(AND Expr 		MINUS Expr 			NOT Expr);
*/


is_Expr *insert_Expr(is_Expr *iex1);
is_Expr *insert_ExprI(char *intrealid, is_ParamList *ipl);
is_Expr *insert_ExprO(is_Expr *iex1, tipos_expr te, is_Expr *iex2);
is_ParamList *insert_ParamList(is_Expr *iex, is_ParamList *lista);
