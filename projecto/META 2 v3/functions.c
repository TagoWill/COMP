#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

is_Prog *insert_Prog(is_ProgHeading *iph, is_ProgBlock *ipb)
{
	is_Prog *p=(is_Prog*)malloc(sizeof(is_Prog));
	p->ph = iph;
	p->pb = ipb;
	return p;
}

is_ProgHeading *insert_ProgHeading(char *valor)
{
	is_ProgHeading *ph=(is_ProgHeading*)malloc(sizeof(is_ProgHeading));
	ph->id = valor;
	return ph;
}

is_ProgBlock *insert_ProgBlock(is_VarPart_List *ivp, is_FuncPart_List *ifpl, is_StatPart *isp)
{
	is_ProgBlock *pb=(is_ProgBlock*)malloc(sizeof(is_ProgBlock));
	pb->vp = ivp;
	pb->fpl = ifpl;
	pb->sp = isp;
	return pb;
}

is_VarPart_List *insert_VarPart(is_VarDeclaration *ivd, is_VarPart_List *list)
{
	is_VarPart_List *vp=(is_VarPart_List*)malloc(sizeof(is_VarPart_List));
	vp->vd = ivd;


	if(list == NULL)
		return vp;

	is_VarPart_List *aux;
	for(aux = list; aux->next != NULL; aux=aux->next);
		aux->next = vp;

	return list;

}

is_VarDeclaration *insert_VarDeclaration(is_IDList_List *iIDlist, char *value)
{
	is_VarDeclaration *vd=(is_VarDeclaration*)malloc(sizeof(is_VarDeclaration));

	vd->idlist = iIDlist; 
	vd->id = value;

	return vd;
}

is_IDList_List *insert_IDList(char *value, is_IDList_List *list)
{
	is_IDList_List *il=(is_IDList_List*)malloc(sizeof(is_IDList_List));
	il->id = value;
	
	if(list == NULL)
		return il;

	is_IDList_List *aux;
	for(aux=list;aux->next != NULL; aux=aux->next);
		aux->next = il;

	return list;
}

is_FuncPart_List *insert_FuncPart(is_FuncDeclaration *ifd, is_FuncPart_List *list)
{
	is_FuncPart_List *fp=(is_FuncPart_List*)malloc(sizeof(is_FuncPart_List));
	fp->fd = ifd;

	if(list == NULL)
		return fp;

	is_FuncPart_List *aux;
	for(aux=list;aux->next != NULL; aux=aux->next);
		aux->next = fp;
	return list;
}

is_FuncDeclaration *insert_FuncDeclarationH(is_FuncHeading *ifh,is_FuncBlock *ifb)
{
	is_FuncDeclaration *fd=(is_FuncDeclaration*)malloc(sizeof(is_FuncDeclaration));
	fd->tf=tipo_funcHeading;
	fd->data_funcdeclaration.fh=(struct is_FuncHeading*) ifh;

	fd->fb = ifb;

	return fd;
}

is_FuncDeclaration *insert_FuncDeclarationI(is_FuncIdent *ifi,is_FuncBlock *ifb)
{
	is_FuncDeclaration *fd=(is_FuncDeclaration*)malloc(sizeof(is_FuncDeclaration));
	fd->tf=tipo_funcident;
	fd->data_funcdeclaration.fi=(struct is_FuncIdent*) ifi;

	fd->fb = ifb;

	return fd;
}

is_FuncHeading *insert_FuncHeading(char *value1, is_FormalParamList * ifpl, char *value2)
{
	is_FuncHeading *fh=(is_FuncHeading*)malloc(sizeof(is_FuncHeading));
	fh->id1 = value1;
	fh->fpl = ifpl;
	fh->id2 = value2;
	return fh;
}

is_FuncIdent *insert_FuncIdent(char *value)
{
	is_FuncIdent *fi=(is_FuncIdent*)malloc(sizeof(is_FuncIdent));
	fi->id = value;
	return fi;
}

is_FormalParamList *insert_FormalParamList(is_FormalParams *ifp,is_FormalParamList *list)
{
	is_FormalParamList *fpl=(is_FormalParamList*)malloc(sizeof(is_FormalParamList));

	fpl->fp = ifp;

	if(list == NULL)
		return fpl;

	is_FormalParamList *aux;
	for(aux=list;aux->next != NULL; aux=aux->next);
		aux->next = fpl;
	
	return list;
}

is_FormalParams *insert_FormalParams(is_IDList_List *list, char *value)
{
	is_FormalParams *fps=(is_FormalParams*)malloc(sizeof(is_FormalParams));
	fps->idlist = list;
	fps->id = value;

	return fps;
}

is_FuncBlock *insert_FuncBlock(is_VarPart_List *vp, is_StatPart *sp)
{
	is_FuncBlock *fb=(is_FuncBlock*)malloc(sizeof(is_FuncBlock));
	fb->vp = vp;
	fb->sp = sp;
	return fb;
}

is_StatPart *insert_StatPart(is_CompStat *ics)
{
	is_StatPart *sp=(is_StatPart*)malloc(sizeof(is_StatPart));
	sp->cs = ics;
	return sp;
}

is_CompStat *insert_CompStat(is_StatList_List *isl)
{
	is_CompStat *cs=(is_CompStat*)malloc(sizeof(is_CompStat));
	cs->sl = isl;
	return cs;
}

is_StatList_List *insert_StatList(is_Stat *is, is_StatList_List *list)
{
	is_StatList_List *sl=(is_StatList_List*)malloc(sizeof(is_StatList_List));
	sl->s = is;

	if(list == NULL)
		return sl;

	is_StatList_List *aux;
	for(aux=list;aux->next != NULL; aux=aux->next);
		aux->next = sl;
	
	return list;
}
/*
is_Stat *insert_Stat1()
{
	is_Stat1 *st1=(is_Stat1*)malloc(sizeof(is_Stat1));
	return st1;
}

is_Stat *insert_Stat2()
{
	is_Stat *st2=(is_Stat*)malloc(sizeof(is_Stat));
	return st2;
}

is_Stat *insert_StatITE()
{
	is_Stat *stITE=(is_Stat*)malloc(sizeof(is_Stat));
	return stITE;
}

is_Stat *insert_StatIWR()
{
	is_Stat *stIWR=(is_Stat*)malloc(sizeof(is_Stat));
	return stIWR;
}

is_Stat *insert_StatV()
{
	is_Stat *stV=(is_Stat*)malloc(sizeof(is_Stat));
	return stV;
}

is_Stat *insert_StatWR()
{
	is_Stat *stWR=(is_Stat*)malloc(sizeof(is_Stat));
	return stWR;
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
*/

is_WritelnPList *insert_WritelnPList(is_Expr *iex, is_WritelnPList *iwl)
{
	is_WritelnPList *wl=(is_WritelnPList*)malloc(sizeof(is_WritelnPList));
	wl->ex = iex;
	if(iwl == NULL)
		return wl;

	is_WritelnPList *aux;
	for(aux=iwl; aux->next != NULL; aux=aux->next);
		aux->next = wl;
	return iwl;
}

is_WritelnPList *insert_WritelnPList2(char *string, is_WritelnPList *iwl)
{
	is_WritelnPList *wl2=(is_WritelnPList*)malloc(sizeof(is_WritelnPList));
	wl2->string = string;

	if(iwl == NULL)
		return wl2;

	is_WritelnPList *aux;
	for(aux=iwl; aux->next != NULL; aux=aux->next);
		aux->next = wl2;
	return iwl;
}

is_Expr *insert_Expr(is_Expr *iex1)
{
	is_Expr *ex=(is_Expr*)malloc(sizeof(is_Expr));	
	ex->ex1 = iex1;
	return ex;
}

is_Expr *insert_ExprO(is_Expr *iex1, tipos_expr te, is_Expr *iex2)
{
	is_Expr *exo=(is_Expr*)malloc(sizeof(is_Expr));	
	exo->ex1 = iex1;
	exo->te = te;
	exo->ex2 = iex2;
	return exo;
}

is_Expr *insert_ExprI(char *intrealid, is_ParamList *ipl)
{
	is_Expr *exi=(is_Expr*)malloc(sizeof(is_Expr));	
	exi->intrealid = intrealid;
	exi->ipl = ipl;
	return exi;
}

is_ParamList *insert_ParamList(is_Expr *iex, is_ParamList *lista)
{
	is_ParamList *ipl=(is_ParamList*)malloc(sizeof(is_ParamList));
	ipl->iex = iex;

	if(lista == NULL)
		return ipl;

	is_ParamList *aux;
	for(aux=lista; aux->next != NULL; aux=aux->next);
		aux->next = ipl;
	
	return lista;
}
