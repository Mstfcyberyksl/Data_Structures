#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    NONE
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

void init_list(Linked_List* list){
    list->head_node = (Node*)malloc(sizeof(Node));
    list->head_node->next = NULL;
    list->head_node->val = NULL;
    list->head_node->type = NONE;
    list->size = 0;
}

void add(Linked_List* list,int index,value_type type, void* value){
    if (list->size >= index){
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->type = type;
        switch (type){
            case TYPE_INT:
                new_node->val = malloc(sizeof(int));
                *(int*)new_node->val = *(int*)value;
                break;
            case TYPE_FLOAT:
                new_node->val = malloc(sizeof(float));
                *(float*)new_node->val = *(float*)value;
                break;
            case TYPE_CHAR:
                new_node->val = malloc(sizeof(char));
                *(char*)new_node->val = *(char*)value;
                break;
            case TYPE_STRING:
                new_node->val = malloc((strlen((char*)value) + 1) * sizeof(char));
                strcpy((char*)new_node->val, (char*)value);
                break;
            default:
                printf("TYPE ERROR: INVALID DATA TYPE\n");
                break;
        }

        Node* current = list->head_node;
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
        list->size++;
    }else{
        printf("INDEX ERROR: INVALID INDEX\n");
    }
}

void change(int index, value_type type, void* val){
    if (list.size > index){
        int i;
        Node* current = list.head_node->next;
        for (i = 0; i < index;i++){
            current = current->next;
        }
        free(current->val);
        current->val = val;
        current->type = type;
    }else{
        printf("INDEX ERROR: INVALID INDEX\n");
    }
}

float sum(){
    int i;
    float result = 0.0f;
    Node* current = list.head_node->next;
    for (i = 0;i < list.size;i++){
        if (current->type == TYPE_INT){
            result += *(int*)current->val;
        }else if (current->type == TYPE_FLOAT){
            result += *(float*)current->val;
        }
        current = current->next;
    }
    return result;
}

void pop(Linked_List* list, int index){
    if(list->size > index){
        int i;
        Node* current = list->head_node;
        Node* trash = current->next;
        for(i = 0;i < index;i++){
            current = current->next;
        }
        trash = current->next;
        current->next = trash->next;
        trash->next = NULL;
        list->size--;
        free(trash->val);
        free(trash);
    }else{
        printf("INDEX ERROR: INVALID INDEX\n");
    }
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
    Node* current = list.head_node->next;
    if (index == -1){
        for (i = 0;i < list.size;i++){
            switch (current->type){
                case TYPE_INT:
                    printf("%d -> ",*(int*)current->val);
                    break;
                case TYPE_FLOAT:
                    printf("%f -> ",*(float*)current->val);
                    break;
                case TYPE_CHAR:
                    printf("%c -> ",*(char*)current->val);
                    break;
                case TYPE_STRING:
                    printf("%s -> ",(char*)current->val);
                    break;
                default:
                    printf("Unknown type");
                    break;
            }
            current = current->next;
        }
    }else if (list.size > index){
        for(i = 0;i < index;i++){
            current = current->next;
        }
        switch (current->type){
            case TYPE_INT:
                printf("%d",*(int*)current->val);
                break;
            case TYPE_FLOAT:
                printf("%f",*(float*)current->val);
                break;
            case TYPE_CHAR:
                printf("%c",*(char*)current->val);
                break;
            case TYPE_STRING:
                printf("%s",(char*)current->val);
                break;
            default:
                printf("Unknown type");
                break;
        }
    }else{
        printf("INDEX ERROR: INVALID INDEX");
    }
}

void free_list(){
    int i;
    Node *current, *after;
    current = list.head_node;
    for(i = 0;i < list.size+1;i++){
        after = current->next;
        if (current->val != NULL){
            free(current->val);
        }
        free(current);
        current = after;
    }
}

int find(value_type type, void* val){
    int i;
    Node* current = list.head_node->next;
    if (type == TYPE_STRING){
        for(i = 0;i < list.size;i++){
            if (strcmp((char*)val, current->val) == 0){
                return i;
            }
            current = current->next;
        }
    }
    for(i = 0;i < list.size;i++){
        if (current->type == type && current->val == val){
            return i;
        }
        current = current->next;
    }
    return -1;
}

// TODO: DON'T FORGET TO COMPARE VALUES INSTEAD OF POINTERS IN del AND find FUNCTIONS

void del(Linked_List* list, value_type type, void* val){
    int i;
    Node* current = list->head_node->next;
    for(i = 0;i < list->size;i++){
        if(current->type == type && current->val == val){
            pop(list,i);
            break;
        }
    }
}

void** to_array(Linked_List* list){
    int i;
    Node* current = list->head_node->next;
    void** result;
    result = (void**)malloc(list->size * sizeof(void*));
    for(i = 0;i < list->size;i++){
        result[i] = current->val;
        current = current->next;
    }
    return result;
}

Linked_List merge(Linked_List* list1, Linked_List* list2){
    int i;
    Node* current = list1->head_node->next;
    for(i = 0;i < list1->size-1;i++){
        current = current->next;
    }
    current->next = list2->head_node->next;

    free(list2->head_node);
    return *list1;
}
Linked_List copy(Linked_List* list){
    int i;
    Linked_List result;
    init_list(&result);

    Node* from = list->head_node->next;

    for (i = 0;i < list->size;i++){
        add(&result,-1,from->type,from->val);
    }
    return result;
}

Linked_List filter(value_type type){
    Linked_List result;
    init_list(&result);
    int i;
    Node* current = list.head_node->next;
    for(i = 0;i < list.size;i++){
        if(current->type == type){
            add(&result,-1,type,current->val);
        }
    }
    return result;
}
