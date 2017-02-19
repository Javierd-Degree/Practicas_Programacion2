#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"

/*void main(){

    Node *n1, *n2, *n3;
    n1 = node_ini();
    node_setName(n1, "a");
    node_setId(n1, 1);
    n2 = node_ini();
    node_setName(n2, "b");
    node_setId(n2, 2);
    n3 = node_ini();
    node_setName(n3, "c");
    node_setId(n3, 3);
    
    Graph *g;
    g = graph_ini();
    graph_addNode(g, n1);
    graph_addNode(g, n2);
    graph_addNode(g, n3);
    
    int nNodes = graph_getNnodes(g);
    int *Ids, i;
    printf("Numero de nodos: %d\n", nNodes);
    Ids = graph_getNodeIds(g);
    for(i=0; i< nNodes; i++){
        printf("ID : %d\n", Ids[i]);
    }
    
    graph_addEdge(g, node_getId(n1), node_getId(n2));

    printf("Numero de enlaces: %d\n", graph_getNedges(g));
    
    printf("Numero de conexiones desde 1: %d\n", graph_getNumberOfConnectionsFrom(g, node_getId(n1)));
    printf("Primera conexión de 1 es con: %d\n", graph_getConnectionsFrom(g, node_getId(n1))[0]);
    
    printf("Numero de conexiones a 1: %d\n", graph_getNumberOfConnectionsTo(g, node_getId(n1)));
    printf("Primera conexión a 1 es con: %d\n", graph_getConnectionsTo(g, node_getId(n1))[0]);
    
    FILE *f;
    f = fopen("texto.txt", "w");
    
    int n = graph_print(f,g);
    printf("numero de caracteres escritos : %d", n);
    
    
    
    node_destroy(n1);
    node_destroy(n2);
    node_destroy(n3);
    graph_destroy(g);
}*/
