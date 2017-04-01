#include "functions.h"
#include "node.h"

/*
* En este fichero se definen las funciones de destrucción, copia e impresión de elementos a almacenar en
* una pila para distintos tipos de datos
*/

/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila. Ojo! Estas funciones
reciben un puntero a entero, no una estructura con un puntero a entero (como en el ejercicio P2_E1) */
void destroy_intp_function(void* e) {
    free((int*) e);
}

void * copy_intp_function(const void* e) {
    int * dst;
    if (e == NULL)
        return NULL;
    dst = (int*) malloc(sizeof (int));
    /*Copiamos el elemento*/
    *(dst) = *((int*) e);
    return dst;
}

int print_intp_function(FILE * f, const void* e) {
    if (f != NULL && e != NULL)
        return fprintf(f, "[%d]", *((int*) e));
    return -1;
}

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void* e) {
    node_destroy((Node *) e);
}

void * copy_node_function(const void* e) {
    return node_copy((Node *) e);
}

int print_node_function(FILE * f, const void* e) {
    return node_print(f, (Node *) e);
}

int compare_nodelist_function(const void* e1, const void* e2) {
    return node_compare((Node *) e1, (Node *) e2);
}
/*Creo q las funciones para nodelist serian asi :

void destroy_nodelist_function(NodeList *n){
    if(n==NULL) return;
    n->data = NULL;
    n->next = NULL;
    free (n);
    return;
}
void *copy_nodelist_function(const NodeList *){
    
}
int printf_nodelist_function(const NodeList *e1, const NodeList *e2);
int compare_nodelist_function(const NodeList *e1, const NodeList *e2);

 */