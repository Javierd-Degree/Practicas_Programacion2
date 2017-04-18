#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define MAX_NAME 100

int main(int argc, char** argv) {
    char name[MAX_NAME];
    FILE *f = NULL;
    Tree *t = NULL;
    int *temp;
    
    if(argc <= 1){
        printf("Datos insuficientes");
        return -1;
    }
    
    t = tree_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(t == NULL) return -1;
    
    strcpy(name, argv[1]);
    
    f = fopen(name, "r");
    if (f == NULL){
        tree_destroy(t);
        return -1;
    } 
    
    while (!feof(f)){
        fscanf("%d\n", temp);
        
    }
    
    fclose(f);
    return (EXIT_SUCCESS);
}

