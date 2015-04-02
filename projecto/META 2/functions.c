#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

is_Prog *insert_Prog()
{
	is_Prog *ip=(is_Prog*)malloc(sizeof(is_Prog));
	return ip;
}

is_ProgHeading *insert_ProgHeading()
{
	is_ProgHeading *iph=(is_ProgHeading*)malloc(sizeof(is_ProgHeading));
	return iph;
}

is_ProgBlock *insert_ProgBlock()
{
	is_ProgBlock *ipb=(is_ProgBlock*)malloc(sizeof(is_ProgBlock));
	return ipb;
}

is_VarPart *insert_VarPart()
{
	is_VarPart *ivp=(is_VarPart*)malloc(sizeof(is_VarPart));
	return ivp;
}

is_VarDeclaration *insert_VarDeclaration()
{
	is_VarDeclaration *ivd=(is_VarDeclaration*)malloc(sizeof(is_VarDeclaration));
	return ivd;
}

is_IDList *insert_IDList()
{
	is_IDList *iie=(is_IDList*)malloc(sizeof(is_IDList));
	return iie;
}

is_FuncPart *insert_FuncPart()
{
	is_FuncPart *ifp=(is_FuncPart*)malloc(sizeof(is_FuncPart));
	return ifp;
}

is_FuncDeclaration1 *insert_FuncDeclaration1()
{
	is_FuncDeclaration1 *ifd1=(is_FuncDeclaration1*)malloc(sizeof(is_FuncDeclaration1));
	return ifd1;
}

is_FuncDeclaration2 *insert_FuncDeclaration2()
{
	is_FuncDeclaration2 *ifd2=(is_FuncDeclaration2*)malloc(sizeof(is_FuncDeclaration2));
	return ifd2;
}

is_FuncDeclaration3 *insert_FuncDeclaration3()
{
	is_FuncDeclaration3 *ifd3=(is_FuncDeclaration3*)malloc(sizeof(is_FuncDeclaration3));
	return ifd3;
}

is_FuncHeading *insert_FuncHeading()
{
	is_FuncHeading *ifh=(is_FuncHeading*)malloc(sizeof(is_FuncHeading));	
	return ifh;
}

is_FuncIdent *insert_FuncIdent()
{
	is_FuncIdent *ifi=(is_FuncIdent*)malloc(sizeof(is_FuncIdent));
	return ifi;
}

is_FormalParamList *insert_FormalParamList()
{
	is_FormalParamList *ifpl=(is_FormalParamList*)malloc(sizeof(is_FormalParamList));
	return ifp1;
}

is_FormalParams *insert_FormalParams()
{
	is_FormalParams *ifps=(is_FormalParams*)malloc(sizeof(is_FormalParams));
	return ifps;
}

is_FuncBlock *insert_FuncBlock()
{
	is_FuncBlock *ifb=(is_FuncBlock*)malloc(sizeof(is_FuncBlock));
	return ifb;
}

is_StatPart *insert_StatPart()
{
	is_StatPart *isp=(is_StatPart*)malloc(sizeof(is_StatPart));
	return isp;
}

is_CompStat *insert_CompStat()
{
	is_CompStat *ics=(is_CompStat*)malloc(sizeof(is_CompStat));
	return ics;
}

is_StatList *insert_StatList()
{
	is_StatList *isl=(is_StatList*)malloc(sizeof(is_StatList));	
	return isl;
}

is_Stat1 *insert_Stat1()
{
	is_Stat1 *is1=(is_Stat1*)malloc(sizeof(is_Stat1));
	return is1;
}

is_Stat2 *insert_Stat2()
{
	is_Stat2 *is2=(is_Stat2*)malloc(sizeof(is_Stat2));
	return is2;
}

is_Stat3 *insert_Stat3()
{
	is_Stat3 *is3=(is_Stat3*)malloc(sizeof(is_Stat3));
	return is3;
}

is_Stat4 *insert_Stat4()
{
	is_Stat4 *is4=(is_Stat4*)malloc(sizeof(is_Stat4));
	return is4;
}

is_Stat5 *insert_Stat5()
{
	is_Stat5 *is5=(is_Stat5*)malloc(sizeof(is_Stat5));
	return is5;
}

is_Stat6 *insert_Stat6()
{
	is_Stat6 *is6=(is_Stat6*)malloc(sizeof(is_Stat6));
	return is6;
}

is_Stat7 *insert_Stat7()
{
	is_Stat7 *is7=(is_Stat7*)malloc(sizeof(is_Stat7));
	return is7;
}

is_WritelnPList *insert_WritelnPList()
{
	is_WritelnPList *iwl=(is_WritelnPList*)malloc(sizeof(is_WritelnPList));
	return iwl;
}

is_Expr1 *insert_Expr1()
{
	is_Expr1 *iex1=(is_Expr1*)malloc(sizeof(is_Expr1));	
	return iex1;
}

is_Expr2 *insert_Expr2()
{
	is_Expr2 *iex2=(is_Expr2*)malloc(sizeof(is_Expr2));
	return iex2;
}

is_Expr3 *insert_Expr3()
{
	is_Expr3 *iex3=(is_Expr3*)malloc(sizeof(is_Expr3));
	return iex3;	
}

is_Expr4 *insert_Expr4()
{
	is_Expr4 *iex4=(is_Expr4*)malloc(sizeof(is_Expr4));
	return iex4;
}

is_Expr5 *insert_Expr5()
{
	is_Expr5 *iex5=(is_Expr5*)malloc(sizeof(is_Expr5));
	return iex5;
}

is_ParamList *insert_ParamList()
{
	is_ParamList *ipl=(is_ParamList)malloc(sizeof(is_ParamList));
	return ipl;
}


