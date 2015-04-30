#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern int lineaux;
extern int colaux;

/* Funcao que cria um novo no - Necessario caso seja um no a imprimir */
is_Nos *inserir_no(tipos_nos tipo, is_Nos *filho)
{
	is_Nos* novono = (is_Nos*)malloc(sizeof(is_Nos));
	novono->queraioeisto = tipo;
	novono->valor = NULL;
	novono->nofilho = filho;
	novono->nonext = NULL;
	novono->lina = lineaux;
	novono->cola = colaux;

	return novono;
}

/* Funcao que cria um no e adiciona-lhe um valor e um tipo */
is_Nos *inserir_valor(tipos_nos tipo, char *valor)
{
	is_Nos *novono = (is_Nos*)malloc(sizeof(is_Nos));
	novono->queraioeisto = tipo;
	novono->valor = valor;
	novono->nofilho = NULL;
	novono->nonext = NULL;
	novono->lina = lineaux;
	novono->cola = colaux;

	return novono;
}

/* Funcao que adiciona um filho a uma lista de nos filhos */
is_Nos *inserir_irmao(is_Nos *lista1, is_Nos *lista2)
{
	is_Nos *aux = lista1;
	if(lista1==NULL){
		return lista2;
	}

	while(aux->nonext != NULL){
		aux=aux->nonext;
	}

	aux->nonext = lista2;
	return lista1;
}
