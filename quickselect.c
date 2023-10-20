#include "arrays.h"
#include <stdio.h>

int quickselect(int[], int, int, int);
int partition(int[], int, int);

int main(int argc, char *argv[]) {
    int list[] = {0, 5, 2, 4, 1, 6, 3};
    int length = 7, nth_lowest_value = 3;

    int value = quickselect(list, nth_lowest_value, 0, length - 1);
    printf("Element at index %d is %d\n", nth_lowest_value, value);

    return 0;
}

int quickselect(int list[], int nth_lowest_value, int left, int right) {
    if (right - left <= 0)
        return list[left];
    int pivot = partition(list, left, right);

    if (pivot == nth_lowest_value)
        return list[pivot];
    else if (pivot > nth_lowest_value)
        return quickselect(list, nth_lowest_value, left, pivot - 1);
    else
        return quickselect(list, nth_lowest_value, pivot + 1, right);
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
