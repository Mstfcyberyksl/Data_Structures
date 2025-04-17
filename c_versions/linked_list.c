#include <stdlib.h>

typedef struct Node{
    void* val;
    struct Node* next;
} Node;

typedef struct Linked_List{
    int size;
    Node* head_node;
} Linked_List;

Linked_List list;

void add(int index,void* value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = value;
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
}

void pop(int index){
    int i;
    Node* current = list.head_node;
    for(i = 0;i < index-1;i++){
        current = current->next;
    }
    Node* trash = current;
    trash = trash->next;
    current->next = trash->next;
    trash->next = NULL;
    free(trash);
}

void reverse(int left, int right){
    int i;
    if (list.size > 2){
        Node *prev, *current, *after;
        if (left == -1){
            left = 0;
        }
        if (right == -1){
            right = list.size;
        }

        prev = list.head_node->next;
        current = prev->next;
        after = current->next;
        for (i = 0;i < left;i++){
            prev = current;
            current = after;
            after = after->next;
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
int main(){
    list.head_node->next = NULL;
    list.head_node->val = NULL;
}
