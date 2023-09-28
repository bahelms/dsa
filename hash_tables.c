/*
 * Chapter 8 - A Common-Sense Guide to Data Structures and Algorithms
 * */

#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>

void findIntersections();
void findDuplicate();
int *initHashTable(int);

int main(int argc, char *argv[]) {
    findIntersections();
    findDuplicate();
    return 0;
}

int *initHashTable(int length) {
    int *table = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        table[i] = 0;
    }
    return table;
}

// Exercise 1 - O(N)
void findIntersections() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {0, 2, 4, 6, 8};
    int i;
    int *table = initHashTable(26);

    int intersection[10];
    for (i = 0; i < 10; i++) {
        intersection[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        table[arr1[i]] = 1;
    }

    int idx = 0;
    for (i = 0; i < 5; i++) {
        if (table[arr2[i]]) {
            intersection[idx] = arr2[i];
            idx++;
        }
    }

    free(table);
    printf("Intersection: ");
    printArray(intersection, idx);
}

// Exercise 2 - O(N)
void findDuplicate() {
    const int length = 7;
    int list[] = {'a', 'b', 'c', 'd', 'c', 'e', 'f'};
    int i, key;
    int *table = initHashTable(26);

    for (i = 0; i < length; i++) {
        key = list[i] - 97;
        if (table[key]) {
            printf("Duplicate is '%c'\n", list[i]);
            return;
        }
        table[key] = 1;
    }
    free(table);
    puts("No duplicate characters found");
}
