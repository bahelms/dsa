#include <stdio.h>

void swapValue(int list[], int a, int b) {
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void printArray(int list[], int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", list[i]);
        if (i != length - 1)
            printf(",");
    }
    puts("]");
}
