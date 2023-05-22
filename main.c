#include <stdio.h>
#include <stdlib.h>

#define NODE_DEF(T) struct Node_##T { T data; struct Node_##T* next; }
#define NODE(T) struct Node_##T
// #define NODE(T) struct Node_##T { T data; struct Node_##T* next; }
#define MAPCAR(T, head, func) mapcar_##T(head, func)

NODE_DEF(int);

NODE(int)* mapcar_int(NODE(int)* head, int (*func)(int)) {
    NODE(int)* current = head;
    NODE(int)* new_head = NULL;
    NODE(int)* new_current = NULL;

    while (current != NULL) {
        NODE(int)* new_node = (NODE(int)*) malloc(sizeof(NODE(int)));
        new_node->data = func(current->data);
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
            new_current = new_head;
        } else {
            new_current->next = new_node;
            new_current = new_current->next;
        }

        current = current->next;
    }

    return new_head;
}

NODE(int)* create_node_int(int data) {
    NODE(int)* node = (NODE(int)*) malloc(sizeof(NODE(int)));
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list_int(NODE(int)* head) {
    NODE(int)* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int square(int x) {
    return x * x;
}

void free_list_int(NODE(int)* head) {
    NODE(int)* current = head;
    while (current != NULL) {
        NODE(int)* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    NODE(int)* list = create_node_int(1);
    list->next = create_node_int(2);
    list->next->next = create_node_int(3);

    printf("Original list: ");
    print_list_int(list);

    NODE(int)* new_list = MAPCAR(int, list, square);
    printf("New list: ");
    print_list_int(new_list);

    free_list_int(list);
    free_list_int(new_list);

    return 0;
}
