#ifndef _STRUCTURES_
#define _STRUCTURES_

/*is_oper  is_PLUS  is_MINUS*/
typedef enum {is_PLUS, is_MINUS} is_oper;

/*is_ expression   is_infix_ expression   is_unary_expression 
			    is_NUMBER*/

typedef enum {d_infix_exp, d_unary_exp, d_number} disc_expression;

typedef struct _a3 {
	disc_expression  disc_d;
	union{
		struct is_infix_expression  *u_infix_exp;
		struct is_unary_expression  *u_unary_exp;
		int number;
	}data_expression;
}is_expression;

/*is_infix_expression   
	(<exp1: is_expression><oper:is_oper><exp2:is_expression>)*/

typedef struct _a4 {
	is_expression  *exp1;
	is_oper oper;
	is_expression  *exp2;
}is_infix_expression;
/*is_unary_expression   (<exp: is_expression>)*/

typedef struct _a5 {
	is_expression  *exp;
}is_unary_expression;

typedef struct _a2 {
	is_expression  *expr;
	struct _a2 *next;
}is_expression_list;

#endif
