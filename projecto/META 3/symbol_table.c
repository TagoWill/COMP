#include "symbol_table.h"
#include<malloc.h>
#include<string.h>
#include<stdio.h>

extern table* symtab;

/* Funcao que procura um dado valor na tabela Outer Symbol Table */
table *encontra_na_tabela_outer(char *valor){
	table *aux = symtab;
	while(aux->tabletype != is_outer){
		aux = aux->pai;
	}
	for(aux=aux->variaveis;aux!= NULL;aux=aux->next){
		if(strcasecmp(aux->name,valor)==0){
			return aux;
		}
	}
	return NULL;
}

/* Funcao que procura um dado valor nas tabelas Function Symbol Table e Program Symbol Table */
table *encontra_na_tabela(char *valor){
	table *aux, *aux2;
	for(aux=symtab->variaveis;aux!= NULL;aux=aux->next){
		if(strcasecmp(aux->name,valor)==0){
			return aux;
		}
	}
	aux=symtab->pai;
	while(aux!=NULL){
		for(aux2=aux->variaveis;aux2!=NULL;aux2=aux2->next){
			if(strcasecmp(aux2->name,valor)==0){
				return aux;
			}
		}
		aux=aux->pai;
	}
	return NULL;
}

/* Funcao que preenche a tabela estatica Outer Symbol Table - Faz parte da funcao check_program */
void cria(){
	table *aux;
	table *outer = (table*)malloc(sizeof(table));
	outer->tabletype = is_outer;
	outer->pai = NULL;

	table *boo = (table*)malloc(sizeof(table));
	boo->tabletype = is_variavel;
	boo->name = "boolean";
	boo->type = "_type_";
	boo->isconstant=1;
	boo->valreturn = "_boolean_";
	boo->next = NULL;
	boo->pai =NULL;
	boo->filho=NULL;
	boo->variaveis=NULL;
	
	outer->variaveis = boo;

	table *in = (table*)malloc(sizeof(table));
	in->tabletype = is_variavel;
	in->name = "integer";
	in->type = "_type_";
	in->isconstant=1;
	in->valreturn = "_integer_";
	in->next = NULL;
	in->pai =NULL;
	in->filho=NULL;
	in->variaveis=NULL;

	aux = outer->variaveis;
	aux->next = in;

	table *rea = (table*)malloc(sizeof(table));
	rea->tabletype = is_variavel;
	rea->name = "real";
	rea->type = "_type_";
	rea->isconstant=1;
	rea->valreturn ="_real_";
	rea->next = NULL;
	rea->pai =NULL;
	rea->filho=NULL;
	rea->variaveis=NULL;

	aux = aux->next;
	aux->next = rea;

	table *fals = (table*)malloc(sizeof(table));
	fals->tabletype = is_variavel;
	fals->name = "false";
	fals->type = "_boolean_";
	fals->isconstant = 1;
	fals->valreturn = "_false_";
	fals->next = NULL;
	fals->pai =NULL;
	fals->filho=NULL;
	fals->variaveis=NULL;

	aux = aux->next;
	aux->next = fals;

	table *tru = (table*)malloc(sizeof(table));
	tru->tabletype = is_variavel;
	tru->name = "true";
	tru->type = "_boolean_";
	tru->isconstant = 1;
	tru->valreturn = "_true_";
	tru->next = NULL;
	tru->pai =NULL;
	tru->filho=NULL;
	tru->variaveis=NULL;

	aux = aux->next;
	aux->next = tru;

	table *parac = (table*)malloc(sizeof(table));
	parac->tabletype = is_variavel;
	parac->name = "paramcount";
	parac->type = "_function_";
	parac->next = NULL;
	parac->pai =NULL;
	parac->filho=NULL;
	parac->variaveis=NULL;

	aux = aux->next;
	aux->next = parac;

	table *func1 = (table*)malloc(sizeof(table));
	func1->tabletype = is_function;
	func1->name = "paramcount";
	func1->type = "_integer_";
	func1->valreturn = "return";
	func1->next = NULL;
	func1->pai =outer;
	func1->filho=NULL;
	func1->variaveis=NULL;

	outer->filho = func1;

	table *prog = (table*)malloc(sizeof(table));
	prog->tabletype = is_variavel;
	prog->name = "program";
	prog->type = "_program_";
	prog->next = NULL;
	prog->pai =NULL;
	prog->filho=NULL;
	prog->variaveis=NULL;

	aux = aux->next;
	aux->next = prog;

	table *newSymbol = (table*)malloc(sizeof(table));
	newSymbol->tabletype = is_program;
	newSymbol->name = "program";
	newSymbol->type = "_integer_";
	newSymbol->valreturn = "return";
	newSymbol->next = NULL;
	newSymbol->filho=NULL;
	newSymbol->variaveis=NULL;
	newSymbol->pai = outer;
	symtab = newSymbol;

	aux = outer->filho;
	aux->next = newSymbol;

}

/* Funcao que preenche a tabela Function Symbol Table - Faz parte da funcao checkFuncDeclaration */
table *inserir_funcoes(char *valor, char *type){
	table *newSymbol = (table*)malloc(sizeof(table));
	table *aux;
	table *previous;
	if(valor != NULL){
		newSymbol->name = (char*)malloc(sizeof(char));
		strcpy(newSymbol->name, valor);
	}else{
		newSymbol->name = NULL;
	}

	newSymbol->tabletype = is_function;
	
	if(type != NULL){
		newSymbol->type = (char*)malloc(sizeof(char));
		if(strcmp(type, "integer")==0)
		strcpy(newSymbol->type, "_integer_");
	if(strcmp(type, "real")==0)
		strcpy(newSymbol->type, "_real_");
	if(strcmp(type, "boolean")==0)
		strcpy(newSymbol->type, "_boolean_");
	}else{
		newSymbol->type = NULL;
	}
	newSymbol->isconstant=0;
	newSymbol->valreturn = (char*)malloc(sizeof(char));
	strcpy(newSymbol->valreturn, "return");

	newSymbol->variaveis == NULL;
	newSymbol->filho=NULL;
	newSymbol->pai =symtab;
	newSymbol->next=NULL;

	if(symtab->filho != NULL){
		for(aux=symtab->filho;aux != NULL; previous=aux , aux=aux->next){
			if(strcmp(aux->name, valor)==0){
				return NULL;
			}
		}
		previous->next=newSymbol;
	}else{
		symtab->filho=newSymbol;
	}
	return newSymbol;
}

/* Funcao que preenche a tabela Function Symbol Table - Faz parte da funcao checkFuncDeclaration */
table *inserir_coisas(char *valor, char *type,char *ret){
	int i;
	table *newSymbol = (table*)malloc(sizeof(table));
	table *aux;
	table *previous;
	char *lower = valor;
	for(i = 0; lower[i]; i++){
  		lower[i] = tolower(lower[i]);
	}
	if(valor != NULL){
		newSymbol->name = (char*)malloc(sizeof(char));
		strcpy(newSymbol->name, lower);
	}else{
		newSymbol->name=NULL;
	}

	newSymbol->tabletype = is_variavel;
	
	if(type != NULL){
		newSymbol->type = (char*)malloc(sizeof(char));
		strcpy(newSymbol->type, type);
	}else{
		newSymbol->type = NULL;
	}
	newSymbol->isconstant=0;
	if(ret != NULL){
		newSymbol->valreturn = (char*)malloc(sizeof(char));
		strcpy(newSymbol->valreturn, ret);
	}else{
		newSymbol->valreturn = NULL;
	}
	newSymbol->variaveis == NULL;
	newSymbol->filho=NULL;
	newSymbol->pai =NULL;
	newSymbol->next=NULL;

	if(symtab->variaveis != NULL){
		for(aux=symtab->variaveis;aux != NULL; previous=aux , aux=aux->next){
			if(strcmp(aux->name, valor)==0){
				return NULL;
			}
		}
		previous->next=newSymbol;
	}else{
		symtab->variaveis=newSymbol;
	}
	return newSymbol;

}

/* Funcao que imprime as tabelas de simbolos - Faz parte da imprimeTabelas */
void imprimirTabela(table* actual){
	switch(actual->tabletype){
		case is_outer:
			printf("===== Outer Symbol Table =====\n");
			break;
		case is_function:
			printf("\n===== Function Symbol Table =====\n");
			printf("%s\t", actual->name);
			printf("%s\t", actual->type);
			printf("%s\n", actual->valreturn);
			break;
		case is_program:
			printf("\n===== Program Symbol Table =====\n");
			break;
		case is_variavel:
			printf("%s\t", actual->name);
			printf("%s", actual->type );
			if(actual->isconstant == 1)printf("\tconstant");
			if(actual->valreturn != NULL)printf("\t%s", actual->valreturn);
			printf("\n");
			break;

	}
	if(actual->variaveis != NULL)
		imprimirTabela(actual->variaveis);
	if(actual->next != NULL)
		imprimirTabela(actual->next);
	if(actual->filho != NULL)
		imprimirTabela(actual->filho);
}

/* Funcao que manda imprimir as tabelas de simbolos de forma ordenada */
void imprimeTabelas(table* actual)
{
	if(actual->tabletype != is_outer){
		imprimeTabelas(actual->pai);
	}else{
		imprimirTabela(actual);
	}
}

