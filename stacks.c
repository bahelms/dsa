#include <stdio.h>
#include <string.h>

struct Stack {
    int index;
    char data[30];
};

void push(struct Stack *stack, char chr) {
    stack->index++;
    stack->data[stack->index] = chr;
}

char pop(struct Stack *stack) {
    char chr = stack->data[stack->index];
    stack->index--;
    return chr;
}

// Chapter 9 - exercise 4 - O(n)
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        puts("A string must be provided.");
        return 0;
    }

    char *str = argv[1];
    int length = strlen(str);
    char reversed[length + 1];
    struct Stack stack;
    stack.index = -1;

    for (int i = 0; i < length; i++) {
        push(&stack, str[i]);
    }

    for (int i = 0; i < length; i++) {
        reversed[i] = pop(&stack);
    }
    reversed[length] = '\0';

    printf("reversed: %s\n", reversed);
    return 0;
}
