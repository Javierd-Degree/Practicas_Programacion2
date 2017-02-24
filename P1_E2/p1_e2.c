#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"

int main(int argc, char** argv) {

    Node *n1, *n2;
    n1 = node_ini();
    node_setName(n1, "first");
    node_setId(n1, 111);
    n2 = node_ini();
    node_setName(n2, "second");
    node_setId(n2, 222);
    
    Graph *g;
    g = graph_ini();
    graph_print(stdout, g);

    printf("Insertando nodo 1...\n");
    graph_addNode(g, n1);
    graph_print(stdout, g);
    
    printf("Insertando nodo 2...\n");
    graph_addNode(g, n2);
    graph_print(stdout, g);
    printf("Conectados nodo 1 y nodo 2? ");
    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    printf("Conectados nodo 2 y nodo 1? ");
    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    
    
    printf("Insertando nodo 2-> nodo 1\n");
    graph_addEdge(g, node_getId(n2), node_getId(n1));
    graph_print(stdout, g);
    printf("Conectados nodo 1 y nodo 2? ");
    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    printf("Conectados nodo 2 y nodo 1? ");
    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    
    printf("Insertando nodo 1-> nodo 2\n");
    graph_addEdge(g, node_getId(n1), node_getId(n2));
    graph_print(stdout, g);
    printf("Conectados nodo 1 y nodo 2? ");
    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    printf("Conectados nodo 2 y nodo 1? ");
    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    
    printf("Insertando nodo 2-> nodo 1\n");
    graph_addEdge(g, node_getId(n2), node_getId(n1));
    graph_print(stdout, g);
    printf("Conectados nodo 1 y nodo 2? ");
    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    printf("Conectados nodo 2 y nodo 1? ");
    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == TRUE){
        printf("Sí\n");
    }else{
        printf("No\n");
    }
    
    node_destroy(n1);
    node_destroy(n2);
    graph_destroy(g);
    return (EXIT_SUCCESS);
}
