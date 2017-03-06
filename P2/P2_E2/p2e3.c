#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"
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




int recorrer_grafo (Graph *g, Node *n){
    Stack *s;
    int desc[MAX_NODES],*listconex,i,j,k;
    j=0;
    s= stack_ini();
    stack_push(s,n);
    listconex=graph_getConnectionsTo(g,node_getId(n));
    for(i=0;listconex[i]!= 0; i++){ 
            for(k=0;desc[k]!=0;k++){
                if(desc[k]==listconex[i]) break;
            }
            for(k=0;stack_isEmpty == FALSE;k++){
                Node *n1;
                n1= stack_pop(s);
                if(listconex[i]==n1)break;
            }
            stack_push(s,listconex[i]);
        } 
    while(stack_isEmpty == FALSE){
        Node *n;
        n=stack_pop(s);
        for(i=0;desc[i]!=0;i++){
            if(desc[i]!=node_getId(n)) desc[j]= node_getId(n);
            j++;
        }
        listconex=graph_getConnectionsTo(g,node_getId(n));
        for(i=0;listconex[i]!= 0; i++){ 
            for(k=0;desc[k]!=0;k++){
                if(desc[k]==listconex[i]) break;
            }
            for(k=0;stack_isEmpty == FALSE;k++){
                Node *n1;
                n1= stack_pop(s);
                if(listconex[i]==n1)break;
            }
            stack_push(s,listconex[i]);
        }   
    }
    if(graph_getNnodes(g)== j)return 0;
    return -1;
}