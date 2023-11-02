#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *init_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *search(Node *node, int value) {
    if (node == NULL || node->value == value) {
        return node;
    } else if (value > node->value) {
        return search(node->right, value);
    } else {
        return search(node->left, value);
    }
}

void insert(Node *node, int value) {
    if (node->value == value) {
        return;
    } else if (value > node->value) {
        if (node->right == NULL) {
            node->right = init_node(value);
        } else {
            insert(node->right, value);
        }
    } else {
        if (node->left == NULL) {
            node->left = init_node(value);
        } else {
            insert(node->left, value);
        }
    }
}

int main(int argc, char *argv[]) {
    /*
     *       50
     *     /    \
     *   25      75
     *  /  \    /  \
     * 20  27  70  80
     */
    Node *root = init_node(50);
    root->value = 50;
    root->left = init_node(25);
    root->right = init_node(75);
    root->left->left = init_node(20);
    root->left->right = init_node(27);
    root->right->left = init_node(70);
    root->right->right = init_node(80);

    puts("Search");
    Node *node = search(root, 27);
    if (node != NULL)
        printf("Node exists: %d\n", node->value);
    node = search(root, 71);
    if (node == NULL)
        printf("Node doesn't exist: %d\n", 71);

    puts("\nInsert");
    insert(root, 30);
    node = search(root, 30);
    if (node == NULL)
        printf("Node doesn't exist: %d\n", 30);
    else
        printf("Node exists: %d\n", node->value);

    return 0;
}
