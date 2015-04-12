#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

is_Prog *insert_Prog()
{
	is_Prog *ip=(is_Prog*)malloc(sizeof(is_Prog));
	ip->teste = 25;
	ip->next = NULL;
	return ip;
}

