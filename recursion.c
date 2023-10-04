#include "arrays.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

int charCount(char *[], int, int);
int *evenNumbers(int[], int[], int, int);
int triangularNumbers(int);
int indexOfX(const char *, int);
int uniquePaths(int, int);

int main(int argc, char *argv[]) {
    char *strings[] = {"ab", "c", "def", "ghij"};
    printf("charCount: %d\n", charCount(strings, 4, 0));

    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int evenNums[] = {0, 0, 0, 0, 0};
    printf("evenNumbers: ");
    printArray(evenNumbers(nums, evenNums, 10, 0), 5);

    printf("triangularNumbers: %d\n", triangularNumbers(7));
    printf("indexOfX: %d\n", indexOfX("abcdefghijklmnopqrstuvwxyz", 0));
    printf("uniquePaths: %d\n", uniquePaths(3, 7));
    return 0;
}

// Ch. 11 - Exercise 1
int charCount(char *strings[], int length, int count) {
    if (length == 0)
        return count;
    return charCount(&strings[1], --length, strlen(strings[0]) + count);
}

// Ch. 11 - Exercise 2
int *evenNumbers(int nums[], int evenNums[], int length, int i) {
    if (length == 0)
        return evenNums;
    if (nums[0] % 2 == 0) {
        evenNums[i] = nums[0];
        i++;
    }
    return evenNumbers(&nums[1], evenNums, --length, i);
}

// Ch. 11 - Exercise 3
int triangularNumbers(int num) {
    if (num == 1)
        return 1;
    return num + triangularNumbers(num - 1);
}

// Ch. 11 - Exercise 4
int indexOfX(const char *str, int index) {
    if (str[index] == 'x')
        return index;
    return indexOfX(str, ++index);
}

// Ch. 11 - Exercise 4
int uniquePaths(int rows, int cols) {
    if (rows == 1 || cols == 1)
        return 1;
    return uniquePaths(rows - 1, cols) + uniquePaths(rows, cols - 1);
}
