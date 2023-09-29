/*
 * Chapter 8 - A Common-Sense Guide to Data Structures and Algorithms
 * */

#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *initHashTable(int);
void findIntersections();
void findDuplicate();
void findMissingLetter();
void firstNonDuplicateLetter();

int main(int argc, char *argv[]) {
    findIntersections();
    findDuplicate();
    findMissingLetter();
    firstNonDuplicateLetter();
    return 0;
}

int *initHashTable(int length) {
    int *table = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        table[i] = 0;
    }
    return table;
}

int hashCharacter(char chr) { return chr - 97; }

// Exercise 1 - O(N)
// should be [2, 4]
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
    int list[] = {'a', 'b', 'c', 'd', 'c', 'e', 'f'}; // should be 'c'
    int i, key;
    int *table = initHashTable(26);

    for (i = 0; i < length; i++) {
        key = hashCharacter(list[i]);
        if (table[key]) {
            printf("Duplicate is '%c'\n", list[i]);
            return;
        }
        table[key] = 1;
    }
    free(table);
    puts("No duplicate characters found");
}

// Exercise 3 - O(N)
void findMissingLetter() {
    char *string =
        "the quick brown box jumps over the lazy dog"; // should be 'f'
    int i, key, length = strlen(string);
    int *table = initHashTable(length);

    for (i = 0; string[i] != '\0'; i++) {
        key = hashCharacter(string[i]);
        table[key] = 1;
    }

    for (i = 0; i < length; i++) {
        if (!table[i]) {
            printf("The missing letter is '%c'\n", i + 97);
            return;
        }
    }
}

// Exercise 4 - O(N)
void firstNonDuplicateLetter() {
    char *string = "minimum"; // should be 'n'
    int i, key, length = strlen(string);
    int *table = initHashTable(length);

    for (i = 0; string[i] != '\0'; i++) {
        key = hashCharacter(string[i]);
        table[key]++;
    }

    for (i = 0; string[i] != '\0'; i++) {
        key = hashCharacter(string[i]);
        if (table[key] == 1) {
            printf("The first non-duplicated letter is '%c'\n", string[i]);
            return;
        }
    }
}
