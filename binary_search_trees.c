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

Node *successor(Node *node, Node *node_to_delete) {
    if (node->left != NULL) {
        node->left = successor(node->left, node_to_delete);
        return node;
    } else {
        node_to_delete->value = node->value;
        Node *node_to_lift = node->right;
        free(node);
        return node_to_lift;
    }
}

Node *delete_value(Node *node, int value) {
    if (node == NULL) {
        return NULL;
    } else if (value < node->value) {
        node->left = delete_value(node->left, value);
        return node;
    } else if (value > node->value) {
        node->right = delete_value(node->right, value);
        return node;
    } else {
        if (node->left == NULL) {
            Node *node_to_lift = node->right;
            free(node);
            return node_to_lift;
        } else if (node->right == NULL) {
            Node *node_to_lift = node->left;
            free(node);
            return node_to_lift;
        } else {
            node->right = successor(node->right, node);
            return node;
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

// inorder
void traverse(Node *node) {
    if (node == NULL)
        return;

    traverse(node->left);
    printf("%d\n", node->value);
    traverse(node->right);
}

Node *greatest(Node *node) {
    if (node->right != NULL) {
        return greatest(node->right);
    }
    return node;
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
    delete_value(root, 80);
    find_value(root, 80);
    find_value(root, 85);

    find_value(root, 75);
    delete_value(root, 75);
    find_value(root, 75);
    find_value(root, 70);
    find_value(root, 85);

    delete_value(root, 100);
    delete_value(root, 50);

    traverse(root);
    printf("Greatest value: %d\n", greatest(root)->value);

    return 0;
}
