#include "arrays.h"
#include <stdio.h>

void selectionSort(int[], int);

int main(int argc, char *argv[]) {
    int list[] = {4, 2, 7, 1, 33, 5, 42, 8, 15, 10};
    int length = 10;

    selectionSort(list, length);
    printArray(list, length);

    return 0;
}

void selectionSort(int list[], int length) {
    for (int start = 0; start < length - 1; start++) {
        int lowest = start;
        for (int i = start + 1; i < length; i++) {
            if (list[i] < list[lowest]) {
                lowest = i;
            }
        }

        if (lowest != start) {
            swapValue(list, start, lowest);
        }
    }
}
