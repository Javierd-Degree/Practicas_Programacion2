#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"

int main(int argc, char** argv) {
    List *l;
    char name[100];
    FILE *f = NULL;
    Tree *t = NULL;
    int temp;

    printf("Programa iniciado\n");
    
    if(argc <= 1){
        printf("Datos insuficientes");
        return -1;
    }
    
    t = tree_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(t == NULL) return -1;
    
    printf("Arbol iniciado\n");

    strcpy(name, argv[1]);
    
    f = fopen(name, "r");
    if (f == NULL){
        tree_destroy(t);
        return -1;
    } 
    
    while (!feof(f)){
        fscanf(f, "%d\n", &temp);
        printf("Numero introducido %d\n", temp);
        if (!tree_insert(t, &temp)) printf("Error al insertar el elemento %d", temp);
    }
    
    printf("Numero de nodos: %d\n", tree_numNodes(t));
    printf("Profundidad: %d\n", tree_depth(t));

    l = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(l == NULL){
        tree_destroy(t);
        fclose(f);
        printf("Error al crear la lista");
        return -1;
    }
    printf("Orden previo: ");
    tree_preOrderToList(l, t);
    list_print(stdout, l);
    printf("\n");
    list_free(l);

    l = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(l == NULL){
        tree_destroy(t);
        fclose(f);
        printf("Error al crear la lista");
        return -1;
    }
    printf("Orden medio: ");
    tree_inOrderToList(l, t);
    list_print(stdout, l);
    printf("\n");
    list_free(l);

    l = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(l == NULL){
        tree_destroy(t);
        fclose(f);
        printf("Error al crear la lista");
        return -1;
    }
    printf("Orden posterior: ");
    tree_postOrderToList(l, t);
    list_print(stdout, l);
    printf("\n");
    list_free(l);

    printf("Introduzca un numero: ");
    scanf("%d", &temp);
    printf("Numero introducido %d\n", temp);
    if(tree_find(t, &temp)) printf("El dato %d se encuentra dentro del Arbol\n", temp);
    else printf("El dato %d no se encuentra dentro del Arbol\n", temp);
    
    
    tree_destroy(t);
    fclose(f);
    return (EXIT_SUCCESS);
}

