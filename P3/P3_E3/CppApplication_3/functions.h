#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include <stdio.h>

void destroy_intp_function(void* e);
void * copy_intp_function(const void* e);
int print_intp_function(FILE * f, const void* e);

void destroy_node_function(void* e);
void * copy_node_function(const void* e);
int print_node_function(FILE * f, const void* e);
/*Creo q las funciones para nodelist serian asi:
void destroy_nodelist_function(NodeList *);
void *copy_nodelist_function(const NodeList *);
int printf_nodelist_function(const NodeList *e1, const NodeList *e2);
int compare_nodelist_function(const NodeList *e1, const NodeList *e2);

#endif /* FUNCTIONS_H */

*/