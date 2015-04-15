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

is_StatPart *insert_StatPart(is_Stat *ics);

is_Stat *insert_CompStat(is_Stat *isl);

is_Stat *insert_StatList(is_Stat *is, is_Stat *list);

is_Stat *insert_Stat1(is_Stat *ics);

is_Stat *insert_Stat2(char *value, is_Expr *iexpr);

is_Stat *insert_StatITE(is_Expr *iexpr, is_Stat *istat1, is_Stat *istat2);

is_Stat *insert_StatIT(is_Expr *iexpr, is_Stat *istat1);

is_Stat *insert_StatIWR(is_Expr *iexpr, is_Stat *istat1);

is_Stat *insert_StatIRU(is_Stat *list, is_Expr *iexpr);

is_Stat *insert_StatV(is_Expr *iexpr, char *value);

is_Stat *insert_WPL(is_WritelnPList *iwlp);

is_WritelnPList *insert_WritelnPList(is_Expr *iex, is_WritelnPList *iwl);
is_WritelnPList *insert_WritelnPList2(char *string, is_WritelnPList *iwl);

is_Expr *insert_Expr(tipos_expr te,is_Expr *iex1);
is_Expr *insert_ExprI(tipos_expr te, char *intrealid, is_ParamList *ipl);
is_Expr *insert_ExprO(is_Expr *iex1, tipos_expr te, is_Expr *iex2);
is_ParamList *insert_ParamList(is_Expr *iex, is_ParamList *lista);