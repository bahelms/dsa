#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 27

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
int unhashCharacter(int index) { return index + 97; }

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
    // This marks it as full word
    trie->table[26] = malloc(sizeof(TrieNode));
}

TrieNode *search(TrieNode *trie, const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        char chr = word[i];
        TrieNode *child = trie->table[hashCharacter(chr)];
        if (child == NULL)
            return NULL;
        trie = child;
    }
    return trie;
}

struct Words {
    int index;
    char **words;
    int wordSize;
};

void append(struct Words *words, char *word) {
    strncpy(words->words[words->index], word, words->wordSize);
    words->index++;
}

// depth first
void _collectAllWords(const TrieNode *trie, char *word, struct Words *words) {
    for (int i = 0; i < HASH_TABLE_SIZE - 1; i++) {
        TrieNode *child = trie->table[i];
        if (child != NULL) {
            char chr = unhashCharacter(i);
            char *newWord = malloc(words->wordSize);
            strncpy(newWord, word, words->wordSize);
            strncat(newWord, &chr, 1);
            if (child->table[26] != NULL) {
                append(words, newWord);
            } else {
                _collectAllWords(child, newWord, words);
            }
        }
    }
}

char **collectAllWords(const TrieNode *trie) {
    const int wordCount = 20;
    struct Words words;
    words.index = 0;
    words.words = malloc(sizeof(char *) * wordCount);
    words.wordSize = 20;
    for (int i = 0; i < wordCount; i++)
        words.words[i] = malloc(words.wordSize);
    char *word = malloc(words.wordSize);

    _collectAllWords(trie, word, &words);
    return words.words;
}

int main(int argc, char *argv[]) {
    const int length = 6;
    const char words[][10] = {"batter", "ace", "ball", "act", "bat", "can"};
    TrieNode *trie = newNode();

    for (int i = 0; i < length; i++)
        insert(trie, words[i]);

    printf("Has 'bat'? %d\n", search(trie, "bat") == NULL ? 0 : 1);
    printf("Has 'battery'? %d\n", search(trie, "battery") == NULL ? 0 : 1);
    printf("Has 'ace'? %d\n", search(trie, "ace") == NULL ? 0 : 1);

    puts("All words:");
    char **allWords = collectAllWords(trie);
    for (int i = 0; i < 20; i++)
        printf("%s\n", allWords[i]);

    return 0;
}
