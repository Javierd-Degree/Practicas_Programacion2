#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "graph.h"

typedef struct _Graph{
    Node* nodes[MAX_NODES];
    List* out_connections[MAX_NODES]; /* Listas de enteros */
    List* in_connections[MAX_NODES]; /* Listas de enteros */
}Graph;

Graph *graph_ini(){
    int i, j;
    Graph *g;
    g = (Graph *)malloc(sizeof(Graph));
    if(g == NULL) return NULL;
    g->out_connections = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    g->in_connections = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(g->out_connections == NULL || g->in_connections == NULL) return NULL;
    for(i=0; i<MAX_NODES; i++){
        g->nodes[i] = NULL;
    }
    
    return g;
}

void graph_destroy(Graph *g){
    int i;
    if(g == NULL) return;
    
    for(i=0; i<MAX_NODES; i++){
        if(g->nodes[i] != NULL){
            node_destroy(g->nodes[i]);
        }
    }
    
    list_free(g->out_connections);
    list_free(g->in_connections);
    
    free(g);
}

int graph_getNnodes(const Graph *g){
    int i=0;
    if (g == NULL) return -1;
    
    while(g->nodes[i] != NULL){
        i++;
    }
    return i;
}

int *graph_getNodeIds(const Graph *g){
    int i;
    if (g == NULL) return NULL;
    int *nIds = (int *)malloc(sizeof(int)* graph_getNnodes(g));
    if (nIds == NULL) return NULL;
    
    for(i=0; i<graph_getNnodes(g); i++){
        nIds[i] = node_getId(g->nodes[i]);
    }
    return nIds;
}

int graph_getNedges(const Graph *g){
    int i, numEdges;
    if (g == NULL) return -1;
    
    for(i=0; i<graph_getNnodes(g); i++){
       if(g->out_connections[i] != NULL){
           numEdges += list_size(g->out_connections[i]);
       }
    }
 
    return numEdges;
}

Graph *graph_addNode(Graph *g, const Node *n){
    if (g == NULL || n == NULL) return NULL;
    if(graph_getNnodes(g)>= MAX_NODES) return NULL;
    
    Node *nCopy;
    nCopy = node_copy(n);
    if ( nCopy == NULL) return NULL;
    
    g->nodes[graph_getNnodes(g)] = nCopy;
    
    return g;
}

int find_node_index(const Graph *g, int nId1){
    int i;
    if (g == NULL) return -1;
    for(i=0; i<graph_getNnodes(g); i++){
        if(node_getId(g->nodes[i]) == nId1) return i;
    }
    return -1;
}

Graph *graph_addEdge(Graph *g, const int nId1, const int nId2){
    int i, pos1, pos2;
    if (g == NULL) return NULL;
    
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    
    if(pos1 == -1 || pos2 == -1) return NULL;
    
    list_insertLast(g->out_connections[pos1], nId2);
    list_insertLast(g->in_connections[pos2], nId1);
     
    return g;
}

Node *graph_getNode(const Graph *g, int nId){
    int i;
    if (g == NULL) return NULL;
    
    for(i=0; i<graph_getNnodes(g); i++){
        if(node_getId(g->nodes[i]) == nId){
            return g->nodes[i];   /*Devolvemos un puntero al nodo, no una copia de éste, para que se pueda editar etc*/
        }
    }
    return NULL;
}

Bool graph_areConnected(const Graph *g, const int nId1, const int nId2){
    if (g == NULL) return FALSE;
    int pos1, pos2;
    
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    
    if(pos1 == -1 || pos2 == -1) return FALSE; /*Por si alguno no existe*/
   
    if(g->out_connections[]) return TRUE;
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
    int i, pos, numConex = 0;
    if(g == NULL) return -1;
    pos = find_node_index(g, fromId);
  
    numConex = list_size(g->out_connections[pos]);

    return numConex;
}

int* graph_getConnectionsFrom(const Graph * g, const int fromId){
    int i, numConex, addedNodes, toId, *listConex;
    if(g == NULL) return NULL;
    
    numConex = graph_getNumberOfConnectionsFrom(g, fromId);
    if(numConex == 0 || numConex == -1) return NULL;
    
    listConex = (int *)malloc(sizeof(int)*numConex);
    if(listConex == NULL) return NULL;
    
    /*Revisamos las conexiones mirando toda la fila del nodo*/
    for(i=0, addedNodes=0; i<g->nNodes; i++){
        toId = node_getId(g->dat[i]);
        if(toId == -1) continue; /*El nodo no es válido, lo saltamos*/
        if(graph_areConnected(g, fromId, toId)){
            listConex[addedNodes] = toId;
            addedNodes++;
        }
    }
    return listConex;
}

int graph_getNumberOfConnectionsTo(const Graph * g, const int fromId){
    int i, pos, numConex = 0;
    if(g == NULL) return -1;
    pos = find_node_index(g, fromId);
  
    numConex = list_size(g->in_connections[pos]);

    return numConex;
}

int* graph_getConnectionsTo(const Graph * g, const int fromId){
    int i, toId, numConex, addedNodes, *listConex;
    if(g == NULL) return NULL;
    
    numConex = graph_getNumberOfConnectionsTo(g, fromId);
    if(numConex == 0 || numConex == -1) return NULL;
    
    listConex = (int *)malloc(sizeof(int)*numConex);
    if(listConex == NULL) return NULL;
    
    /*Revisamos las filas de la matriz en la columna del nodo*/
    for(i=0, addedNodes=0; i<g->nNodes; i++){
        toId = node_getId(g->dat[i]);
        if(toId == -1) continue; /*El nodo no es válido, lo saltamos*/
        if(graph_areConnected(g, toId, fromId) == TRUE){
            listConex[addedNodes] = toId;
            addedNodes++;
        }
    }
    return listConex;
}

int graph_print(FILE *pf, const Graph *g){
        int i, j, numChar;
        numChar=0;
        numChar+=fprintf(pf,"N=%d, E=%d:\n", graph_getNnodes(g), graph_getNedges(g));
        
        for(i=0;i<graph_getNnodes(g);i++){
            numChar+=fprintf(pf,"[%d , %s]->", node_getId(g->nodes[i]), node_getName(g->nodes[i]));
            for(j=0;j<graph_getNnodes(g);j++){
                numChar+=fprintf(pf,"%d ", g->conexion[i][j]);
            }
            numChar+=fprintf(pf,"\n");
        }
    return numChar;
}