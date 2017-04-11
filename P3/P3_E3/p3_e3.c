#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"

#define MAXNAME 100

int main(int argc, char** argv) {
    int numElem, *intAux;
    char file_name[MAXNAME];
    FILE *f = NULL;
    List *list = NULL, *orderedList = NULL;
    
    if(argc < 2){
        printf("No hay suficientes argumentos");
        return -1;
    }
    strcpy(file_name, argv[1]);
    f = fopen(file_name, "r");
    if(f == NULL){
        printf("Error al abrir el archivo.\n");
        return -1;
    }
    
    list = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if (list == NULL){
        fclose(f);
        printf("Error al iniciar la lista.\n");
        return -1;
    }
    
    orderedList = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if (orderedList == NULL){
        fclose(f);
        list_free(list);
        printf("Error al iniciar la lista.\n");
        return -1;
    }
    
    while(!feof(f)){
        intAux = (int *)malloc(sizeof(int));
        fscanf(f, "%d\n", intAux);
        if((*intAux)%2 == 0){
            list_insertFirst(list, intAux);
        }else{
            list_insertLast(list, intAux);
        }
        printf("Lista con %d elementos:\n", list_size(list));
        list_print(stdout, list);
        destroy_intp_function(intAux);
    }
    
    numElem = list_size(list);
    
    while(!list_isEmpty(list)){
        if(list_size(list) >= numElem / 2){ /*La primera mitad de los elementos*/
            intAux = (int*) list_extractFirst(list);
        }else{
            intAux = (int*) list_extractLast(list);
        }
        printf("Lista con %d elementos:\n", list_size(list));
        list_print(stdout,list);
        list_insertInOrder(orderedList, intAux);
        printf("Lista ordenada con %d elementos:\n", list_size(orderedList));
        if(intAux != NULL) destroy_intp_function(intAux);
        list_print(stdout, orderedList);
    }
    
    fclose(f);
    list_free(list);
    list_free(orderedList);
    return (EXIT_SUCCESS);
}

