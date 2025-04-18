#include <stddef.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    NONE
} value_type;

typedef struct Node{
    int val;
    value_type type;
    struct Node* right;
    struct Node* left;
}Node;

typedef struct min_heap{
    int size;
    Node* root;
} min_heap;

min_heap* init_heap(){
    min_heap* heap = (min_heap*)malloc(sizeof(min_heap));
    heap->root->type = NONE;
    heap->root->left = NULL;
    heap->root->right = NULL;
    heap->size = 0;
    return heap;
}

min_heap* to_min_heap(int* vals){
    min_heap* heap = (min_heap*)malloc(sizeof(min_heap));

    return heap;
}

void add(min_heap* heap, int value){

}
