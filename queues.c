/*
 * Queue powered by a doubly linked list
 */

#include "linked_lists.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    DoublyLinkedList list;
} Queue;

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
