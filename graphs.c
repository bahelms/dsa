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

// this creates easy collisions - candy and irena are both 42
int hashString(char *str) {
    int hash = 0;
    int idx = 0;
    char chr = str[idx];
    while (chr != '\0') {
        hash += chr - 97;
        chr = str[++idx];
    }
    return hash;
}

void _traverse(Vertex *v, int visited[]) {
    visited[hashString(v->value)] = 1;
    printf("%s\n", v->value);
    for (int i = 0; i < v->neighborCount; i++) {
        Vertex *neighbor = v->neighbors[i];
        if (visited[hashString(neighbor->value)])
            continue;
        _traverse(neighbor, visited);
    }
}

// depth first search
void traverse(Vertex *v) {
    int visited[200]; // based on the size of a hashed Vertex value
    for (int i = 0; i < 200; i++) {
        visited[i] = 0;
    }
    _traverse(v, visited);
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
    Vertex *irena = newVertex("irene");
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

    traverse(alice);
    return 0;
}
