#include "node.h"
#include "types.h"
#include <string.h>
#include <stdlib.h>

typedef struct _Node{
    char *name;
    int id;
    Visited visited;
};

Node  *node_ini(){
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    if(node == NULL) return NULL;   /*Se podría omitir en este caso*/
    node->visited=WHITE;
    node->name=NULL;
    return node;
}

void node_destroy(Node *n){
    if(n == NULL) return;
    if(n->name != NULL) free(n->name);
    free(n);
}

int node_getId(const Node *n){
    if(n == NULL) return -1;
    return n->id;
}

Visited node_getVisited(const Node *n){
    if(n == NULL) return WHITE;
    return n->visited;
}

char *node_getName(const Node *n){
    if(n == NULL) return NULL;
    return (char *)n->name;
}

Node *node_setId(Node *n, const int id){
    if(n == NULL) return NULL;
    n->id=id;
    return n;
}

Node *node_setVisited(Node *n, const Visited visited){
    if(n == NULL) return NULL;
    n->visited = visited;
    return n;
}

Node *node_setName(Node *n, const char *name){
    if(n == NULL) return NULL;
    n->name = (char *)malloc(sizeof(char)*(strlen(name)+1));
    if(n->name == NULL) return NULL;
    strcpy(n->name, name);
    return n;
}

/*Para comprar, copiar e imprimir el estado es indiferente*/
Bool node_equals(const Node *n1, const Node *n2){
    if(n1 == NULL || n2 == NULL) return FALSE;
    if(n1->id == n2->id && (strcmp(n1->name, n2->name) == 0)){
        return TRUE;
    }
    return FALSE;
}

int node_cmp(Node *n1, Node *n2){
    if(n1 == NULL || n2 == NULL) return -1;
    if(node_equals(n1, n2)) return 0;
    if(n1->id > n2->id) return 1;
    return -1;
}

Node *node_copy(const Node *src){
	Node *n2;
    if(src == NULL) return NULL;

    n2 = node_ini();
    if (n2 == NULL) return NULL;
    n2->id = src->id;
    n2->name = (char*)malloc(sizeof(char)* (strlen(src->name)+1));
    strcpy(n2->name, src->name);
    return n2;
}

int node_print(FILE *pf, const Node *n){
    if(pf == NULL || n == NULL) return -1;
    return fprintf(pf, "[%d, %s]", node_getId(n), node_getName(n));
}
