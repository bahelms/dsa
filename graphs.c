#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NEIGHBORS 20

typedef struct Vertex {
    char *value;
    struct Vertex *neighbors[MAX_NEIGHBORS];
    int neighborCount;
} Vertex;

Vertex *newVertex(char *value) {
    Vertex *v = malloc(sizeof(Vertex));
    v->value = value;
    v->neighborCount = 0;
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        v->neighbors[i] = NULL;
    }
    return v;
}

void addNeighbor(Vertex *v, Vertex *neighbor) {
    v->neighbors[v->neighborCount++] = neighbor;
}

// causes easy conflicts
int hashString(char *str) {
    int hash = 0;
    int idx = 0;
    char chr = str[idx];
    while (chr != '\0') {
        hash += (chr - 97) % MAX_NEIGHBORS;
        chr = str[++idx];
    }
    return hash;
}

void _dfs_traverse(Vertex *v, int visited[]) {
    visited[hashString(v->value)] = 1;
    printf("%s\n", v->value);
    for (int i = 0; i < v->neighborCount; i++) {
        Vertex *neighbor = v->neighbors[i];
        if (visited[hashString(neighbor->value)])
            continue;
        _dfs_traverse(neighbor, visited);
    }
}

// depth first traversal
void dfs_traverse(Vertex *v) {
    int visited[200]; // based on the size of a hashed Vertex value
    for (int i = 0; i < 200; i++) {
        visited[i] = 0;
    }
    _dfs_traverse(v, visited);
}

/*
 * Needed for BFS search - graph specific queues
 * */

typedef struct Node {
    Vertex *value;
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

Node *init_node(Vertex *value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insertAtEnd(DoublyLinkedList *list, Vertex *value) {
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

Vertex *removeFromFront(DoublyLinkedList *list) {
    Node *node = list->first;
    if (node == NULL) {
        return NULL;
    }

    list->first = node->next;
    if (list->first != NULL) {
        list->first->prev = NULL;
    }
    Vertex *value = node->value;
    free(node);
    return value;
}

Queue *newQueue(void) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list.first = NULL;
    queue->list.last = NULL;
    return queue;
}

void enqueue(Queue *queue, Vertex *value) { insertAtEnd(&queue->list, value); }

Vertex *dequeue(Queue *queue) { return removeFromFront(&queue->list); }

int isEmpty(Queue *queue) { return queue->list.first == NULL; }

/* End of graph queue code */

// breadth first traversal
void bfs_traverse(Vertex *v) {
    Queue *q = newQueue();
    int visited[200]; // based on the size of a hashed Vertex value
    for (int i = 0; i < 200; i++) {
        visited[i] = 0;
    }

    visited[hashString(v->value)] = 1;
    enqueue(q, v);

    while (!isEmpty(q)) {
        Vertex *current = dequeue(q);
        printf("%s\n", current->value);
        for (int i = 0; i < current->neighborCount; i++) {
            Vertex *neighbor = current->neighbors[i];
            if (visited[hashString(neighbor->value)])
                continue;
            visited[hashString(neighbor->value)] = 1;
            enqueue(q, neighbor);
        }
    }
}

int main(int argc, char *argv[]) {
    // setup graph
    Vertex *alice = newVertex("alice");
    Vertex *bob = newVertex("bob");
    Vertex *candy = newVertex("candy");
    Vertex *derek = newVertex("derek");
    Vertex *elaine = newVertex("elaine");
    Vertex *fred = newVertex("fred");
    Vertex *helen = newVertex("helen");
    Vertex *gina = newVertex("gina");
    Vertex *irena = newVertex("irena");
    addNeighbor(alice, bob);
    addNeighbor(alice, candy);
    addNeighbor(alice, derek);
    addNeighbor(alice, elaine);
    addNeighbor(bob, alice);
    addNeighbor(bob, fred);
    addNeighbor(fred, bob);
    addNeighbor(fred, helen);
    addNeighbor(helen, fred);
    addNeighbor(helen, candy);
    addNeighbor(candy, helen);
    addNeighbor(candy, alice);
    addNeighbor(derek, alice);
    addNeighbor(derek, elaine);
    addNeighbor(derek, gina);
    addNeighbor(elaine, derek);
    addNeighbor(elaine, alice);
    addNeighbor(gina, derek);
    addNeighbor(gina, irena);
    addNeighbor(irena, gina);

    puts("DFS traversal");
    dfs_traverse(alice);
    puts("\nBFS traversal");
    bfs_traverse(alice);
    return 0;
}
