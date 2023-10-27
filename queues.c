/*
 * Queue powered by a doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DoublyLinkedList {
    struct Node *first;
    struct Node *last;
} DoublyLinkedList;

typedef struct Queue {
    DoublyLinkedList list;
} Queue;

Node *init_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
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

Queue *new_queue(void) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list.first = NULL;
    queue->list.last = NULL;
    return queue;
}

void enqueue(Queue *queue, int value) { insert_at_end(&queue->list, value); }

int dequeue(Queue *queue) { return remove_from_front(&queue->list); }

int main(int argc, char *argv[]) {
    Queue *queue = new_queue();

    enqueue(queue, 42);
    enqueue(queue, 13);
    enqueue(queue, 56);

    printf("Dequeued value: %d\n", dequeue(queue));
    printf("Dequeued value: %d\n", dequeue(queue));
    printf("Dequeued value: %d\n", dequeue(queue));
    printf("Dequeued value: %d\n", dequeue(queue));
    return 0;
}
