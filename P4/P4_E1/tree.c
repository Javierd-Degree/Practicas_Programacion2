#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#define ROOT(T) (T)->root
#define RIGHT(T) (T)->right
#define LEFT(T) (T)->left
#define INFO(N) (N)->info

typedef struct _NodeBT {
void* info;
struct _NodeBT* left;
struct _NodeBT* right;
} NodeBT;

struct _Tree {
NodeBT *root;
destroy_elementtree_function_type destroy_element_function;
copy_elementtree_function_type copy_element_function;
print_elementtree_function_type print_element_function;
cmp_elementtree_function_type cmp_element_function;
};

Tree * tree_ini( destroy_elementtree_function_type f1,
copy_elementtree_function_type f2,
print_elementtree_function_type f3,
cmp_elementtree_function_type f4){
    Tree *t;
    if(f1 == NULL || f2 == NULL || f3 == NULL || f4 ==  NULL) return NULL;
    t = (Tree*)malloc(sizeof(Tree));
    if(t==NULL) return NULL;
    t->cmp_element_function = f4;
    t->copy_element_function = f2;
    t ->destroy_element_function = f1;
    t->print_element_function = f3;
    t->root = NULL;
}

NodeBT *nodeBT_ini(Tree *pa, void *info){
    NodeBT *n = NULL;
    if(info == NULL) return NULL;
    n = (NodeBT*)malloc(sizeof(NodeBT));
    if (n == NULL) return NULL;
    n->info = pa->copy_element_function(info);
    if(n->info == NULL){
        free(NodeBT);
        return NULL;
    }
    RIGHT(N) = NULL;
    LEFT(N) = NULL;
}

void tree_destroy(Tree* pa){
    if(pa == NULL) return NULL;
    tree_destroy_rec(ROOT(pa));
    free(pa);
}

void tree_destroy_rec(NodeBT* n, Tree* pa){
    if(n == NULL) return;
    tree_destroy_rec(RIGHT(n));
    tree_destroy_rec(LEFT(n));
    pa->destroy_element_function(INFO(n));
    free(n);
}

Status tree_insert(Tree* pa, const void* po){
    if(pa == NULL || po == NULL) return ERROR;
    
    return tree_insert_rec(pa, po, ROOT(pa));
}

Status tree_insert_rec(Tree* pa, const void* po, NodeBT *n){
    int cmp;
    if(pa == NULL || po == NULL) return NULL;
    
    if(n == NULL){
        n = nodeBT_ini(pa, po);
        if(n == NULL) return ERROR;
        return OK;
    }
    
    cmp = pa->cmp_element_function(po, n);
    if(cmp == -1) return tree_insert_rec(pa, po, LEFT(pa));
    if(cmp == 1) return tree_insert_rec(pa, po, RIGHT(pa));
    return OK;  /*Ya está insertado*/
}

Bool tree_find(Tree* pa, const void* po){
    if(pa == NULL || po == NULL) return FALSE;
    if(pa->cmp_element_function(po, ROOT(pa)) == 0) return TRUE;
    return tree_find_rec(pa, po, ROOT(pa));
}

tree_find_rec(Tree* pa, const void* po, const NodeBT *n){
    if(pa == NULL || po == NULL || n == NULL) return FALSE;
    if(pa->cmp_element_function(po, INFO(n)) == 0) return TRUE;
    if(pa->cmp_element_function(po, INFO(n)) == 1)
        return tree_find_rec(pa, po, RIGHT(n));
    if(pa->cmp_element_function(po, INFO(n)) == -1)
        return tree_find_rec(pa, po, LEFT(n));
}

Bool tree_isEmpty( const Tree* pa){
    if(pa == NULL) return TRUE;
    if(ROOT(pa) == NULL) return TRUE;
    return FALSE;
}

int tree_numNodes(const Tree* pa){
    if(tree_isEmpty(pa)) return 0;
    return tree_numNodes_rec(pa, ROOT(pa));
}

int tree_numNodes_rec(const Tree *pa, NodeBT *n){
    int nRight, nLeft;
    if (pa == NULL || n == NULL) return 0;
    
    nRight = tree_numNodes_rec(pa, RIGHT(n));
    nLeft = tree_numNodes_rec(pa, LEFT(n));
    
    return nRight + nLeft + 1;  /*Los nodos de su derecha, los de su izquierda y el mismo*/
}

int tree_depth(const Tree* pa){
    if(tree_isEmpty(pa)) return 0;
    return tree_depth_rec(pa, ROOT(pa));
}

int tree_depth_rec(const Tree *pa, NodeBT *n){
    int nRight, nLeft;
    if (pa == NULL || n == NULL) return 0;
    
    nRight = tree_depth_rec(pa, RIGHT(n));
    nLeft = tree_depth_rec(pa, LEFT(n));
    if(nRight > nLeft) return nRight + 1;
    
    return nLeft + 1;
    
}