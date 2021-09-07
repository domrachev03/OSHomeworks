#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

struct Node* initialize_list() {
    return 0;
}

struct Node* predecessor_node(struct Node *list, int pos) {
    struct Node *predecessor = list;
    int cur_pos = 0;
    
    while (cur_pos < pos-1 && predecessor) {
        cur_pos += 1;
        predecessor = predecessor->next;
    }
    
    if(!predecessor || pos <= 0) {
        
        return 0;
    }

    return predecessor;
}

struct Node* insert_node(struct Node **list, int pos, int value){
    if(!*list) {
        *list = (struct Node*) malloc(sizeof(struct Node));
        (*list)->next = 0;
        (*list)->value = value;
        return *list;
    }
   
    struct Node *predecessor = predecessor_node(*list, pos);
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    
    new_node->value = value;
    if(predecessor) { 
        new_node->next = predecessor->next;
        predecessor->next = new_node;
    }
    else {
        new_node->next = *list;
        *list = new_node;
    }

    return new_node;
}

void remove_node(struct Node **list, int pos) {
    struct Node* predecessor = predecessor_node(*list, pos);
    struct Node* deleted = (predecessor) ? predecessor->next : *list;
    
    if (predecessor) {
        predecessor->next = deleted->next;        
    } else {
        *list = deleted->next;
    }
    
    free(deleted);
}

void print_list(struct Node *list) {
    struct Node* cur_pos = list;
    while(cur_pos) {
        printf("%d ", cur_pos->value);
        cur_pos = cur_pos->next;
    }
    printf("\n");
}

int main() { 
    struct Node *linked_list = initialize_list();
    
    for(int i = 0; i < 10; ++i) {
        insert_node(&linked_list, i, i);
        print_list(linked_list);
    }
    
    for(int i = 0; i < 5; ++i) {
        remove_node(&linked_list, 0);
        print_list(linked_list);
    }
}
