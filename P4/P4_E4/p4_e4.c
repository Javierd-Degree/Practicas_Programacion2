#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "tree.h"

int main(int argc, char** argv) {
    Node *nTemp;
    char name[1000];
    FILE *f = NULL;
    Tree *t = NULL;
    int temp;

    printf("Programa iniciado\n");
    
    if(argc <= 1){
        printf("Datos insuficientes");
        return -1;
    }
    
    t = tree_ini(destroy_node_function, copy_node_function, print_node_function, cmp_node_function);
    if(t == NULL) return -1;

    strcpy(name, argv[1]);
    
    f = fopen(name, "r");
    if (f == NULL){
        tree_destroy(t);
        return -1;
    } 
    
    while (!feof(f)){
        nTemp = node_ini();
        fscanf(f, "%s\n", name);
        node_setName(nTemp, name);
        if (!tree_insert(t, nTemp)) printf("Error al insertar el elemento %s", name);
        node_destroy(nTemp);
    }
    
    printf("Numero de nodos: %d\n", tree_numNodes(t));
    printf("Profundidad: %d\n", tree_depth(t));

    tree_inOrder(stdout, t);
    printf("\n");

    printf("Introduce una cadena para buscar en el arbol (siguiendo el mismo formato que en el fichero de entrada): ");

    scanf("%s", name);
    nTemp = node_ini();
    node_setName(nTemp, name);

    if(tree_find(t, nTemp)) printf("Elemento encontrado!\n");
    else printf("Elemento no encontrado!\n");
    
    node_destroy(nTemp);
    tree_destroy(t);
    fclose(f);
    return (EXIT_SUCCESS);
}

