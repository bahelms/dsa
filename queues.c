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

void insert_at_end(DoublyLinkedList *list, Node *node) {
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }
}

Queue *new_queue(void) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list.first = NULL;
    queue->list.last = NULL;
    return queue;
}

void enqueue(Queue *queue, int value) {
    Node *node = init_node(value);
    insert_at_end(&queue->list, node);
}

int dequeue(Queue *queue) {
    Node *node = queue->list.first;
    if (node == NULL) {
        return -1;
    }

    queue->list.first = node->next;
    if (queue->list.first != NULL) {
        queue->list.first->prev = NULL;
    }
    int value = node->value;
    free(node);
    return value;
}

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
