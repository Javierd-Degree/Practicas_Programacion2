#include "types.h"
#include "queue.h"
#define MAXQUEUE 200

struct _Queue {
    void** head;
    void** end;
    void* item[MAXQUEUE];
    destroy_elementqueue_function_type destroy_element_function;
    copy_elementqueue_function_type copy_element_function;
    print_elementqueue_function_type print_element_function;
};

Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2,
print_elementqueue_function_type f3){
    Queue *q;
    int i;
    if (f1 == NULL || f2==NULL || f3==NULL) return NULL;
    q = (Queue *)malloc(sizeof(Queue));
    if(q==NULL) return NULL;
    q->copy_element_function = f2;
    q->destroy_element_function = f1;
    q->print_element_function = f3;
    q->end = q->item;
    q->head= q->item;
    for(i=0; i<MAXQUEUE;i++){
        q->item[i] = NULL;
    }
    return q;
}

void queue_destroy(Queue *q){
    if(q!= NULL){
        while (q->head != q->end){
            q->destroy_element_function (*(q->head));
            if(q->head != &(q->item[MAXQUEUE-1])){
                q->head ++;
            }else {
                q->head= q->item;
            }
        }
    }
    free(q);
}

Bool queue_isEmpty(const Queue *q){
    if(q==NULL) return TRUE;
    if(q->head == q->end) return TRUE;
    return FALSE;
}

Bool queue_isFull(const Queue* q){
    void **aux;
    if(q==NULL) return TRUE;
    if(q->end == &(q->item[MAXQUEUE -1])){
        aux = q->item;
    }else{
        aux = q->end +1;
    }
    if(aux == q->head) return TRUE;
    return FALSE;
}

Queue* queue_insert(Queue *q, const void* pElem){
    void *aux;
    if(q==NULL || pElem == NULL || queue_isFull(q)== TRUE) return NULL;
    aux = q->copy_element_function(pElem);
    if(aux == NULL) return NULL;
    *(q->end) = aux;
    if(q->end == &(q->item[MAXQUEUE -1])){
        q->end = q->item;
    }else{
        q->end ++;
    }
    return q;
}

void * queue_extract(Queue *q){
    void *aux;
    if(q==NULL || queue_isEmpty(q) ==TRUE) return NULL;
    aux = *(q->head);
    if(q->head == &(q->item[MAXQUEUE -1])){
        q->head = q->item;
    }else{
        q->head ++;
    }
    return aux;
}

int queue_size(const Queue *q){
    if(q== NULL) return -1;
    if(queue_isFull(q) == TRUE) return MAXQUEUE;
    if(queue_isEmpty(q)== TRUE) return 0;
    
    if(q->head < q->end){
        return q->end - q->head;
    }else{
        return MAXQUEUE - (q->head - q->end);
    }
}

int queue_print(FILE *pf, const Queue *q){
    int i, numChar;
    void **aux;
    if(pf == NULL || q == NULL) return -1;
    
    aux = q->head;
    numChar = 0;
    while(aux!=q->end){
        i = q->print_element_function(pf, *aux);
        numChar += fprintf(pf, "\n");
        if(i == -1) return -1; /*Si da error al imprimir el elemento devolvemos -1*/
        numChar += i;
        if(aux == &(q->item[MAXQUEUE -1])){
            aux = q->item;
        }else{
            aux ++;
        }
    }
    return numChar;
}