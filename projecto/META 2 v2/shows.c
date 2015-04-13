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

void show_statpart(is_StatPart *sp, int tamanho){

}

void show_funcpart(is_FuncPart_List *fpl, int tamanho){

}

void show_varpart(is_VarPart_List *vp, int tamanho){

	if(vp != NULL){
		show_varpart(vp->next, tamanho);
		show_vardeclaration(vp->vd, tamanho+1);
		
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