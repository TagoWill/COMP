#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

is_Prog *insert_Prog()
{
	is_Prog *p=(is_Prog*)malloc(sizeof(is_Prog));
	p->teste = 25;
	p->next = NULL;
	return ip;
}

is_ProgHeading *insert_ProgHeading()
{
	is_ProgHeading *ph=(is_ProgHeading*)malloc(sizeof(is_ProgHeading));
	return ph;
}

is_ProgBlock *insert_ProgBlock()
{
	is_ProgBlock *pb=(is_ProgBlock*)malloc(sizeof(is_ProgBlock));
	return pb;
}

is_VarPart *insert_VarPart()
{
	is_VarPart *vp=(is_VarPart*)malloc(sizeof(is_VarPart));
	return vp;
}

is_VarPart2 *insert_VarPart2()
{
	is_VarPart2 *vp2=(is_VarPart2*)malloc(sizeof(is_VarPart2));
	return vp2;
}

is_VarDeclaration *insert_VarDeclaration()
{
	is_VarDeclaration *vd=(is_VarDeclaration*)malloc(sizeof(is_VarDeclaration));
	return vd;
}

is_IDList *insert_IDList()
{
	is_IDList *il=(is_IDList*)malloc(sizeof(is_IDList));
	return il;
}

is_IDList2 *insert_IDList2()
{
	is_IDList2 *il2=(is_IDList2*)malloc(sizeof(is_IDList2));
	return il2;
}

is_FuncPart *insert_FuncPart()
{
	is_FuncPart *fp=(is_FuncPart*)malloc(sizeof(is_FuncPart));
	return fp;
}

is_FuncDeclaration *insert_FuncDeclaration()
{
	is_FuncDeclaration1 *fd=(is_FuncDeclaration1*)malloc(sizeof(is_FuncDeclaration1));
	return fd;
}

is_FuncHeading *insert_FuncHeading()
{
	is_FuncHeading *fh=(is_FuncHeading*)malloc(sizeof(is_FuncHeading));	
	return fh;
}

is_FuncIdent *insert_FuncIdent()
{
	is_FuncIdent *fi=(is_FuncIdent*)malloc(sizeof(is_FuncIdent));
	return fi;
}

is_FormalParamList *insert_FormalParamList()
{
	is_FormalParamList *fpl=(is_FormalParamList*)malloc(sizeof(is_FormalParamList));
	return fp1;
}

is_FormalParams *insert_FormalParams()
{
	is_FormalParams *fps=(is_FormalParams*)malloc(sizeof(is_FormalParams));
	return fps;
}

is_FormalParams2 *insert_FormalParams2()
{
	is_FormalParams2 *fps2=(is_FormalParams2*)malloc(sizeof(is_FormalParams2));
	return fps2;
}

is_FuncBlock *insert_FuncBlock()
{
	is_FuncBlock *fb=(is_FuncBlock*)malloc(sizeof(is_FuncBlock));
	return fb;
}

is_StatPart *insert_StatPart()
{
	is_StatPart *sp=(is_StatPart*)malloc(sizeof(is_StatPart));
	return sp;
}

is_CompStat *insert_CompStat()
{
	is_CompStat *cs=(is_CompStat*)malloc(sizeof(is_CompStat));
	return cs;
}

is_StatList *insert_StatList()
{
	is_StatList *sl=(is_StatList*)malloc(sizeof(is_StatList));	
	return sl;
}

is_StatList2 *insert_StatList2()
{
	is_StatList2 *sl2=(is_StatList2*)malloc(sizeof(is_StatList2));	
	return sl2;
}

is_Stat1 *insert_Stat1()
{
	is_Stat1 *st1=(is_Stat1*)malloc(sizeof(is_Stat1));
	return st1;
}

is_Stat2 *insert_Stat2()
{
	is_Stat2 *st2=(is_Stat2*)malloc(sizeof(is_Stat2));
	return st2;
}

is_StatITE *insert_StatITE()
{
	is_StatITE *stITE=(is_StatITE*)malloc(sizeof(is_StatITE));
	return stITE;
}

is_StatIWR *insert_StatIWR()
{
	is_StatIWR *stIWR=(is_StatIWR*)malloc(sizeof(is_StatIWR));
	return stIWR;
}

is_StatV *insert_StatV()
{
	is_StatV *stV=(is_StatV*)malloc(sizeof(is_StatV));
	return stV;
}

is_StatWR *insert_StatWR()
{
	is_StatWR *stWR=(is_StatWR*)malloc(sizeof(is_StatWR));
	return stWR;
}

is_WritelnPList *insert_WritelnPList()
{
	is_WritelnPList *wl=(is_WritelnPList*)malloc(sizeof(is_WritelnPList));
	return wl;
}

is_WritelnPList2 *insert_WritelnPList2()
{
	is_WritelnPList2 *wl2=(is_WritelnPList2*)malloc(sizeof(is_WritelnPList2));
	return wl2;
}

is_Expr *insert_Expr()
{
	is_Expr *ex=(is_Expr*)malloc(sizeof(is_Expr));	
	return ex;
}

is_ExprO *insert_ExprO()
{
	is_ExprO *exO=(is_ExprO*)malloc(sizeof(is_ExprO));
	return exO;
}

is_ExprAMN *insert_ExprAMN()
{
	is_ExprAMN *exAMN=(is_ExprAMN*)malloc(sizeof(is_ExprAMN));
	return exAMN;	
}

is_ExprI *insert_ExprI()
{
	is_ExprI *exI=(is_ExprI*)malloc(sizeof(is_ExprI));
	return exI;
}

is_ParamList *insert_ParamList()
{
	is_ParamList *ipl=(is_ParamList)malloc(sizeof(is_ParamList));
	return ipl;
}

is_ParamList2 *insert_ParamList2()
{
	is_ParamList2 *pl2=(is_ParamList2)malloc(sizeof(is_ParamList2));
	return pl2;
}
