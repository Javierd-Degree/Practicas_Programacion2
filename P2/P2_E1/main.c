#include <stdlib.h>
#include "stack.h"
#include "element.h"

int main(int argc, char** argv) {
    int numEnteros, i, temp;
    Element **elementos, *tempElement;
    Stack *sTotal, *sPar, *sImpar;
    sTotal = stack_ini();
    tempElement = element_ini();
    
    numEnteros = atoi(argv[1]);
    elementos = (Element **)malloc(numEnteros*sizeof(Element *));
    
    /*Comprobamos la pila total*/
    printf("Pila total ");
    if(stack_isFull(sTotal)){
        printf("(llena, ");
    }else{
        printf("(no llena, ");
    }
    if(stack_isEmpty(sTotal)){
        printf("vacía):\n\n");
    }else{
        printf("no vacía):\n\n");
    }
    
    sPar = stack_ini();
    sImpar = stack_ini();
    
    /*TODO DECLARAR ELEMENTOS, NO FUNCIONA*/
    
    for(i = 0; i < numEnteros; i++){
        printf("Introduce número: ");
        scanf("\n%d", &temp);
        elementos[i] = element_ini();
        element_setInfo(elementos[i], &temp);
        
        stack_push(sTotal, elementos[i]);
        if(temp%2){
            stack_push(sImpar, elementos[i]);
        }else{
            stack_push(sPar, elementos[i]);
        }
    }
    
    /*Comprobamos la pila total*/
    printf("Pila total ");
    if(stack_isFull(sTotal)){
        printf("(llena, ");
    }else{
        printf("(no llena, ");
    }
    if(stack_isEmpty(sTotal)){
        printf("vacía):\n");
    }else{
        printf("no vacía):\n");
    }
    
    while(stack_isEmpty(sTotal) == FALSE){
        tempElement = stack_pop(sTotal);
        element_print(stdout, tempElement);
        printf("\n");
    }
   
    /*Comprobamos la pila par*/
    printf("Imprimiendo la pila ");
    if(stack_isFull(sPar)){
        printf("(llena, ");
    }else{
        printf("(no llena, ");
    }
    if(stack_isEmpty(sPar)){
        printf("vacía) con números pares:\n");
    }else{
        printf("no vacía) con números pares:\n");
    }
    while(stack_isEmpty(sPar) == FALSE){
        tempElement = stack_pop(sPar);
        element_print(stdout, tempElement);
        printf("\n");
    }
    
    /*Comprobamos la pila par*/
    printf("Imprimiendo la pila ");
    if(stack_isFull(sImpar)){
        printf("(llena, ");
    }else{
        printf("(no llena, ");
    }
    if(stack_isEmpty(sImpar)){
        printf("vacía) con números impares:\n");
    }else{
        printf("no vacía) con números impares:\n");
    }

    while(stack_isEmpty(sImpar) == FALSE){
        tempElement = stack_pop(sImpar);
        element_print(stdout, tempElement);
        printf("\n");
    }
   
    /*TODO VER LAS SALIDAS REALES QUE TIENE QUE TENER (PILA NO LLENA, VACÍA)*/
    /*Comprobamos la pila total*/
    printf("Pila total ");
    if(stack_isFull(sTotal)){
        printf("(llena, ");
    }else{
        printf("(no llena, ");
    }
    if(stack_isEmpty(sTotal)){
        printf("vacía):\n");
    }else{
        printf("no vacía):\n");
    }
    
    
    free(elementos);
    element_destroy(tempElement);
    stack_destroy(sTotal);
    stack_destroy(sPar);
    stack_destroy(sImpar);
   
    return (EXIT_SUCCESS);
}

/*
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
} */

