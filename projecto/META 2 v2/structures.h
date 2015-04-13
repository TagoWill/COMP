#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef struct _a10
{
	char *id;
	struct _a10 *next;
}is_IDList_List;

typedef struct _a9
{
	is_IDList_List *idlist; 
	char *id;
}is_VarDeclaration;


typedef struct _a7
{
	int apagar;
	/* data */
}is_StatPart;

typedef struct _a6
{
	int apaggar;
	struct _a6 *next;
	/* data */
}is_FuncPart_List;

typedef struct _a5
{
	is_VarDeclaration* vd;
	struct _a5 *next;

}is_VarPart_List;

typedef struct _a4
{
	is_VarPart_List *vp;
	is_FuncPart_List *fpl;
	is_StatPart	*sp;
}is_ProgBlock;

typedef struct _a3 {
	char *id;
}is_ProgHeading;


typedef struct _a2 {
	is_ProgHeading *ph;
	is_ProgBlock *pb;
}is_Prog;

#endif
