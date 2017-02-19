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

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
    int i, posNode, numConex = 0;
    if(g == NULL) return -1;
    posNode = find_node_index(g, fromId);
    //Revisamos las conexiones mirand toda la fila del nodo
    for(i=0; i<g->nNodes; i++){
        if(g->conexion[posNode][i] == TRUE){
            numConex ++;
        }
    }
    return numConex;
}

int* graph_getConnectionsFrom(const Graph * g, const int fromId){
    int i, posNode, numConex, addedNodes, *listConex;
    if(g == NULL) return NULL;
    numConex = graph_getNumberOfConnectionsFrom(g, fromId);
    if(numConex == 0) return NULL;
    listConex = (int *)malloc(sizeof(int)*numConex);
    if(listConex == NULL) return NULL;
    posNode = find_node_index(g, fromId);
    //Revisamos las conexiones mirand toda la fila del nodo
    for(i=0, addedNodes=0; i<g->nNodes; i++){
        if(g->conexion[posNode][i] == TRUE){
            listConex[addedNodes] = node_getId(g->dat[i]);
            addedNodes++;
        }
    }
    return listConex;
}

int graph_getNumberOfConnectionsTo(const Graph * g, const int fromId){
    int i, posNode, numConex = 0;
    if(g == NULL) return -1;
    posNode = find_node_index(g, fromId);
    //Revisamos las conexiones mirand toda la fila del nodo
    for(i=0; i<g->nNodes; i++){
        if(g->conexion[i][posNode] == TRUE){
            numConex ++;
        }
    }
    return numConex;
}

int* graph_getConnectionsTo(const Graph * g, const int fromId){
    int i, posNode, numConex, addedNodes, *listConex;
    if(g == NULL) return NULL;
    numConex = graph_getNumberOfConnectionsFrom(g, fromId);
    if(numConex == 0) return NULL;
    listConex = (int *)malloc(sizeof(int)*numConex);
    if(listConex == NULL) return NULL;
    posNode = find_node_index(g, fromId);
    //Revisamos las conexiones mirand toda la fila del nodo
    for(i=0, addedNodes=0; i<g->nNodes; i++){
        if(g->conexion[i][posNode] == TRUE){
            listConex[addedNodes] = node_getId(g->dat[i]);
            addedNodes++;
        }
    }
    return listConex;
}
int graph_print(FILE *pf, const Graph *g){
        int i,j,n1,nt,n2,n3;
        nt=0;
        n1=fprintf(pf,"N= %d E= %d \n",graph_getNedges(g),graph_getNnodes(g));
        for(i=0;i<(g->nNodes);i++){
            n2=fprintf(pf,"[ %d , %s]-> ", node_getId(g->dat[i]),node_getName(g->dat[i]));
            n3=0;
            for(j=0;j<g->nNodes;j++){
            fprintf(pf,"%d", g->conexion[i][j]);
            n3++;
            }
            fprintf(pf,"\n");
            nt=nt+n2+n3;
        }
        nt=nt+n1;
        
    return nt;
}
