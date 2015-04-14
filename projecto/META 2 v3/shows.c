#include "shows.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void espacamento(int tamanho){
	int i;
	for(i=0;i<tamanho;i++){
		printf("  ");
	}
}

void show_expr(is_Expr *iex, int tamanho)
{
	if(iex != NULL){
		espacamento(tamanho-1);
		printf("Expression\n");
		show_expr(iex->ex1, tamanho);
		show_expr(iex->ex2, tamanho);
	}
}

void show_paramlist(is_ParamList *ipl, int tamanho){
	if(ipl != NULL){
		espacamento(tamanho-1);
		printf("ParamList\n");
		show_paramlist(ipl->next, tamanho);
		if(ipl->iex != NULL){
			show_expr(ipl->iex, tamanho);
		}
	}
}

void show_idlist(is_IDList_List *idlist, int tamanho){

	if(idlist != NULL){
		show_idlist(idlist->next, tamanho);
		if(idlist->id != NULL){
			espacamento(tamanho);
			printf("Id(%s)\n", idlist->id);
		}
	}
}

void show_vardeclaration(is_VarDeclaration *vd, int tamanho){

	if(vd != NULL){
		espacamento(tamanho-1);
		printf("VarDecl\n");
		show_idlist(vd->idlist, tamanho);
		espacamento(tamanho);
		printf("Id(%s)\n", vd->id);
	}
}

void show_statlist(is_StatList_List *sl, int tamanho){
	if(sl != NULL){
		show_statlist(sl->next, tamanho);
		if(sl->s != NULL){
			//showsomething
		}
	}
}

void show_statpart(is_StatPart *sp, int tamanho){
	if(sp !=  NULL){
		is_StatList_List *aux = sp->cs->sl;
		show_statlist(aux, tamanho);
	}
}

void show_funcident(is_FuncIdent *fi, int tamanho){
	if(fi != NULL){
		espacamento(tamanho);
		char *value = fi->id;
		printf("Id(%s)\n", value);
	}
}

void show_formalparamlist(is_FormalParamList *fpl, int tamanho){
	if(fpl != NULL){
		show_formalparamlist(fpl->next, tamanho);
		if(fpl->fp != NULL){
			is_FormalParams *aux;
			aux = fpl->fp;
			show_idlist(aux->idlist, tamanho);
			espacamento(tamanho);
			printf("Id(%s)\n", aux->id);
		}
	}
}

void show_funcheading(is_FuncHeading *fh, int tamanho){
	if(fh != NULL){
		espacamento(tamanho);
		printf("Id(%s)\n", fh->id1);
		espacamento(tamanho);
		printf("FuncParams\n");
		show_formalparamlist(fh->fpl, tamanho+1);
		espacamento(tamanho);
		printf("Id(%s)\n", fh->id2);
	}
}

void show_funcpart(is_FuncPart_List *fpl, int tamanho){
	if(fpl != NULL){
		show_funcpart(fpl->next, tamanho);
		show_funcdeclaration(fpl->fd, tamanho+1);
	}
}

void show_varpart(is_VarPart_List *vp, int tamanho){

	if(vp != NULL){
		show_varpart(vp->next, tamanho);
		show_vardeclaration(vp->vd, tamanho+1);
	}
}

void show_funcblock(is_FuncBlock *fb, int tamanho){

	if(fb != NULL){
		espacamento(tamanho-1);
		printf("FuncBlock\n");
		show_varpart(fb->vp, tamanho);
	}
	/*NAO ACABADO*/
}

void show_funcdeclaration(is_FuncDeclaration *fd, int tamanho){
	if(fd != NULL){
		espacamento(tamanho-1);
		printf("FuncDecl\n");
		if(fd->tf == tipo_funcident){
			show_funcident((is_FuncIdent*)fd->data_funcdeclaration.fi, tamanho);
		}else{
			show_funcheading((is_FuncHeading*)fd->data_funcdeclaration.fh, tamanho);
		}
		show_funcblock(fd->fb, tamanho);
	}
}

void show_progblock(is_ProgBlock *pb, int tamanho){
	espacamento(tamanho);
	printf("VarPart\n");
	show_varpart(pb->vp, tamanho+1);
	espacamento(tamanho);
	printf("FuncPart\n");
	show_funcpart(pb->fpl, tamanho+1);
	espacamento(tamanho);
	printf("StatPart\n");
	show_statpart(pb->sp, tamanho+1);
}

void show_progheading(is_ProgHeading *ph, int tamanho){
	espacamento(tamanho);
	char *value = ph->id;
	printf("Id(%s)\n", value);
}

void show_prog(is_Prog *prog){

	printf("Program\n");
	show_progheading(prog->ph, 1);
	show_progblock(prog->pb, 1);
}