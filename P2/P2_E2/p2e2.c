#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"
#include "stack.h"

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

int format_graph(const Graph * g, Stack *p) {
    int i, j, nNodes, numConexTo, numConexFrom;
    int *ids, *conex;

    if(g == NULL || p == NULL) return -1;
    
    ids = graph_getNodeIds(g);
    nNodes = graph_getNnodes(g);

    for (i = 0; i < nNodes; i++) {
        numConexTo = graph_getNumberOfConnectionsTo(g, ids[i]);
        numConexFrom = graph_getNumberOfConnectionsFrom(g, ids[i]);

        Element *e;
        /*Miramos las conexiones entrantes*/
        conex = graph_getConnectionsTo(g, ids[i]);
        for (j = 0; j < numConexTo; j++) {
            e = element_ini();
            element_setInfo(e, graph_getNode(g, conex[j]));
            stack_push(p, e);
            element_destroy(e); /*Como push hace una copia, liberamos*/
        }

        free(conex);
        /*Miramos las conexiones salientes*/
        conex = graph_getConnectionsFrom(g, ids[i]);
        for (j = 0; j < numConexFrom; j++) {
            e = element_ini();
            element_setInfo(e, graph_getNode(g, conex[j]));
            stack_push(p, e);
            element_destroy(e); /*Como push hace una copia, liberamos*/
        }
        free(conex);
    }
}

int main(int argc, char** argv) {

    Graph * g = NULL;
    Stack *s = NULL;

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

    format_graph(g, s);
    stack_print(stdout, s);

    graph_destroy(g);
    stack_destroy(s);

    return (EXIT_SUCCESS);
}

