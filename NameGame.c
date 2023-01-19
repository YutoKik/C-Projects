#include <stdio.h>
#include <stdlib.h>
/*
 * Yuto Kikuchi
 * COP3502 Section 4
 * Assignment 6: Name Change
 * 11/21/2022
 */

typedef struct TrieNode TrieNode;
struct TrieNode {
    TrieNode *children[26]; // trie node that has 26 children for 26 characters in the alphabet
    int mangos; // each node can store the mango at that location
    int subtreesum; // and the total sum

};

TrieNode *createNode() { // create a node function
    TrieNode *result = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++) // once created a node set all characters to null
        result->children[i] = NULL;
    result->mangos = 0; // and results to 0
    result->subtreesum = 0;
    return result;
}
TrieNode *addWord(TrieNode *root, char* word, int mangos) { // meades function of adding a word
    if (root == NULL) { // if children does not exist create a children
        root = createNode();
    }
    if (word[0] == '\0') { // if at the end of the word
        root->subtreesum += mangos; // add mango to result total
        root->mangos += mangos; // add mango to the end of the word
    } else {
        root->subtreesum += mangos; // add mangos to total sum tree
        root->children[word[0] - 'A'] = addWord(root->children[word[0] - 'A'], word + 1, mangos); // recurse through till end of word
    }

    return root;
}
int containstotal(TrieNode *root, char* word) { // returns the total sum up to the end of the word

    if (root == NULL) {
        return 0;
    } if (word[0] == '\0') {
        return root->subtreesum;
    }
    return containstotal(root->children[word[0] - 'A'], word + 1); // recurse and return
}
int contains(TrieNode *root, char* word) { // returns the mangos at the end of the word
    if (root == NULL) {
        return 0;
    } if (word[0] == '\0') {
        return root->mangos;
    }
    return contains(root->children[word[0] - 'A'], word + 1);
}
void removename(TrieNode *root, char* word, int mangos) { // to remove a name just set the names mangos -= to old mango then set the new names mangos to the old names mangos
    if (root == NULL) {

        return;
    } if (word[0] == '\0') { // if at the end of the word
        root->subtreesum -= mangos; // -= old mangos from total sum
        root->mangos -= mangos; // -= old mangos from root mangos
        return;
    }
    root->subtreesum -= mangos; // until at end of the word -= old mango from total sum
    return removename(root->children[word[0] - 'A'], word + 1, mangos);

}
void cleanTrie(TrieNode *root) { // cleans or frees the trie
    if (root == NULL)
        return;
    for (int i = 0; i < 26; i++)
        cleanTrie(root->children[i]);
    free(root);
}

int main(void) {
    TrieNode *root; // create a trie root
    root = createNode();

    int orangutans = 0;
    int d;
    int x;
    int mangos;
    char name[21]; // name max characters is 20+1 for null
    scanf("%d %d", &d , &orangutans); // scan how many names and how many times to loop
    for (int i=0; i<orangutans; i++) { // for loop
        scanf("%d", &x); // scan x
        if (x == 1) { // if x = 1 add the mangos at the end of the word, and add to total

            scanf("%s %d", name, &mangos);
            addWord(root, name, mangos);

        } else if (x == 2) { // if x = 2, grab mangos at the old name, set the mangos at the old name -= to old mangos then at the new name += mangos
            //rename
            int temp;
            char newname[21];
            scanf("%s %s", name, newname); // gets name and newname
            temp = contains(root, name); // contains grabs the old mangos

            removename(root, name, temp); // remove name -= from each totalsum and mango at the last node
            addWord(root, newname, temp); // add word += old mangos to total sum and mango at the last node
        } else if (x == 3) { // 3 grabs the total sum of mangos at the last letter
            // recall how many mangos for name
            scanf("%s", name); // scans the name
            printf("%d\n", containstotal(root, name)); // grabs the total and print
        }
    }


    cleanTrie(root); // clean and free
    return 0;
}
