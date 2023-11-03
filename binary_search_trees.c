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
    if (node == NULL || node->value == value)
        return node;
    else if (value > node->value)
        return search(node->right, value);
    else
        return search(node->left, value);
}

void insert(Node *node, int value) {
    if (value > node->value) {
        if (node->right == NULL) {
            node->right = init_node(value);
        } else {
            insert(node->right, value);
        }
    } else if (value < node->value) {
        if (node->left == NULL) {
            node->left = init_node(value);
        } else {
            insert(node->left, value);
        }
    }
}

Node *move_successor_node(Node *node, Node *parent) {
    if (node->left == NULL) {
        if (node->right != NULL)
            parent->left = node->right;
        return node;
    }
    return move_successor_node(node->left, node);
}

Node *delete_node(Node *node) {
    Node *left = node->left, *right = node->right, *successor = NULL;

    if (node->left == NULL && node->right == NULL) {
        free(node);
    } else if (node->left == NULL) {
        Node *new_child = node->right;
        free(node);
        successor = new_child;
    } else if (node->right == NULL) {
        Node *new_child = node->left;
        free(node);
        successor = new_child;
    } else {
        successor = move_successor_node(node->right, node);
        free(node);
    }
    if (successor != NULL) {
        successor->left = left;
        successor->right = right;
    }
    return successor;
}

void delete_value(Node *node, int value) {
    if (node == NULL) {
        return;
    }
    // handle not finding value
    // handle value being root
    if (node->left != NULL && node->left->value == value) {
        node->left = delete_node(node->left);
    } else if (node->right != NULL && node->right->value == value) {
        node->right = delete_node(node->right);
    } else {
        if (node->value < value) {
            delete_value(node->right, value);
        } else {
            delete_value(node->left, value);
        }
    }
}

void find_value(Node *node, int value) {
    node = search(node, value);
    if (node == NULL)
        printf("Node doesn't exist: %d\n", value);
    else
        printf("Node exists: %d\n", node->value);
}

int main(int argc, char *argv[]) {
    /*
     *       50
     *     /    \
     *   25      75
     *  /  \    /  \
     * 20  27  70  80
     *      \       \
     *      30      85
     */
    Node *root = init_node(50);
    insert(root, 25);
    insert(root, 75);
    insert(root, 20);
    insert(root, 27);
    insert(root, 70);
    insert(root, 80);
    insert(root, 30);
    insert(root, 85);

    puts("Search");
    find_value(root, 27);
    find_value(root, 71);

    puts("\nDelete");
    find_value(root, 20);
    delete_value(root, 20);
    find_value(root, 20);

    find_value(root, 80);
    /* delete_value(root, 80); */
    find_value(root, 80);
    find_value(root, 85);

    find_value(root, 75);
    /* delete_value(root, 75); */
    find_value(root, 75);
    find_value(root, 70);
    find_value(root, 85);

    delete_value(root, 100);
    /* delete_value(root, 50); */

    return 0;
}
