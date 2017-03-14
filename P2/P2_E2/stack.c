#include "stack.h"
#include <stdlib.h>  /*Si no da error al compilar*/

struct _Stack {
    int top;
    Element* item[MAXSTACK];
};

Stack * stack_ini(){
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    if(s==NULL) return NULL;
    s->top = 0;
    return s;
}

void stack_destroy(Stack *s){
    int i;
    if(s==NULL) return;
    for(i=0; i<s->top; i++){
        /*Liberamos cada uno de los elementos de la pila*/
        element_destroy(s->item[i]);
    }
    free(s);
}

Stack * stack_push(Stack *s, const Element *e){
    if(s==NULL || e==NULL || stack_isFull(s)) return NULL;
    Element *ec;
    ec = element_copy(e);
    if (ec == NULL )return NULL;
    s->item[s->top] = ec;
    s->top ++;
    return s;
}

Element * stack_pop(Stack *s){
    if(s==NULL) return NULL;
    /*No hay ningún elemento*/
    if(stack_isEmpty(s)) return NULL;
    /*Reducimos el número de elementos y mandamos el último*/
    s->top--;
    return s->item[s->top];
}

Element * stack_top(const Stack *s){
    if(s==NULL) return NULL;
    /*No hay ningún elemento*/
    if(stack_isEmpty(s)) return NULL; 
    return s->item[s->top -1];
}

Bool stack_isEmpty(const Stack *s){
    if(s==NULL) return TRUE;
    /*No hay ningún elemento*/
    if(s->top == 0) return TRUE;
    return FALSE;
}

Bool stack_isFull(const Stack *s){
    if(s==NULL) return FALSE;
    /*No hay ningún elemento*/
    if(s->top == MAXSTACK) return TRUE;
    return FALSE;
}

int stack_print(FILE *f, const Stack *s){
    int i, numChar, temp;
    if(s == NULL || f == NULL) return -1;
    for(i=(s->top -1); i>=0; i--){
        temp = element_print(f, s->item[i]);
        if(temp == -1) return -1;
        /*Si falla al imprimir un elemento, ya ha fallado*/
        numChar += temp;
        numChar += printf("\n");
    }
    return numChar;
}




