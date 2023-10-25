#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *init(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Node *access(Node *node, int index) {
    Node *current_node = node;
    int current_idx = 0;
    while (current_idx < index) {
        current_node = current_node->next;
        current_idx++;
        if (current_node == NULL) {
            break;
        }
    }
    return current_node;
}

Node *insert_after(int value, Node *node) {
    Node *new_node = init(value);
    node->next = new_node;
    return new_node;
}

Node *insert_at(Node *node, int value, int index) {
    if (index == 0) {
        Node *new_node = init(value);
        new_node->next = node;
        return new_node;
    }

    Node *current_node = access(node, index - 1);
    if (current_node == NULL) {
        printf("Index %d is out of bounds\n", index);
        exit(0);
    }
    Node *tail = current_node->next;
    Node *new_node = insert_after(value, current_node);
    new_node->next = tail;
    return node;
}

Node *delete_at(Node *node, int index) {
    if (index == 0) {
        Node *head = node->next;
        free(node);
        return head;
    }

    Node *current_node = access(node, index - 1);
    if (current_node == NULL) {
        printf("Index %d is out of bounds\n", index);
        exit(0);
    }

    Node *node_to_delete = current_node->next;
    if (node_to_delete == NULL) {
        printf("Index %d is out of bounds\n", index);
        exit(0);
    }

    Node *tail = node_to_delete->next;
    current_node->next = tail;
    free(node_to_delete);
    return node;
}

int read(Node *node, int index) {
    Node *current_node = access(node, index);
    if (current_node == NULL) {
        printf("Index %d is out of bounds\n", index);
        exit(0);
    }
    return current_node->value;
}

int index_of(Node *node, int value) {
    int index = 0;
    while (node->value != value) {
        node = node->next;
        index++;
        if (node == NULL) {
            return -1;
        }
    }
    return index;
}

void print_list(Node *node) {
    printf("[");
    do {
        printf("%d,", node->value);
        node = node->next;
    } while (node != NULL);
    puts("]");
}

int main(int argc, char *argv[]) {
    Node *head = init(1);
    insert_after(2, head);
    insert_after(3, head->next);
    insert_after(4, head->next->next);

    printf("Value at index 3: %d\n", read(head, 3));
    printf("Index of 3: %d\n", index_of(head, 3));

    print_list(head);
    head = insert_at(head, 5, 2);
    print_list(head);
    head = insert_at(head, 6, 0);
    print_list(head);

    head = delete_at(head, 0);
    print_list(head);
    head = delete_at(head, 2);
    print_list(head);

    return 0;
}
