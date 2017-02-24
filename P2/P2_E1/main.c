#include <stdlib.h>
#include "stack.h"
#include "element.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Element *e1, *e2, *e3;
    int h = 11;
    e1=element_ini();
    e2=element_ini();
    e3=element_ini();
    
    element_setInfo(e1, &h);
    if(element_equals(e1, e2)){
        printf("Son iguales\n");
    }else{
        printf("No son iguales\n");
    }
    
    e2 = element_copy(e1);
    if(element_equals(e1, e2)){
        printf("Son iguales\n");
    }else{
        printf("No son iguales\n");
    }
    
    element_print(stdout, e1);
    element_print(stdout, e2);
    
    printf("Creamos una cola\n");
    
    Stack *s;
    s = stack_ini();
    printf("Está vacía la cola?: %d\n", stack_isEmpty(s));
    
    stack_push(s, e1);
    stack_push(s, e2);
    
    printf("Imprimimos la pila\n");
    stack_print(stdout, s);
    printf("Está vacía la cola?: %d\n", stack_isEmpty(s));
    printf("Está llena la cola?: %d\n", stack_isFull(s));
    
    printf("Imprimimos el elemento e3\n");
    e3 = stack_pop(s);
    element_print(stdout, e3);
    stack_destroy(s);
    
    element_destroy(e1);
    element_destroy(e2);
    return (EXIT_SUCCESS);
}

