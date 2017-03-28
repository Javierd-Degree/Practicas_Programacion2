#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "node.h"
#include "queue.h"
#include "functions.h"
#define MAX 255
#define MAX_NODES 4096

Graph * read_graph_from_file(char * filename){
	FILE * in;
	Graph * g;
	Node * n;
    char buff[MAX], name[MAX];
	int i, nnodes, id1, id2;

	g = graph_ini();
	if (g == NULL){
		return NULL;
	}
	in = (FILE*) fopen(filename, "r");
	if (in == NULL){
		graph_destroy(g);
		return NULL;
	}
	/* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for(i=0; i<nnodes;i++) {
        fgets(buff, MAX, in);
		sscanf(buff, "%d %s", &id1, name);
		/* create node */
		n = node_ini();
		if (node_setId(n, id1) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		if (node_setName(n, name) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* add node to graph */
		if (graph_addNode(g, n) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* destroy node */
		node_destroy(n);
	}
	/* read connections */
	while (!feof(in)){
        fgets(buff, MAX, in);
		sscanf(buff, "%d %d", &id1, &id2);
		if (graph_addEdge(g, id1, id2) == NULL){
			fclose (in);
			graph_destroy(g);
			return NULL;
		}
	}

	fclose (in);

	return g;
}

Bool hayCamino(Graph *g, Node *nOrig, Node *nDest){
    int numConex, *listConex, i; 
    Node *nTemp;
    Queue *q;
    if(g == NULL || nOrig == NULL || nDest == NULL) return FALSE;
    q = queue_ini(destroy_node_function, copy_node_function, print_node_function);
    if (q == NULL) return FALSE;
    
    node_setVisited(nOrig, GREY);
    queue_insert(q, nOrig);
    
    while(!queue_isEmpty(q)){
        nTemp = queue_extract(q);
        node_setVisited(nTemp, BLACK);
        numConex = graph_getNumberOfConnectionsFrom(g, node_getId(nTemp));
        listConex = graph_getConnectionsFrom(g, node_getId(nTemp));
        for(i = 0; i< numConex; i++){
            nTemp = graph_getNode(g, listConex[i]);
            if(node_getVisited(nTemp) == WHITE){
                /*Si es el nodo que buscamos, ya hemos acabado*/
                if(node_equals(nTemp, nDest)){
                    free(listConex);
                    queue_destroy(q);
                    return TRUE;
                }
                node_setVisited(nTemp, GREY);
                queue_insert(q, nTemp);
            }
        }
        free(listConex);
    }
    queue_destroy(q);
    return FALSE;
}

int main(int argc, char** argv) {
    FILE *f = NULL;
    int numNodos, i, tempId;
    char tempName[100];
    Graph *g;
    Node *nOrig, *nDest;
    
    g = read_graph_from_file(argv[1]);    
    if(g == NULL){
        fclose(f);
        return -1;
    }
    
    nOrig = graph_getNode(g, 3);
    nDest = graph_getNode(g, 1);
    if( nOrig == NULL || nDest == NULL){
        node_destroy(nOrig);
        node_destroy(nDest);
        graph_destroy(g);
        fclose(f);
        return -1;
    }
    
    if( hayCamino(g, nOrig, nDest)){
        printf("HAY CAMINO!");
    }else{
        printf("NO HAY CAMINO!");
    }
    return (EXIT_SUCCESS);
}

