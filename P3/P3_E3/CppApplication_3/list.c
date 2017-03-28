#include "list.h"
#include <stdlib.h>
#include <stdio.h>

#define NEXT(N) (N)->next
#define FIRST(N) (N)->node

typedef struct _NodeList {
    void* data;
    struct _NodeList *next;
} NodeList;

struct _List {
    NodeList *node;
    destroy_elementlist_function_type destroy_element_function;
    copy_elementlist_function_type copy_element_function;
    print_elementlist_function_type print_element_function;
    cmp_elementlist_function_type cmp_element_function;
};

List *list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2,
print_elementlist_function_type f3, cmp_elementlist_function_type f4){
    List *l;
    if(f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL) return NULL;
    l = (List*)malloc(sizeof(List));
    if(l == NULL) return NULL;
    l->node = NULL;
    l->copy_element_function = f2;
    l->cmp_element_function = f4;
    l->destroy_element_function = f1;
    l->print_element_function = f3;
    return l;
}

void list_free(List* l){
    NodeList *nTemp;
    if(l == NULL) return;
    if(list_isEmpty(l)){
        free(l);
        return;
    }
    
    while( NEXT(NEXT(FIRST(l))) != NULL){
        nTemp = NEXT(NEXT(FIRST(l)));
        l->destroy_element_function(NEXT(FIRST(l)));
        NEXT(FIRST(l)) = nTemp;
    }
    
    l->destroy_element_function(NEXT(FIRST(l)));
    l->destroy_element_function(FIRST(l));
    free(l);
}

List* list_insertFirst(List* list, const void *elem){
    void *eCopy;
    if( list == NULL || elem == NULL) return NULL;
    eCopy = list->copy_element_function(elem);
    if(eCopy == NULL) return NULL;
    if(list_isEmpty(list)){
        FIRST(list) = eCopy;
        NEXT(eCopy) = NULL;
        return list;
    }
    NEXT(eCopy) = FIRST(list);
    FIRST(list) = eCopy;
    return list;
}

List* list_insertLast(List* list, const void *elem){
    void *eCopy;
    NodeList *nAux;
    if( list == NULL || elem == NULL) return NULL;
    eCopy = list->copy_element_function(elem);

    if(list_isEmpty(list)){
        FIRST(list) = eCopy;
        NEXT(eCopy) = NULL;
        return list;
    }
    
    for(nAux = FIRST(list); NEXT(nAux) != NULL; nAux = NEXT(nAux));
    NEXT(nAux) = eCopy;
    return list;
}

/*De menor a mayor*/
List* list_insertInOrder(List *list, const void *pElem){
    void *eCopy;
    NodeList *nAux;
    if( list == NULL || pElem == NULL) return NULL;
    eCopy = list->copy_element_function(pElem);

    if(list_isEmpty(list)){
        FIRST(list) = eCopy;
        NEXT(eCopy) = NULL;
        return list;
    }
    
    if(NEXT(FIRST(list)) == NULL){
        if(list->cmp_element_function(FIRST(list), eCopy) == 1){
            NEXT(eCopy) = FIRST(list);
            FIRST(list) = eCopy;
            return list;
        }
        NEXT(FIRST(list)) = eCopy;
        return list;
    }
    
    for(nAux = FIRST(list); NEXT(nAux) != NULL; nAux = NEXT(nAux)){
        /*Si en el que estamos tiene mas prioridad*/
        if(list->cmp_element_function(NEXT(nAux), eCopy) == 1){   
            NEXT(eCopy) = NEXT(nAux);
            NEXT(nAux) = eCopy;
        }
    }
    NEXT(nAux) = eCopy;
    return list;
}

void * list_extractFirst(List* list){
    NodeList *nAux;
    if(list == NULL || list_isEmpty(list)) return;
    nAux = FIRST(list);
    FIRST(list) = NEXT(nAux);
    return nAux;
}

void * list_extractLast(List* list){
    NodeList *nAux;
    if(list == NULL || list_isEmpty(list)) return;
    for(nAux = FIRST(list); NEXT(NEXT(nAux)) != NULL; nAux = NEXT(nAux));
    list->destroy_element_function(NEXT(nAux));
    NEXT(nAux) = NULL;
}

Bool list_isEmpty(const List* l){
    if(l == NULL) return TRUE;
    if(FIRST(l) == NULL) return TRUE;
    return FALSE;
}

