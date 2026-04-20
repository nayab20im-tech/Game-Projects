#include <stdio.h>
#include <stdlib.h>

#define N 9

int board[N][N] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},

    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},

    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

int fixed[N][N] = {0};

void initFixed() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] != 0)
                fixed[i][j] = 1;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    printf("========================================\n");
    printf("           🎮 SUDOKU CHALLENGE\n");
    printf("========================================\n");
}

void printBoard() {

    printf("\n      1 2 3   4 5 6   7 8 9\n");
    printf("    +-------+-------+-------+\n");

    for (int i = 0; i < N; i++) {

        printf("%d   | ", i + 1);

        for (int j = 0; j < N; j++) {

            if (board[i][j] == 0)
                printf("_ ");
            else
                printf("%d ", board[i][j]);

            if ((j + 1) % 3 == 0)
                printf("| ");
        }

        printf("\n");

        if ((i + 1) % 3 == 0)
            printf("    +-------+-------+-------+\n");
    }

    printf("\n");
}

int isValid(int r, int c, int num) {

    for (int i = 0; i < N; i++)
        if (board[r][i] == num || board[i][c] == num)
            return 0;

    int sr = (r / 3) * 3;
    int sc = (c / 3) * 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[sr + i][sc + j] == num)
                return 0;

    return 1;
}

int complete() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == 0)
                return 0;
    return 1;
}

int main() {

    initFixed();

    int r, c, num;

    while (!complete()) {

        clearScreen();
        printHeader();

        printBoard();

        printf("Instructions:\n");
        printf("Row (1-9) | Col (1-9) | Num (1-9)\n\n");

        printf("Enter row: ");
        scanf("%d", &r);

        printf("Enter col: ");
        scanf("%d", &c);

        printf("Enter num: ");
        scanf("%d", &num);

        r--; c--;

        if (fixed[r][c]) {
            printf("\n❌ Cannot change fixed number!\n");
            getchar(); getchar();
            continue;
        }

        if (isValid(r, c, num)) {
            board[r][c] = num;
            printf("\n✅ Correct move!\n");
        } else {
            printf("\n❌ Invalid move!\n");
        }

        getchar(); getchar();
    }

    clearScreen();
    printHeader();
    printBoard();

    printf("🎉 CONGRATULATIONS! YOU SOLVED IT!\n");

    return 0;
}