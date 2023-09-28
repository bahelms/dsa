#include <stdio.h>
#include <stdlib.h>

int binary_search(int[], int, int);

int main(int argc, char *argv[]) {
    int list[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int value = atoi(argv[1]); // what we're searching for
    int index;

    if ((index = binary_search(list, value, 9)) == -1) {
        printf("%d was not found\n", value);
    } else {
        printf("%d is at index %d\n", value, index);
    }

    return 0;
}

int binary_search(int list[], int value, int length) {
    int lower = 0, upper = length - 1;
    int index;

    while (lower <= upper) {
        index = (lower + upper) / 2;
        if (value == list[index]) {
            return index;
        } else if (value < list[index]) {
            upper = index - 1;
        } else {
            lower = index + 1;
        }
    }
    return -1;
}
