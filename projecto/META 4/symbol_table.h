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
	int usado;
	struct _t3 *variaveis;
	struct _t3 *filho;
	struct _t3 *next;
	struct _t3 *pai;
} table;

void changeStatus();
table *encontra_funcao_em_tudo(char *valor);
table *encontra_para_return(char *valor);
table *encontra_funcao_na_tabela(char *valor);
table *encontra_na_tabela_outer(char *valor);
table *encontra_em_tudo(char *valor);
table *encontra_na_tabela(char *valor);
void cria();
table *inserir_funcoes(char *valor, char *type, int usado);
table *inserir_coisas(char *valor, char *type,char *ret);
void imprimirTabela(table* actual);
void imprimeTabelas(table* actual);

#endif
