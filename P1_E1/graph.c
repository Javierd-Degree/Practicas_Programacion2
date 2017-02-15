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
            free(g->dat[i]);
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
            return g->dat[i];   //Devolvemos un puntero al nodo, no una copia de éste, para que se pueda editar etc
        }
    }
    return NULL;
}

Bool graph_areConnected(const Graph *g, const int nId1, const int nId2){
    if (g == NULL) return FALSE;
    int pos1, pos2;
    pos1 = find_node_index(g, nId1);
    pos2 = find_node_index(g, nId2);
    
    if(pos1 == -1 || pos2 == -1) return FALSE;
    
    if(g->conexion[pos1][pos2] || g->conexion[pos2][pos1]) return TRUE;
    return FALSE;
}

void main(){

    Node *n1, *n2;
    n1 = node_ini();
    node_setName(n1, "topotamadre");
    node_setId(n1, 21);
    n2 = node_ini();
    node_setName(n2, "Hola");
    node_setId(n2, 69);
    
    Graph *g;
    g = graph_ini();
    graph_addNode(g, n1);
    graph_addNode(g, n2);
    
    int nNodes = graph_getNnodes(g);
    int *Ids, i;
    printf("Numero de nodos: %d\n", nNodes);
    Ids = graph_getNodeIds(g);
    for(i=0; i< nNodes; i++){
        printf("ID : %d\n", Ids[i]);
    }
    
    graph_addEdge(g, node_getId(n1), node_getId(n2));
    printf("Numero de enlaces: %d\n", graph_getNedges(g));
    
    
    node_destroy(n1);
    node_destroy(n2);
    graph_destroy(g);
}
   
//Hola