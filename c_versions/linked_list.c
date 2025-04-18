#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR
} value_type;

typedef struct Node{
    void* val;
    value_type type;
    struct Node* next;
} Node;

typedef struct Linked_List{
    int size;

    Node* head_node;
} Linked_List;

Linked_List list;

void add(int index,value_type type, void* value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = value;
    new_node->type = type;
    Node* current = list.head_node;
    if (index == -1){
        while(current->next != NULL){
            current = current->next;
        }
        new_node->next = NULL;
        current->next = new_node;
    }else{
        int i;
        for(i = 0;i < index-1;i++){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    list.size++;
}

void pop(int index){
    int i;
    Node* current = list.head_node;
    for(i = 0;i < index-1;i++){
        current = current->next;
    }
    Node* trash = current->next;
    current->next = trash->next;
    trash->next = NULL;
    list.size--;
    free(trash);
}

void reverse(int left, int right){
    int i;
    if (list.size > 2){
        Node *current, *after;
        if (left == -1){
            left = 0;
        }
        if (right == -1){
            right = list.size-1;
        }
        current = list.head_node;
        for (i = 0;i < left;i++){
            current = current->next;
        }
        Node* const prev = current;
        Node* const start = current->next;
        current = start->next;
        for(i = 0;i < right - left;i++){
            after = current->next;
            current->next = prev->next;
            prev->next = current;
            start->next = after;
            current = after;
        }
    }else if (list.size == 2){
        Node *prev, *current;
        prev = list.head_node->next;
        current = prev->next;
        current->next = prev;
        prev->next = NULL;
        list.head_node->next = current;
    }
}

void print_list(int index){
    int i;
    if (index == -1){
        Node* current = list.head_node->next;
        for (i = 0;i < list.size;i++){
            switch (current->type){
                case TYPE_INT:
                    printf("%d -> ",*(int*)current->val);
                case TYPE_FLOAT:
                    printf("%f -> ",*(float*)current->val);
                case TYPE_CHAR:
                    printf("%c -> ",*(char*)current->val);
                case TYPE_STRING:
                    printf("%s -> ",(char*)current->val);
            }
            current = current->next;
        }
    }
}
void init_list(Linked_List* list){
    list->head_node = (Node*)malloc(sizeof(Node));
    list->head_node->next = NULL;
    list->head_node->val = NULL;
    list->size = 0;
}

int main(){
    init_list(&list);
    return 0;
}
