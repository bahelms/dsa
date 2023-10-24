#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *insert(int value, Node *node) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    node->next = new_node;
    return new_node;
}

int read(Node *node, int index) {
    Node *current_node = node;
    int current_idx = 0;
    while (current_idx < index) {
        current_node = current_node->next;
        current_idx++;
        if (current_node == NULL) {
            printf("Index %d is out of bounds\n", index);
            exit(0);
        }
    }
    return current_node->value;
}

int main(int argc, char *argv[]) {
    Node head;
    head.value = 1;
    head.next = NULL;

    insert(2, &head);
    insert(3, head.next);
    insert(4, head.next->next);

    printf("Value at index 3: %d\n", read(&head, 3));
    printf("Value at index 4: %d\n", read(&head, 4));
    return 0;
}
