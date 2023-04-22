#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie* children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

struct Trie* createNode(void) {
    struct Trie* pNode = (struct Trie*)malloc(sizeof(struct Trie));
    pNode->isEndOfWord = 0;
    pNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(struct Trie** ppTrie, char* word) {
    struct Trie* pTrie = *ppTrie;
    if (pTrie == NULL) {
        pTrie = createNode();
        *ppTrie = pTrie;
    }
    int length = strlen(word);
    struct Trie* pCrawl = pTrie;
    for (int level = 0; level < length; level++) {
        int index = word[level] - 'a';
        if (pCrawl->children[index] == NULL) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = 1;
    pCrawl->count++;
}

int numberOfOccurrences(struct Trie* pTrie, char* word) {
    if (pTrie == NULL) {
        return 0;
    }
    int length = strlen(word);
    struct Trie* pCrawl = pTrie;
    for (int level = 0; level < length; level++) {
        int index = word[level] - 'a';
        if (pCrawl->children[index] == NULL) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
    }
    if (pCrawl != NULL && pCrawl->isEndOfWord) {
        return pCrawl->count;
    } else {
        return 0;
    }
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie* trie = NULL;
    
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
