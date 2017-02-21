#include <stdio.h>
#include <stdlib.h>
#include "element.h"

typedef struct _Element{
    int * info;
}Element;

Element * element_ini(){
    Element *e;
    e = (Element*)malloc(sizeof(Element));
    if (e == NULL) return NULL;
    e->info = NULL;
    return e;
}

void element_destroy(Element *e){
    if (e == NULL) return ;
    free(e->info);
    free(e);
}

Element * element_setInfo(Element *e , void *v){
    if (e == NULL || v == NULL) return NULL;
    if(e->info == NULL) e->info = (int *)malloc(sizeof(int));
    *(e->info) = *((int*)v);
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
    
    if (*e1->info == *e2->info) return TRUE;
    
    return FALSE;  
}
    

int element_print(FILE *f, const Element *e){
    int n;
    if (f == NULL || e == NULL) return -1;
    n = fprintf(f, "%d", *e->info);
    return n;
}