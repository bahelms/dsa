#include "arrays.h"
#include <stdio.h>

#define HEAP_CAPACITY 100

typedef struct BinaryHeap {
    int data[HEAP_CAPACITY];
    int last_node;
    int count;
} BinaryHeap;

int left_child_index(int index) { return index * 2 + 1; }
int right_child_index(int index) { return index * 2 + 2; }
int parent_index(int index) { return (index - 1) / 2; }

void insert(BinaryHeap *heap, int value) {
    heap->count++;
    heap->last_node++;
    heap->data[heap->last_node] = value;

    int trickle_index = heap->last_node;
    int parent_node = parent_index(trickle_index);
    while (value > heap->data[parent_node]) {
        swapValue(heap->data, parent_node, trickle_index);
        trickle_index = parent_node;
        parent_node = parent_index(trickle_index);
    }
}

void delete_node(BinaryHeap *heap) {
    int index = 0;
    heap->data[index] = heap->data[heap->last_node];
    heap->last_node--;
    heap->count--;

    while (1) {
        int child_index = left_child_index(index);
        int child = heap->data[child_index];
        int right = heap->data[right_child_index(index)];
        if (right > child) {
            child = right;
            child_index = right_child_index(index);
        }

        if (heap->data[index] < child) {
            heap->data[child_index] = heap->data[index];
            heap->data[index] = child;
            index = child_index;
        } else {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    BinaryHeap heap;
    heap.last_node = -1;
    heap.count = 0;

    insert(&heap, 100);
    insert(&heap, 88);
    insert(&heap, 25);
    insert(&heap, 87);
    insert(&heap, 16);
    insert(&heap, 8);
    insert(&heap, 12);
    insert(&heap, 86);
    insert(&heap, 50);
    insert(&heap, 2);
    insert(&heap, 15);
    insert(&heap, 3);
    insert(&heap, 40);
    printArray(heap.data, heap.count);

    puts("Deleting root node");
    delete_node(&heap);
    printArray(heap.data, heap.count);
    printf("Last node: %d\n", heap.data[heap.last_node]);

    return 0;
}
