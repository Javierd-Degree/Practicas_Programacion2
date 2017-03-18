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


Status ejercicio1(Graph *g, Node *n){
    Stack *s;
    Node *tempN;
    Element *tempEle, *procEle;
    int *listConex, numConex, aDesc[MAX_NODES], numDesc = 0, i;
    
    if(g == NULL || n==NULL) return ERROR;
    s = stack_ini();
    if (s == NULL) return ERROR;
    
    /*Insertamos el elemento inicial*/
    procEle = element_ini();
    if(procEle == NULL) return ERROR;
    element_setInfo(procEle, n);

    stack_push(s, procEle);
    element_destroy(procEle);
 
    while(!stack_isEmpty(s)){
        procEle = stack_pop(s);
        numConex = graph_getNumberOfConnectionsFrom(g, node_getId(element_getInfo(procEle)));
        listConex = graph_getConnectionsFrom(g, node_getId(element_getInfo(procEle)));
        
            for(i = 0; i<numConex; i++){
                tempN = graph_getNode(g, listConex[i]);
                if(node_getVisited(tempN) != BLACK){
                    tempEle = element_ini();
                    node_setVisited(tempN, GREY);
                    element_setInfo(tempEle, tempN);
                    stack_push(s, tempEle);
                    element_destroy(tempEle);
                }
            }
        
        free(listConex);
        /*Cogemos el nodo del grafo, no la copia que obtenemos al hacer stack pop*/
        tempN = graph_getNode(g, node_getId(element_getInfo(procEle))); 
        node_setVisited(tempN, BLACK);
        printf("Nodo %d visitado y descubierto\n", node_getId(tempN));
        element_destroy(procEle);
    }
    stack_destroy(s);
    return OK;
}

Bool ejercicio2(Graph *g, Node *n, Node *nDestino){
    Stack *s;
    Node *tempN;
    Element *tempEle, *procEle;
    int *listConex, numConex, aDesc[MAX_NODES], numDesc = 0, i;
    
    if(g == NULL || n==NULL) return ERROR;
    s = stack_ini();
    if (s == NULL) return ERROR;
    
    /*Insertamos el elemento inicial*/
    procEle = element_ini();
    if(procEle == NULL) return ERROR;
    element_setInfo(procEle, n);

    stack_push(s, procEle);
    element_destroy(procEle);
 
    while(!stack_isEmpty(s)){
        procEle = stack_pop(s);
        numConex = graph_getNumberOfConnectionsFrom(g, node_getId(element_getInfo(procEle)));
        listConex = graph_getConnectionsFrom(g, node_getId(element_getInfo(procEle)));
        
            for(i = 0; i<numConex; i++){
                tempN = graph_getNode(g, listConex[i]);
                if(node_equals(tempN, nDestino)){
                        return TRUE; /*Hay alguna forma de llegar*/
                }
                if(node_getVisited(tempN) != BLACK){
                    tempEle = element_ini();
                    node_setVisited(tempN, GREY);
                    element_setInfo(tempEle, tempN);
                    stack_push(s, tempEle);
                    element_destroy(tempEle);
                }
            }
        
        free(listConex);
        /*Cogemos el nodo del grafo, no la copia que obtenemos al hacer stack pop*/
        tempN = graph_getNode(g, node_getId(element_getInfo(procEle))); 
        node_setVisited(tempN, BLACK);
        element_destroy(procEle);
    }
    stack_destroy(s);
    return OK;
}

int main(int argc, char** argv) {
    Graph * g = NULL;
    Stack *s = NULL;
    Node *n = NULL, *nDestino = NULL;

    if (argc < 2) {
        fprintf(stdout, "Not enough parameters: %d\n", argc);
        return -1;
    }

    g = read_graph_from_file(argv[1]);
    s = stack_ini();
    if (s == NULL) {
        graph_destroy(g);
        return -1;
    }
    
    n = graph_getNode(g, 1);
    if (n == NULL) {
        graph_destroy(g);
        stack_destroy(s);
        return -1;
    }
    
    nDestino = graph_getNode(g, 4);
    if (nDestino == NULL) {
        graph_destroy(g);
        stack_destroy(s);
        printf("Nodo destino no disponible");
        return -1;
    }
    
    printf("Ejercicio 1\n");
    ejercicio1(g, n);
    printf("Ejercicio 2\n");
    if( ejercicio2(g, n, nDestino) == TRUE ){
        printf("Nodo con id %d accesible", node_getId(nDestino));
    }else{
        printf("Nodo con id %d no accesible", node_getId(nDestino));
    }
    
    return (EXIT_SUCCESS);
}

/*int recorrer_grafo (Graph *g, Node *n){
    Stack *s;
    int desc[MAX_NODES],*listconex,i,j,k;
    j=0;
    s= stack_ini();
    stack_push(s,n);
    listconex = graph_getConnectionsFrom(g, node_getId(n));
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
}*/