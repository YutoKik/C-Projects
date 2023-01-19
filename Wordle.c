#include <stdio.h>



int main() {
    char confirm[6];
    char word[6];
    char guess[6] = "";
    char * abc;
    int moves = 10;
    int n = 50;
    int *p = &n;

    printf("%d", *p);
    printf("what is the wordle word\n");
    scanf("%s", word);
    printf("%s\n", word);
    printf("What is the word you are using to find the word\n");
    for (int i=0; i<moves; i++) {
        scanf("%s", guess);
        printf("%s\n", guess);
        for (int j=0; j<5; j++) {
            char test = '_';
            for (int z=0; z<5; z++) {
                if (word[z] == guess[j]) {
                    if (j == z) {
                        confirm[z] = '*';
                    } else {
                        confirm[z] = '+';
                    }
                }
            }
            printf("%s", confirm[i]);
        }
        printf("\n");
    }

    return 0;
}
