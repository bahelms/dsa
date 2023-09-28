#include "arrays.h"
#include <stdio.h>

void insertionSort(int[], int);

int main(int argc, char *argv[]) {
    int list[] = {4, 2, 7, 1, 33, 5, 42, 8, 15, 10};
    int length = 10;

    insertionSort(list, length);
    printArray(list, length);

    return 0;
}

void insertionSort(int list[], int length) {
    int gap, temp;
    for (int i = 1; i < length; i++) {
        gap = i;
        temp = list[gap];
        while (temp < list[gap - 1] && (gap - 1) >= 0) {
            list[gap] = list[gap - 1];
            gap--;
        }
        list[gap] = temp;
    }
}
