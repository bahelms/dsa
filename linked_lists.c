#include "linked_lists.h"
#include <stdio.h>
#include <stdlib.h>

Node *init_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
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
    Node *new_node = init_node(value);
    node->next = new_node;
    return new_node;
}

Node *insert_at(Node *node, int value, int index) {
    if (index == 0) {
        Node *new_node = init_node(value);
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

// Reverse a linked list
Node *reverse(Node *node) {
    Node *next, *prev = NULL;

    while (node != NULL) {
        next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
    return prev;
}

void print_list(Node *node) {
    printf("[");
    do {
        printf("%d,", node->value);
        node = node->next;
    } while (node != NULL);
    puts("]");
}

void insert_at_end(DoublyLinkedList *list, int value) {
    Node *node = init_node(value);
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }
}

int remove_from_front(DoublyLinkedList *list) {
    Node *node = list->first;
    if (node == NULL) {
        return -1;
    }

    list->first = node->next;
    if (list->first != NULL) {
        list->first->prev = NULL;
    }
    int value = node->value;
    free(node);
    return value;
}
