/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.c
 * Author: eps
 *
 * Created on 14 de febrero de 2017, 12:31
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct _Graph{
    Node *dat[MAX_NODES];
    Bool conexion[MAX_NODES][MAX_NODES];
    int nNodes;
}Graph;

Graph *graph_ini(){
    int i, j;
    Graph *g;
    g = (Graph *)malloc(sizeof(Graph));
    if(g == NULL) return NULL;
    g->nNodes = 0;
    
    for(i=0; i<MAX_NODES; i++){
        for(j=0; j<MAX_NODES; j++){
            g->conexion[i][j] = FALSE;
        }
    }
    for(i=0; i<MAX_NODES; i++){
        g->dat[i] = NULL;
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
    }
    free(g);
}

int graph_getNnodes(const Graph *g){
    if (g == NULL) return -1;
    return g->nNodes;
}

int *graph_getNodeIds(const Graph *g){
    int i;
    if (g == NULL) return NULL;
    int *nIds = (int *)malloc(sizeof(int)* g->nNodes);
    if (nIds == NULL) return NULL;
    
    for(i=0; i<g->nNodes; i++){
        nIds[i] = node_getId(g->dat[i]);
    }
    return nIds;
}

int graph_getNedges(const Graph *g){
    int i, j, numEdges;
    if (g == NULL) return -1;
    
    for(i=0, numEdges = 0; i<MAX_NODES; i++){
        for(j=0; j<MAX_NODES; j++){
            if(g->conexion[i][j] == TRUE) numEdges ++;
        }
    }
    return numEdges;
}

Graph *graph_addNode(Graph *g, const Node *n){
    if (g == NULL || n == NULL) return NULL;
    if(g->nNodes>= MAX_NODES) return NULL;
    
    Node *nCopy;
    nCopy = node_copy(n);
    if ( nCopy == NULL) return NULL;
    
    g->dat[g->nNodes] = nCopy;
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
    int pos1, pos2;
    if (g == NULL) return NULL;
    
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    
    if(pos1 == -1 || pos2 == -1) return NULL;
    g->conexion[pos1][pos2] = TRUE;
    
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
    if (g == NULL) return FALSE;
    int pos1, pos2;
    
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    
    if(pos1 == -1 || pos2 == -1) return FALSE; /*Por si alguno no existe*/
   
    if(g->conexion[pos1][pos2]) return TRUE;
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
        numChar=0;
        numChar+=fprintf(pf,"N=%d, E=%d:\n", graph_getNnodes(g), graph_getNedges(g));
        
        for(i=0;i<(g->nNodes);i++){
            numChar+=fprintf(pf,"[%d , %s]->", node_getId(g->dat[i]), node_getName(g->dat[i]));
            for(j=0;j<g->nNodes;j++){
                numChar+=fprintf(pf,"%d ", g->conexion[i][j]);
            }
            numChar+=fprintf(pf,"\n");
        }
    return numChar;
}
