#include "arrays.h"
#include <stdio.h>

void quicksort(int[], int, int);
int partition(int[], int, int);

int main(int argc, char *argv[]) {
    int list[] = {0, 5, 2, 4, 1, 6, 3};
    int length = 7;

    quicksort(list, 0, length - 1);
    printArray(list, length);

    return 0;
}

void quicksort(int list[], int left, int right) {
    if (right - left <= 0)
        return;
    int pivot = partition(list, left, right);
    quicksort(list, left, pivot - 1);
    quicksort(list, pivot + 1, right);
}

int partition(int list[], int left, int pivot) {
    int right = pivot - 1;

    while (1) {
        while (list[left] < list[pivot]) {
            left++;
        }

        while (list[right] > list[pivot]) {
            right--;
        }

        if (left >= right)
            break;

        swapValue(list, left, right);
    }
    swapValue(list, left, pivot);
    return left;
}
