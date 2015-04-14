#include "structures.h"


void espacamento(int tamanho);
void show_idlist(is_IDList_List *idlist, int tamanho);
void show_vardeclaration(is_VarDeclaration *vd, int tamanho);
void show_statlist(is_Stat *sl, int tamanho);
void show_statpart(is_StatPart *sp, int tamanho);
void show_funcident(is_FuncIdent *fi, int tamanho);
void show_formalparamlist(is_FormalParamList *fpl, int tamanho);
void show_funcheading(is_FuncHeading *fh, int tamanho);
void show_funcdeclaration(is_FuncDeclaration *fd, int tamanho);
void show_varpart(is_VarPart_List *vp, int tamanho);
void show_funcblock(is_FuncBlock *fb, int tamanho);
void show_progblock(is_ProgBlock *pb, int tamanho);
void show_progheading(is_ProgHeading *ph, int tamanho);
void show_prog(is_Prog *prog);