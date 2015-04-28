#include "symbol_table.h"
#include<malloc.h>
#include<string.h>
#include<stdio.h>

extern table* symtab;

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

table *inserir_coisas(char *valor, char *ret){
	table *newSymbol = (table*)malloc(sizeof(table));
	table *aux;
	table *previous;
	newSymbol->name = (char*)malloc(sizeof(char));
	newSymbol->tabletype = is_variavel;
	strcpy(newSymbol->name, valor);
	newSymbol->type =NULL;
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

	if(symtab != NULL){
		for(aux=symtab;aux != NULL; previous=aux , aux=aux->next){
			if(strcmp(aux->name, valor)==0){
				return NULL;
			}
		}
		previous->next=newSymbol;
	}else{
		symtab=newSymbol;
	}
	return newSymbol;

}

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
			printf("%s\t", actual->type );
			if(actual->isconstant == 1)printf("constant");
			if(actual->valreturn != NULL)printf("\t%s", actual->valreturn);
			printf("\n");
			break;
		default:
			printf("O daniel e coco\n");

	}
	if(actual->variaveis != NULL)
		imprimirTabela(actual->variaveis);
	if(actual->next != NULL)
		imprimirTabela(actual->next);
	if(actual->filho != NULL)
		imprimirTabela(actual->filho);

}

void imprimeTabelas(table* actual){
	
	if(actual->tabletype != is_outer){
		imprimeTabelas(actual->pai);
	}else{
		imprimirTabela(actual);
	}

	
}

//Insere um novo identificador na cauda de uma lista ligada de simbolo
/*table *insert_el(char *str, basic_type t)
{
	table *newSymbol=(table*) malloc(sizeof(table));
	table *aux;
	table* previous;

	strcpy(newSymbol->name, str);
	newSymbol->type=t;
	newSymbol->next=NULL;	

	if(symtab)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=symtab; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->name, str)==0)
				return NULL;
		
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		symtab=newSymbol;		
	
	return newSymbol; 
}

void show_table()
{
table_element *aux;
printf("\n");
for(aux=symtab; aux; aux=aux->next)
	printf("symbol %s, type %d\n", aux->name, aux->type);
}

//Procura um identificador, devolve 0 caso nao exista
table_element *search_el(char *str)
{
table_element *aux;

for(aux=symtab; aux; aux=aux->next)
	if(strcmp(aux->name, str)==0)
		return aux;

return NULL;
}





*/