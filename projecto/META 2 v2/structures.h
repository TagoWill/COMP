#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum{tipo_funcHeading, tipo_funcident} tipos_funcdeclaration;

typedef enum{tipo_comp, tipo_ifthenelse, tipo_ifthen, tipo_while, tipo_repeat, tipo_val, tipo_stat2, tipo_writelnlist, tipo_writeln, tipo_assign, tipo_statlist} tipos_stat;

typedef struct _a10
{
	char *id;
	struct _a10 *next;
}is_IDList_List;

typedef struct _a16
{
	is_IDList_List *idlist;
	char *id;
}is_FormalParams;

typedef struct _a15
{
	is_FormalParams *fp;
	struct _a15 *next;
}is_FormalParamList;

typedef struct _a13
{
	char *id;
}is_FuncIdent;

typedef struct _a12
{
	char *id1, *id2;
	is_FormalParamList *fpl;
}is_FuncHeading;

typedef struct _a9
{
	is_IDList_List *idlist; 
	char *id;
}is_VarDeclaration;

typedef struct _a20
{
	/* data */
}is_Expr;

typedef struct _a21
{
	/* data */
}is_WritelnPList;

typedef struct _a19
{
	tipos_stat queraioeisto;

	struct _a19 *cs;
	is_Expr *expr;
	struct _a19 *stat1;
	struct _a19 *stat2;
	struct _a19 *statlist;
	char *id;
	is_WritelnPList *writeln;

	struct _a19 *next;
	
}is_Stat;

typedef struct _a7
{
	is_Stat *cs;
}is_StatPart;

typedef struct _a5
{
	is_VarDeclaration* vd;
	struct _a5 *next;

}is_VarPart_List;

typedef struct _a14
{
	is_VarPart_List *vp;
	is_StatPart *sp;
}is_FuncBlock;

typedef struct _a11
{
	tipos_funcdeclaration tf;
	union{
		struct is_FuncHeading *fh;
		struct is_FuncIdent *fi;
	}data_funcdeclaration;
	is_FuncBlock *fb;

}is_FuncDeclaration;

typedef struct _a6
{
	is_FuncDeclaration *fd;
	struct _a6 *next;
	
}is_FuncPart_List;

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
