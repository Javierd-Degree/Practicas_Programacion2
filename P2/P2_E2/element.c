#include <stdio.h>
#include <stdlib.h>
#include "element.h"

typedef struct _Element{
    Node * info;
}Element;

Element * element_ini(){
    Element *e;
    e = (Element*)malloc(sizeof(Element));
    if (e == NULL) return NULL;
    e->info = node_ini();
    return e;
}

void element_destroy(Element *e){
    if (e == NULL) return ;
    node_destroy(e->info);
    free(e);
}

Element * element_setInfo(Element *e , void *v){
    if (e == NULL || v == NULL) return NULL;
    if(e->info == NULL) e->info = node_ini();
    node_setId(e->info, node_getId((Node*)v));
    node_setName(e->info, node_getName((Node*)v));
    return e;
}

void * element_getInfo(Element *e){
    if (e == NULL) return NULL;
    return e->info;
}

Element * element_copy(const Element *e){
    if (e == NULL) return NULL;
    Element *ec;
    ec = element_ini();
    element_setInfo(ec, e->info);
    return ec;
}

Bool element_equals(const Element *e1, const Element *e2){
    if (e1 == NULL || e2 == NULL) return FALSE;
    if (e1->info == NULL || e2->info == NULL) return FALSE;
    
    if (node_equals(e1->info, e2->info)) return TRUE;
    
    return FALSE;  
}
    

int element_print(FILE *f, const Element *e){
    int n;
    if (f == NULL || e == NULL) return -1;
    n = node_print(f, e->info);
    return n;
}