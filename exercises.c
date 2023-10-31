#include "linked_lists.h"
#include "sorting.h"
#include <stdio.h>

int ch13_1(void);
int ch13_2(void);
void ch13_3(void);

int main(int argc, char *argv[]) {
    printf("13.1 - %d\n", ch13_1());
    printf("13.2 - %d\n", ch13_2());
    ch13_3();

    // ch14.4
    Node *head = init_node(1);
    insert_after(2, head);
    insert_after(3, head->next);
    insert_after(4, head->next->next);
    head = reverse(head);
    print_list(head);

    return 0;
}

int ch13_1(void) {
    int list[] = {0, 5, 2, 4, 1, 6, 3};
    quicksort(list, 0, 6);
    return list[6] * list[5] * list[4];
}

int ch13_2(void) {
    int list[] = {0, 5, 2, 1, 6, 3}; // missing 4
    quicksort(list, 0, 5);
    for (int i = 0; i < 6; i++) {
        if (list[i + 1] != list[i] + 1) {
            return list[i] + 1;
        }
    }
    return -1;
}

// find greatest number in O(n^2), O(n log n), O(n)
void ch13_3(void) {
    int length = 7;

    // O(n)
    int list[] = {0, 5, 2, 4, 1, 6, 3};
    int greatest = list[0];
    for (int i = 1; i < length; i++) {
        if (list[i] > greatest) {
            greatest = list[i];
        }
    }
    printf("13.3 O(n) greatest: %d\n", greatest);

    // O(n log n)
    int list2[] = {0, 5, 2, 4, 1, 6, 3};
    quicksort(list2, 0, length - 1);
    printf("13.3 O(n log n) greatest: %d\n", list2[length - 1]);

    // O(n^2)
    int list3[] = {0, 5, 2, 4, 1, 6, 3};
    int is_greatest = 0;
    for (int i = 0; i < length; i++) {
        is_greatest = 1;
        for (int j = 0; j < length; j++) {
            if (list3[j] > list3[i]) {
                is_greatest = 0;
            }
        }
        if (is_greatest) {
            printf("13.3 O(n^2) greatest: %d\n", list[i]);
        }
    }
}
