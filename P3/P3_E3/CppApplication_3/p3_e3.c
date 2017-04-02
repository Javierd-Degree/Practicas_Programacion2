#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"

#define MAXNAME 100

int main(int argc, char** argv) {
    int temp, numElem;
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
        fscanf(f, "%d\n", &temp);
        if(temp%2 == 0){
            list_insertFirst(list, &temp);
        }else{
            list_insertLast(list, &temp);
        }
        printf("Lista con %d elementos:\n", list_size(list));
        list_print(stdout, list);
    }
    
    numElem = list_size(list);
    
    while(!list_isEmpty(list)){
        if(list_size(list) >= numElem / 2){ /*La primera mitad de los elementos*/
            temp = *((int*) list_extractFirst(list));
        }else{
            temp = *((int*) list_extractLast(list));
        }
        printf("Extraído el elemento %d.\n", temp);
        printf("Lista con %d elementos:\n", list_size(list));
        list_print(stdout,list);
        list_insertInOrder(orderedList, &temp);
        printf("Lista ordenada con %d elementos:\n", list_size(orderedList));
        list_print(stdout, orderedList);
    }
    
    fclose(f);
    list_free(list);
    list_free(orderedList);
    return (EXIT_SUCCESS);
}

