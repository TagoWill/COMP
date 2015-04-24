#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

Node *newNode();
Node *leaf(nodeType type, char *value);
Node *addNode(nodeType type, Node *child);
Node *add(Node *no1, Node *no2);
char *figureOutAST(nodeType type);
void printNode(Node *no, int depth);
#endif
