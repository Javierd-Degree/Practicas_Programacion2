#include <stdlib.h>
#include "stack.h"
#include "element.h"

/*int main(int argc, char** argv) {
    int numEnteros, i, temp;
    Element **elementos, *tempElement;
    Stack *sTotal, *sPar, *sImpar;
    sTotal = stack_ini();
    tempElement = element_ini();
    
    numEnteros = atoi(argv[1]);
    elementos = (Element **)malloc(numEnteros*sizeof(Element *));
    
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
}*/

