#include "arrays.h"
#include <stdio.h>

void bubbleSort(int[], int);

int main(int argc, char *argv[]) {
    int list[] = {4, 2, 7, 1, 33, 5, 42, 8, 15, 10};
    int length = 10;

    bubbleSort(list, length);
    printArray(list, length);

    return 0;
}

void bubbleSort(int list[], int length) {
    int sorted = 0, listEnd = length - 1;

    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < listEnd; i++) {
            if (list[i] > list[i + 1]) {
                swapValue(list, i, i + 1);
                sorted = 0;
            }
        }
        listEnd--;
    }
}
