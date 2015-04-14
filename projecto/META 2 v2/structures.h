#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum{tipo_funcHeading, tipo_funcident} tipos_funcdeclaration;

typedef struct _a14
{
	int apagar;
}is_FuncBlock;

typedef struct _a13
{
	char *id;
}is_FuncIdent;

typedef struct _a12
{
	int apgar;
}is_FuncHeading;

typedef struct _a11
{
	tipos_funcdeclaration tf;
	union{
		struct is_FuncHeading *fh;
		struct is_FuncIdent *fi;
	}data_funcdeclaration;
	is_FuncBlock *fb;

}is_FuncDeclaration;

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
	is_FuncDeclaration *fd;
	struct _a6 *next;
	
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
