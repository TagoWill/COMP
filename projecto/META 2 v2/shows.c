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

void show_writelnplist(is_WritelnPList *iwl, int tamanho)
{
	if(iwl != NULL){
		show_writelnplist(iwl->next, tamanho);
		if(iwl->ex != NULL){
			show_expr(iwl->ex, tamanho);
		}
		if(iwl->string != NULL){
			printf("String (%s)\n", iwl->string);
		}
	}
}

void show_expr(is_Expr *iex, int tamanho)
{
	if(iex != NULL){
		if(iex->te == is_EXO){
			show_expr(iex->ex1, tamanho);
		}
		if(iex->te == is_PLUS || iex->te == is_MINUS || iex->te == is_AND || iex->te == is_OR ||iex->te == is_MULT ||
			iex->te == is_DIV ||iex->te == is_GREATER ||iex->te == is_LESS ||iex->te == is_GEQUAL ||iex->te == is_EQUALS ||
			iex->te == is_DIFFERENT || iex->te == is_NOT || iex->te == is_SUB){
			switch(iex->te){
				case is_PLUS:
					espacamento(tamanho);
					printf("Plus\n");
					break;
				case is_MINUS:
					espacamento(tamanho);
					printf("Minus\n");
					break;
				case is_AND:
					espacamento(tamanho);
					printf("And\n");
					break;
				case is_OR:
					espacamento(tamanho);
					printf("Or\n");
					break;
				case is_MULT:
					espacamento(tamanho);
					printf("Mul\n");
					break;
				case is_DIV:
					espacamento(tamanho);
					printf("Div\n");
					break;
				case is_GREATER:
					espacamento(tamanho);
					printf("Gt\n");
					break;
				case is_LESS:
					espacamento(tamanho);
					printf("Lt\n");
					break;
				case is_GEQUAL:
					espacamento(tamanho);
					printf("Geq\n");
					break;
				case is_EQUALS:
					espacamento(tamanho);
					printf("Eq\n");
					break;
				case is_DIFFERENT:
					espacamento(tamanho);
					printf("Neq\n");
					break;
				case is_NOT:
					espacamento(tamanho);
					printf("Not\n");
					break;
				case is_SUB:
					espacamento(tamanho);
					printf("Sub\n");
					break;
			}
			show_expr(iex->ex1, tamanho+1);
			show_expr(iex->ex2, tamanho+1);
		}
		if(iex->te == is_ID){
			espacamento(tamanho);
			printf("Id(%s)\n", iex->intrealid);
			show_paramlist(iex->ipl, tamanho);
		}
		if(iex->te == is_INTLIT){
			espacamento(tamanho);
			printf("IntLit(%s)\n", iex->intrealid);
		}
		if(iex->te == is_REALLIT){
			espacamento(tamanho);
			printf("RealLit(%s)\n", iex->intrealid);
		}
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

void show_statcomplicado(is_Stat *list, int tamanho){
	if(list != NULL){
		if(list->queraioeisto == tipo_statlist){
			show_statcomplicado(list->next,tamanho);
			if(list->statlist != NULL){
				show_statcomplicado(list->statlist, tamanho);
			}
		}
		if(list->queraioeisto == tipo_comp){
			espacamento(tamanho);
			printf("StatList\n");
			show_statcomplicado(list->cs,tamanho+1);
		}
		if(list->queraioeisto == tipo_ifthenelse){
			espacamento(tamanho);
			printf("IfElse\n");
			show_expr(list->expr, tamanho+1);
			show_statcomplicado(list->stat1,tamanho+1);
			show_statcomplicado(list->stat2,tamanho+1);
		}
		if(list->queraioeisto == tipo_ifthen){
			espacamento(tamanho);
			printf("IfElse\n");
			show_expr(list->expr, tamanho+1);
			show_statcomplicado(list->stat1,tamanho+1);
		}
		if(list->queraioeisto == tipo_while){
			espacamento(tamanho);
			printf("While\n");
			show_expr(list->expr, tamanho+1);
			show_statcomplicado(list->stat1,tamanho+1);
		}
		if(list->queraioeisto == tipo_repeat){
			espacamento(tamanho);
			printf("Repeat\n");
			show_statcomplicado(list->statlist,tamanho+1);
			show_expr(list->expr, tamanho+1);
		}
		if(list->queraioeisto == tipo_val){
			espacamento(tamanho);
			printf("ValParam\n");
			show_expr(list->expr, tamanho+1);
			espacamento(tamanho+1);
			printf("Id(%s)\n", list->id);
		}
		if(list->queraioeisto == tipo_writelnlist){
			espacamento(tamanho);
			printf("WriteLn\n");
			show_writelnplist(list->writeln ,tamanho+1);
		}
		if(list->queraioeisto ==tipo_assign){
			espacamento(tamanho);
			printf("Assign\n");
			espacamento(tamanho+1);
			printf("Id(%s)\n", list->id);
			show_expr(list->expr, tamanho+1);
		}
	}
}

void show_statlist(is_Stat *sl, int tamanho){
	if(sl != NULL){
		show_statlist(sl->next, tamanho);
		if(sl->statlist != NULL){
			show_statcomplicado(sl->statlist, tamanho);
		}
	}
}

void show_statpart(is_StatPart *sp, int tamanho){
	if(sp !=  NULL){
		is_Stat *aux = sp->cs->statlist;
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
		show_statpart(fb->sp, tamanho);
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
	printf("StatList\n");
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