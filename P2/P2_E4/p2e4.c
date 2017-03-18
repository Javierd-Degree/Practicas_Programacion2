#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"
#include "stack_fp.h"
#include "functions.h"

#define MAX 255

Graph * read_graph_from_file(char * filename) {
    FILE * in;
    Graph * g;
    Node * n;
    char buff[MAX], name[MAX];
    int i, nnodes, id1, id2;

    g = graph_ini();
    if (g == NULL) {
        return NULL;
    }
    in = (FILE*) fopen(filename, "r");
    if (in == NULL) {
        graph_destroy(g);
        return NULL;
    }
    /* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for (i = 0; i < nnodes; i++) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %s", &id1, name);
        /* create node */
        n = node_ini();
        if (node_setId(n, id1) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        if (node_setName(n, name) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* add node to graph */
        if (graph_addNode(g, n) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* destroy node */
        node_destroy(n);
    }
    /* read connections */
    while (!feof(in)) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %d", &id1, &id2);
        if (graph_addEdge(g, id1, id2) == NULL) {
            fclose(in);
            graph_destroy(g);
            return NULL;
        }
    }

    fclose(in);

    return g;
}

int format_graph(const Graph * g, Stack *sNode, Stack *sInt) {
    int i, j, nNodes, numConexTo, numConexFrom;
    int *ids, *conex, nodeId;

    if(g == NULL || sNode == NULL || sInt == NULL) return -1;
    
    ids = graph_getNodeIds(g);
    nNodes = graph_getNnodes(g);

    for (i = 0; i < nNodes; i++) {
        numConexTo = graph_getNumberOfConnectionsTo(g, ids[i]);
        numConexFrom = graph_getNumberOfConnectionsFrom(g, ids[i]);

        /*Miramos las conexiones entrantes*/
        conex = graph_getConnectionsTo(g, ids[i]);
        for (j = 0; j < numConexTo; j++) {
            nodeId = node_getId(graph_getNode(g, conex[j]));
            stack_push(sNode, graph_getNode(g, conex[j]));
            stack_push(sInt, &nodeId);
        }

        free(conex);
        /*Miramos las conexiones salientes*/
        conex = graph_getConnectionsFrom(g, ids[i]);
        for (j = 0; j < numConexFrom; j++) {
            nodeId = node_getId(graph_getNode(g, conex[j]));
            stack_push(sNode, graph_getNode(g, conex[j]));
            stack_push(sInt, &nodeId);
        }
        free(conex);
    }
}

int main(int argc, char** argv) {
    Graph * g = NULL;
    Stack *sNode = NULL, *sInt = NULL;

    if (argc < 2) {
        fprintf(stdout, "Not enough parameters: %d\n", argc);
        return -1;
    }
    g = read_graph_from_file(argv[1]);
    
    sNode = stack_ini(destroy_node_function, copy_node_function, print_node_function);
    if (sNode == NULL) {
        graph_destroy(g);
        return -1;
    }
    
    sInt = stack_ini(destroy_intp_function, copy_intp_function, print_intp_function);
    if (sInt == NULL) {
        graph_destroy(g);
        stack_destroy(sNode);
        return -1;
    }

    format_graph(g, sNode, sInt);
    printf("Pila de enteros:\n");
    stack_print(stdout, sInt);
    printf("Pila de nodos:\n");
    stack_print(stdout, sNode);

    graph_destroy(g);
    stack_destroy(sNode);
    stack_destroy(sInt);

    return (EXIT_SUCCESS);
}

