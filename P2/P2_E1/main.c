#include <stdlib.h>
#include "element.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Element *e1, *e2;
    int h = 11;
    e1=element_ini();
    e2=element_ini();
    
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
    
    element_destroy(e1);
    element_destroy(e2);
    return (EXIT_SUCCESS);
}

