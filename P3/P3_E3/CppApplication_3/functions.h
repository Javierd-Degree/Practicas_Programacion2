#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

void destroy_intp_function(void* e);
void * copy_intp_function(const void* e);
int print_intp_function(FILE * f, const void* e);

void destroy_node_function(void* e);
void * copy_node_function(const void* e);
int print_node_function(FILE * f, const void* e);
int compare_node_function(const void* e1, const void* e2);

#endif /* FUNCTIONS_H */
