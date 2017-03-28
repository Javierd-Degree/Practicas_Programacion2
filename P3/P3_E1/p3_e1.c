#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"
#include "functions.h"

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *f = NULL;
    int numNodos, i, tempId;
    char tempName[100];
    Node *n;
    Queue *q1, *q2, *q3;
    
    f = fopen(argv[1], "r");
    if(f == NULL) return -1;
    
    q1 = queue_ini(destroy_node_function, copy_node_function, print_node_function);
    if(q1 == NULL){
        fclose(f);
        return -1;
    }
    q2 = queue_ini(destroy_node_function, copy_node_function, print_node_function);
    if(q2 == NULL){
        queue_destroy(q1);
        fclose(f);
        return -1;
    }
    q3 = queue_ini(destroy_node_function, copy_node_function, print_node_function);
    if(q3 == NULL){
        queue_destroy(q1);
        queue_destroy(q2);
        fclose(f);
        return -1;
    }
    
    if(queue_isEmpty(q1)){
        printf("Cola 1: Queue vacia.\n");
    }else{
        printf("Cola 1: Queue no vacia.\n");
    }
    if(queue_isEmpty(q2)){
        printf("Cola 2: Queue vacia.\n");
    }else{
        printf("Cola 2: Queue no vacia.\n");
    }
    if(queue_isEmpty(q3)){
        printf("Cola 3: Queue vacia.\n");
    }else{
        printf("Cola 3: Queue no vacia.\n");
    }
    
    fscanf(f, "%d\n", &numNodos);
    for (i = 0; i < numNodos; i++){
        n = node_ini();
        if(n == NULL) return -1;
        fscanf(f, "%d %s\n", &tempId, tempName);
        node_setName(n, tempName);
        node_setId(n, tempId);
        if(queue_insert(q1, n) == NULL) return -1;
        node_destroy(n);
        
        if (queue_isEmpty(q1)) {
            printf("Cola 1: Queue vacia.\n");
        } else {
            printf("Cola 1: cola con %d elementos.\n", queue_size(q1));
            queue_print(stdout, q1);
        }
        if (queue_isEmpty(q2)) {
            printf("Cola 2: Queue vacia.\n");
        } else {
            printf("Cola 2: cola con %d elementos.\n", queue_size(q2));
            queue_print(stdout, q2);
        }
        if (queue_isEmpty(q3)) {
            printf("Cola 3: Queue vacia.\n");
        } else {
            printf("Cola 3: cola con %d elementos.\n", queue_size(q3));
            queue_print(stdout, q3);
        }
    }
    
    printf("<<<Pasando la primera mitad de Cola 1 a Cola 2\n");
    for (i = 0; i < numNodos/2; i++){
        n = queue_extract(q1);
        if(n == NULL) return -1;
        if(queue_insert(q2, n) == NULL) return -1;
        node_destroy(n);
        
        if (queue_isEmpty(q1)) {
            printf("Cola 1: Queue vacia.\n");
        } else {
            printf("Cola 1: cola con %d elementos.\n", queue_size(q1));
            queue_print(stdout, q1);
        }
        if (queue_isEmpty(q2)) {
            printf("Cola 2: Queue vacia.\n");
        } else {
            printf("Cola 2: cola con %d elementos.\n", queue_size(q2));
            queue_print(stdout, q2);
        }
        if (queue_isEmpty(q3)) {
            printf("Cola 3: Queue vacia.\n");
        } else {
            printf("Cola 3: cola con %d elementos.\n", queue_size(q3));
            queue_print(stdout, q3);
        }
    }
    
    printf("<<<Pasando la segunda mitad de Cola 1 a Cola 3\n");
    for (i = 0; i < (numNodos- numNodos/2); i++){
        n = queue_extract(q1);
        if(n == NULL) return -1;
        if(queue_insert(q3, n) == NULL) return -1;
        node_destroy(n);
        
        if (queue_isEmpty(q1)) {
            printf("Cola 1: Queue vacia.\n");
        } else {
            printf("Cola 1: cola con %d elementos.\n", queue_size(q1));
            queue_print(stdout, q1);
        }
        if (queue_isEmpty(q2)) {
            printf("Cola 2: Queue vacia.\n");
        } else {
            printf("Cola 2: cola con %d elementos.\n", queue_size(q2));
            queue_print(stdout, q2);
        }
        if (queue_isEmpty(q3)) {
            printf("Cola 3: Queue vacia.\n");
        } else {
            printf("Cola 3: cola con %d elementos.\n", queue_size(q3));
            queue_print(stdout, q3);
        }
    }
    
    queue_destroy(q1);
    queue_destroy(q2);
    queue_destroy(q3);
    fclose(f);
    return (EXIT_SUCCESS);
}

