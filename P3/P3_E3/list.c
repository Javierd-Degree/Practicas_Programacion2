#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

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
    l->destroy_element_function = f1;
    l->copy_element_function = f2;
    l->print_element_function = f3;
    l->cmp_element_function = f4;
    return l;
}

/*Función auxiliar para simplificiar list_free*/
void destroy_nodelist(NodeList *n, List *l){
    if(n == NULL || l == NULL) return;
    if(n->data != NULL) l->destroy_element_function(n->data);
    n->next = NULL;
    free (n);
    return;
}

void list_free(List* l){
    NodeList *nTemp;
    if(l == NULL) return;
    if(list_isEmpty(l)){
        free(l);
        return;
    }
    
    while( NEXT(FIRST(l)) != NULL){
        nTemp = NEXT(FIRST(l));
        destroy_nodelist(FIRST(l), l);
        FIRST(l) = nTemp;
    }
    
    destroy_nodelist(FIRST(l), l);
    free(l);
}

List* list_insertFirst(List* list, const void *elem){
    NodeList *eCopy;
    if( list == NULL || elem == NULL) return NULL;
    eCopy = (NodeList *)malloc(sizeof(NodeList));
    if(eCopy == NULL) return NULL;
    
    eCopy->data = list->copy_element_function(elem);
    if(eCopy->data == NULL){
        free(eCopy);
        return NULL;
    } 
    
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
    NodeList *eCopy, *nAux;
    if( list == NULL || elem == NULL) return NULL;
    eCopy = (NodeList *)malloc(sizeof(NodeList));
    if(eCopy == NULL) return NULL;
    
    eCopy->data = list->copy_element_function(elem);
    if(eCopy->data == NULL){
        free(eCopy);
        return NULL;
    }
    
    NEXT(eCopy) = NULL;

    if(list_isEmpty(list)){
        FIRST(list) = eCopy;
        return list;
    }
    if(NEXT(FIRST(list)) == NULL){
        NEXT(FIRST(list)) = eCopy;
        return list;
    }

    for(nAux = FIRST(list); NEXT(nAux) != NULL; nAux = NEXT(nAux));

    NEXT(nAux) = eCopy;
    return list;
}

/*De menor a mayor*/
List* list_insertInOrder(List* list, const void *elem){
    NodeList *eCopy, *nAux;
    if( list == NULL || elem == NULL) return NULL;
    eCopy = (NodeList *)malloc(sizeof(NodeList));
    if(eCopy == NULL) return NULL;
    
    eCopy->data = list->copy_element_function(elem);
    if(eCopy->data == NULL){
        free(eCopy);
        return NULL;
    } 
    
    if(list_isEmpty(list)){
        FIRST(list) = eCopy;
        NEXT(eCopy) = NULL;
        return list;
    }

    if(NEXT(FIRST(list)) == NULL){
        if(list->cmp_element_function(eCopy->data, FIRST(list)->data) != 1){
            NEXT(FIRST(list)) = NULL;
            NEXT(eCopy) = FIRST(list);
            FIRST(list) = eCopy;
            return list;
        }
        NEXT(FIRST(list)) = eCopy;
        NEXT(eCopy) = NULL;
        return list;
    }
    
    /*Comprobamos si es el menor de todos*/
    if(list->cmp_element_function(eCopy->data, FIRST(list)->data) != 1){
        NEXT(eCopy) = FIRST(list);
        FIRST(list) = eCopy;
        return list;
    }

    for(nAux = FIRST(list); NEXT(nAux) != NULL; nAux = NEXT(nAux)){
        if(list->cmp_element_function(eCopy->data, NEXT(nAux)->data) != 1){
            NEXT(eCopy) = NEXT(nAux);
            NEXT(nAux) = eCopy;
            return list;
        }
    }
    NEXT(nAux) = eCopy;
    NEXT(eCopy) = NULL;
    return list;
}

void * list_extractFirst(List* list){
    NodeList *nAux;
    void *data;
    if(list == NULL || list_isEmpty(list)) return NULL;
    
    nAux = FIRST(list);
    FIRST(list) = NEXT(nAux);
    data = list->copy_element_function(nAux->data);
    destroy_nodelist(nAux, list);
    return data;
}

void * list_extractLast(List* list){
    NodeList *nAux;
    void *data;
    if(list == NULL || list_isEmpty(list)) return NULL;

    if(NEXT(FIRST(list)) == NULL){
        data = list->copy_element_function(FIRST(list)->data);
        destroy_nodelist(FIRST(list), list);
        FIRST(list) = NULL;
        return data;
    }

    for(nAux = FIRST(list); NEXT(NEXT(nAux)) != NULL; nAux = NEXT(nAux));
    
    data = list->copy_element_function(NEXT(nAux)->data);
    destroy_nodelist(NEXT(nAux), list);
    NEXT(nAux) = NULL;
    return data;
}

Bool list_isEmpty(const List* list){
    if(list == NULL) return TRUE;
    if(FIRST(list) == NULL) return TRUE;
    return FALSE;
}

const void* list_get(const List* list, int i){
    int j;
    NodeList *nAux;
    if(list == NULL)return NULL;
    if (i==1) return FIRST(list)->data;
    for(j=0, nAux = FIRST(list);j<i && nAux==NULL;j++, nAux=NEXT(nAux)); /*la primera posición es la 0*/
    if(j == i) return nAux->data;
    return NULL;
}

int list_size(const List* list){
    int i;
    NodeList *nAux;
    if(list == NULL) return -1;
    if(list_isEmpty(list) == TRUE) return 0;
    for(i=0,nAux = FIRST(list); nAux != NULL ;i++, nAux = NEXT(nAux));
    /*como empezamos desde la posición 0 la posición del último que no es NULL es el numero de elementos menos uno*/
    return i;
}

int list_print(FILE *fd, const List* list){
    int size, i, nchar, n;
    NodeList * nAux;
    
    if(list == NULL || fd == NULL) return -1;
    size=list_size(list);
    if(size == 0)return 0;
    for(i=0, nAux = FIRST(list);i<size; i++, nAux = NEXT(nAux)){
        if((n = list->print_element_function(fd, nAux->data) == -1)) return -1;
        fprintf(fd, "\n");
        nchar = nchar +n;
    };
    return nchar;
}
