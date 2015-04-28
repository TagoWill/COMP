#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {is_outer, is_program, is_variavel, is_function} basic_type;


typedef struct _t3
{
	basic_type tabletype;
	char *name;
	char *type;
	int isconstant;
	char *valreturn;
	struct _t3 *variaveis;
	struct _t3 *filho;
	struct _t3 *next;
	struct _t3 *pai;
} table;


void cria();
table *inserir_coisas(char *valor, char *ret);
void imprimirTabela(table* actual);
void imprimeTabelas(table* actual);
/*table_element *insert_el(char *str, basic_type t);
void show_table();
table_element *search_el(char *str);*/

#endif
