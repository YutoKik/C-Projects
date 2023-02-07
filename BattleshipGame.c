#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void print_board(char board[10][10]);
void place_ship(char board[10][10], int length);
int check_win(char board[10][10]);

void print_board(char board[10][10]) {
    printf(" 0123456789\n");
    for (int row=0; row<10; row++) {
        printf("%d", row);
        for (int col=0; col<10; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}
void place_ship(char board[10][10], int length) {
    int direction = rand()%2;
    int major = rand() % (11-length);
    int minor = rand() % 10;
    for (int pos=major; pos < major+length; pos++) {
        if (direction == 0) {
            board[minor][pos] = 'S';
        } else {
            board[pos][minor] = 'S';
        }
    }
}
int check_win(char board[10][10]) {
    int won = 1;
    for (int row = 0; row<10; row++) {
        for (int col=0; col<10; col++) {
            if (board[row][col] == 'S'){
                won = 0;
            }
        }
    }
    return won;
}
int main() {
    char board[10][10];
    char hidden[10][10];
    srand(time(0));
    for (int row=0; row<10; row++) {
        for (int col=0; col<10; col++) {
            board[row][col] = '.';
            hidden[row][col] = '.';
        }
    }
    place_ship(hidden, 3);
    place_ship(hidden, 2);
    place_ship(hidden, 4);
    place_ship(hidden, 5);
    print_board(hidden);
    int turns = 30, did_win = 0;
    while (turns >0 && check_win(hidden)!=1) {
        print_board(board);
        int row, col;
        printf("Turns Left: %d\nWhere would you like to attack?\n", turns);
        scanf("%d %d", &col, &row);
        if (board[row][col] == '.') {
            turns--;
            if (hidden[row][col] == 'S') {
                printf("HIT\n\n");
                // check win.
                board[row][col] = 'H';
                hidden[row][col] = '.';
            } else {
                board[row][col] = 'M';
            }
        } else {
            printf("This spot has already been attacked.  Select again.\n\n");
        }
    }
    if (check_win(hidden) == 1) {
        printf("Yay you won!");
    } else {
        printf("You lost.\n");
        printf("Ships remaining:\n");
        print_board(hidden);
    }
    return 0;
}