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
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        TrieNode *child = trie->table[i];
        if (child != NULL) {
            if (i == 26) {
                append(words, word);
                continue;
            }

            char chr = unhashCharacter(i);
            char *newWord = malloc(words->wordSize);
            strncpy(newWord, word, words->wordSize);
            strncat(newWord, &chr, 1);
            _collectAllWords(child, newWord, words);
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

char **autocomplete(TrieNode *trie, char *prefix) {
    TrieNode *node = search(trie, prefix);
    if (node == NULL)
        return NULL;
    return collectAllWords(node);
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

    puts("\nAll words:");
    char **allWords = collectAllWords(trie);
    for (int i = 0; i < 20; i++)
        if (allWords[i][0] != '\0')
            printf("%s\n", allWords[i]);

    puts("\nAutocomplete for 'ba'");
    char **completedWords = autocomplete(trie, "ba");
    for (int i = 0; i < 20; i++)
        if (completedWords[i][0] != '\0')
            printf("ba%s\n", completedWords[i]);

    return 0;
}
