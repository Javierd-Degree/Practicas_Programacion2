#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct _Graph{
    Node *dat[MAX_NODES];
    List *out_connections[MAX_NODES];
    List *in_connections[MAX_NODES];
   
    int nNodes;
}Graph;

Graph *graph_ini(){
    int i;
    Graph *g;
    g = (Graph *)malloc(sizeof(Graph));
    if(g == NULL) return NULL;
    g->nNodes = 0;
    
    for(i = 0; i < MAX_NODES; i++){
        g->dat[i] = NULL;
        g->out_connections[i] = NULL;
        g->in_connections[i] = NULL;
    }
    
    return g;
}

void graph_destroy(Graph *g){
    int i;
    if(g == NULL) return;
    
    for(i=0; i<g->nNodes; i++){
        if(g->dat[i] != NULL){
            node_destroy(g->dat[i]);
        }
        if(g->out_connections[i] != NULL){
            list_free(g->out_connections[i]);
        }
        if(g->in_connections[i] != NULL){
            list_free(g->in_connections[i]);
        }
        
    }
    free(g);
}

int graph_getNnodes(const Graph *g){
    if (g == NULL) return -1;
    return g->nNodes;
}

int *graph_getNodeIds(const Graph *g){
    int i, *nIds;
    if (g == NULL) return NULL;
    nIds = (int *)malloc(sizeof(int)* g->nNodes);
    if (nIds == NULL) return NULL;
    
    for(i=0; i<g->nNodes; i++){
        nIds[i] = node_getId(g->dat[i]);
    }
    return nIds;
}

int graph_getNedges(const Graph *g){
    int i, numEdges;
    if (g == NULL) return -1;
    
    /*Sabemos que en un grafo dirigido, la suma de todas las conexiones entrantes mas las salientes es dos veces el número de enlaces*/
    
    for(i=0, numEdges = 0; i< g->nNodes; i++){
        numEdges = numEdges + list_size(g->out_connections[i]);
        numEdges = numEdges + list_size(g->in_connections[i]);
    }
    
    return numEdges/2;
}

Graph *graph_addNode(Graph *g, const Node *n){
    Node *nCopy;
    List *out_connections, *in_connections;
    if (g == NULL || n == NULL) return NULL;
    if(g->nNodes >= MAX_NODES) return NULL;
    
    nCopy = node_copy(n);
    if ( nCopy == NULL) return NULL;
    
    out_connections = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(out_connections == NULL){
        node_destroy(nCopy);
        return NULL;
    }
    in_connections  = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, compare_intp_function);
    if(in_connections == NULL){
        node_destroy(nCopy);
        list_free(out_connections);
        return NULL;
    }
    
    g->dat[g->nNodes] = nCopy;
    g->out_connections[g->nNodes] = out_connections;
    g->in_connections[g->nNodes] = in_connections;
    g->nNodes++;
    
    return g;
}

int find_node_index(const Graph *g, int nId1){
    int i;
    if (g == NULL) return -1;
    for(i=0; i<g->nNodes; i++){
        if(node_getId(g->dat[i]) == nId1) return i;
    }
    return -1;
}

Graph *graph_addEdge(Graph *g, const int nId1, const int nId2){
    int pos1, numConex, i, *temp;
    if (g == NULL) return NULL;
    
    pos1 = find_node_index(g, nId1);
    if(pos1 == -1) return NULL; /*Por si no existe*/
    
    numConex = list_size(g->out_connections[pos1]);
    if(numConex == -1) return NULL;
    
    /*Comprobamos en primer lugar si ya está añadido*/
    for(i = 0; i < numConex; i++){
        temp = (int *)list_get(g->out_connections[pos1], i);
        printf("Prueba %d\n", *temp);
        if(*temp == nId2){
            return g;
        }
    }
    
    /*Si no está ya añadido, ponemos el enlace*/
    list_insertLast(g->out_connections[pos1], &nId2);
    
    return g;
}

Node *graph_getNode(const Graph *g, int nId){
    int i;
    if (g == NULL) return NULL;
    
    for(i=0; i<g->nNodes; i++){
        if(node_getId(g->dat[i]) == nId){
            return g->dat[i];   /*Devolvemos un puntero al nodo, no una copia de éste, para que se pueda editar etc*/
        }
    }
    return NULL;
}

Bool graph_areConnected(const Graph *g, const int nId1, const int nId2){
    int pos1, pos2, numConex1, numConex2, *temp, i;
    if (g == NULL) return FALSE;
    
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    if(pos1 == -1 || pos2 == -1) return FALSE; /*Por si alguno no existe*/
    
    numConex1 = list_size(g->out_connections[pos1]);
    numConex2 = list_size(g->out_connections[pos2]);
    if(numConex1 == -1 || numConex2 == -1) return FALSE;
   
    /*Comprobamos si el primero está conectado al segundo*/
    for(i = 0; i < numConex1; i++){
        temp = (int *)list_get(g->out_connections[pos1], i);
        if(*temp == nId2){
            return TRUE;
        }
    }
    
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
    int i, toId, numConex = 0;
    if(g == NULL) return -1;
    
    /*Revisamos las conexiones mirando toda la fila del nodo*/
    for(i=0; i<g->nNodes; i++){
        toId = node_getId(g->dat[i]);
        if(toId == -1) continue; /*El nodo no es válido, lo saltamos*/
        if(graph_areConnected(g, fromId, toId) == TRUE){
            numConex ++;
        }
    }
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
    int i, toId, numConex;
    if(g == NULL) return -1;
    /*Revisamos las filas de la matriz en la columna del nodo*/
    for(i=0, numConex=0; i<g->nNodes; i++){
        toId = node_getId(g->dat[i]);
        if(toId == -1) continue; /*El nodo no es válido, lo saltamos*/
        if(graph_areConnected(g, toId, fromId)){
            numConex ++;
        }
    }
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
        Bool conex;
        numChar=0;
        numChar+=fprintf(pf,"N=%d, E=%d:\n", graph_getNnodes(g), graph_getNedges(g));
        
        for(i=0;i<(g->nNodes);i++){
            numChar+=fprintf(pf,"[%d , %s]->", node_getId(g->dat[i]), node_getName(g->dat[i]));
            for(j=0;j<g->nNodes;j++){
                
                conex = graph_areConnected(g, node_getId(g->dat[i]), node_getId(g->dat[j]));
                
                numChar+=fprintf(pf,"%d ", conex);
            }
            numChar+=fprintf(pf,"\n");
        }
    return numChar;
}
