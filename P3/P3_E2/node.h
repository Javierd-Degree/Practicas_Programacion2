#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "types.h"

typedef struct _Node Node;

typedef enum{WHITE = 0, GREY, BLACK}Visited;

Node * node_ini();
void node_destroy(Node * n);

Visited node_getVisited(const Node * n);
int node_getId(const Node * n);
char* node_getName(const Node * n);

Node * node_setVisited(Node * n, const Visited visited);
Node * node_setId(Node * n, const int id);
Node * node_setName(Node * n, const char* name);

Bool node_equals(const Node * n1, const Node * n2);
Node * node_copy(const Node * src);

int node_print(FILE *pf, const Node * n); 

#endif /* NODE_H */
