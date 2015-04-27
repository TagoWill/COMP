#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {integer, character, doub} basic_type;

typedef struct _t2
{
	/* data */
} outer_table;

typedef struct _t4{

} paramcount_table;

typedef struct _t3
{
	basic_type type;
	char name[32];
	struct _t3 *variaveis;
	struct _t3 *filho;
	struct _t3 *next;
	struct _t1 *outer;
} program_table;


table_element *insert_el(char *str, basic_type t);
void show_table();
table_element *search_el(char *str);

#endif
