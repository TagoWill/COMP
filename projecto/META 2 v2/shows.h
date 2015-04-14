#include "structures.h"


void espacamento(int tamanho);
void show_idlist(is_IDList_List *idlist, int tamanho);
void show_vardeclaration(is_VarDeclaration *vd, int tamanho);
void show_statpart(is_StatPart *sp, int tamanho);
void show_funcident(is_FuncIdent *fi, int tamanho);
void show_funcdeclaration(is_FuncDeclaration *fd, int tamanho);
void show_varpart(is_VarPart_List *vp, int tamanho);
void show_progblock(is_ProgBlock *pb, int tamanho);
void show_progheading(is_ProgHeading *ph, int tamanho);
void show_prog(is_Prog *prog);