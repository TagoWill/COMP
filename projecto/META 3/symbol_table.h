#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {integer, character, doub} basic_type;

typedef struct _t1{
	basic_type type;
	char name[32];
	struct _t1 *pai;
	struct _t1 *next;
} table_elements;

table_element *insert_el(char *str, basic_type t);
void show_table();
table_element *search_el(char *str);

#endif
