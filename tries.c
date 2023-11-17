#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 26

typedef struct TrieNode {
    struct TrieNode *table[HASH_TABLE_SIZE];
} TrieNode;

TrieNode *newNode() {
    TrieNode *node = malloc(sizeof(TrieNode));
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        node->table[i] = NULL;
    return node;
}

int hashCharacter(char chr) { return chr - 97; }

void insert(TrieNode *trie, const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        char chr = word[i];
        TrieNode *child = trie->table[hashCharacter(chr)];
        if (child == NULL) {
            child = newNode();
            trie->table[hashCharacter(chr)] = child;
        }
        trie = child;
    }
}

int search(TrieNode *trie, const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        char chr = word[i];
        TrieNode *child = trie->table[hashCharacter(chr)];
        if (child == NULL)
            return 0;
        trie = child;
    }
    return 1;
}

// depth first
char **collectAllWords(TrieNode *trie) {
    char **words = malloc(sizeof(char *) * 20);
    return words;
}

int main(int argc, char *argv[]) {
    const int length = 3;
    const char words[][10] = {"ace", "act", "bat"};
    TrieNode *trie = newNode();

    for (int i = 0; i < length; i++) {
        insert(trie, words[i]);
    }

    printf("Has 'bat'? %d\n", search(trie, "bat"));
    printf("Has 'battery'? %d\n", search(trie, "battery"));
    printf("Has 'ace'? %d\n", search(trie, "ace"));

    puts("All words:");
    char **allWords = collectAllWords(trie);
    for (int i = 0; i < 20; i++) {
        printf("%s\n", allWords[i]);
    }

    return 0;
}
