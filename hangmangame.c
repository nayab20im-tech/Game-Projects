#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 20
#define MAX_LEN 20

char words[MAX_WORDS][MAX_LEN] = {
    "computer","keyboard","mouse","programming",
    "elephant","tiger","giraffe","airplane",
    "internet","software","hardware","developer",
    "language","science","university","education",
    "football","cricket","hockey","basketball"
};

int used[MAX_WORDS] = {0};

char hangman[7][100] = {
" +---+\n     |\n     |\n     |\n    ===",
" +---+\n O   |\n     |\n     |\n    ===",
" +---+\n O   |\n |   |\n     |\n    ===",
" +---+\n O   |\n/|   |\n     |\n    ===",
" +---+\n O   |\n/|\\  |\n     |\n    ===",
" +---+\n O   |\n/|\\  |\n/    |\n    ===",
" +---+\n O   |\n/|\\  |\n/ \\  |\n    ==="
};

void line() {
    printf("========================================\n");
}

int getWord() {
    int i;
    do {
        i = rand() % MAX_WORDS;
    } while (used[i]);
    used[i] = 1;
    return i;
}

void makePuzzle(char word[], char puzzle[], int level) {
    strcpy(puzzle, word);
    int len = strlen(word);

    int hide = (level == 1) ? len / 3 :
               (level == 2) ? len / 2 :
                              (2 * len) / 3;

    for (int i = 0; i < hide; i++) {
        int r = rand() % len;
        if (r != 0 && r != len - 1)
            puzzle[r] = '_';
    }
}

int complete(char p[]) {
    for (int i = 0; p[i]; i++)
        if (p[i] == '_') return 0;
    return 1;
}

int main() {
    srand(time(0));

    char p1[30], p2[30];
    int level, rounds = 5;
    int score1 = 0, score2 = 0;

    printf("\n");
    line();
    printf("        🎮 WORD WIZARD ULTIMATE\n");
    line();

    printf("Enter Player 1 Name: ");
    scanf("%s", p1);

    printf("Enter Player 2 Name: ");
    scanf("%s", p2);

    printf("\nSelect Level (1-Easy | 2-Medium | 3-Hard): ");
    scanf("%d", &level);

    printf("\n🚀 Game Starting...\n\n");

    for (int r = 1; r <= rounds; r++) {

        for (int turn = 1; turn <= 2; turn++) {

            char word[MAX_LEN], puzzle[MAX_LEN];
            int idx = getWord();

            strcpy(word, words[idx]);
            makePuzzle(word, puzzle, level);

            int wrong = 0;
            int hang = 0;

            line();
            printf("ROUND %d | PLAYER: %s\n", r, (turn == 1 ? p1 : p2));
            line();

            printf("Puzzle: %s\n", puzzle);
            printf("Lives ❤️❤️❤️❤️❤️❤️\n");
            printf("Score: %s=%d | %s=%d\n\n", p1, score1, p2, score2);

            while (!complete(puzzle) && wrong < 6) {

                printf("%s\n", hangman[hang]);
                printf("Enter letter: ");

                char ch;
                scanf(" %c", &ch);

                int found = 0;

                for (int i = 0; word[i]; i++) {
                    if (word[i] == ch && puzzle[i] == '_') {
                        puzzle[i] = ch;
                        found = 1;
                    }
                }

                if (!found) {
                    printf("❌ Wrong!\n");
                    wrong++;
                    hang++;
                } else {
                    printf("✅ Correct!\n");
                }

                printf("Puzzle: %s\n\n", puzzle);
            }

            printf("\n✔ Word was: %s\n", word);

            if (turn == 1)
                score1 += complete(puzzle) ? 10 : -2;
            else
                score2 += complete(puzzle) ? 10 : -2;

            printf("📊 Score Update: %s=%d | %s=%d\n\n",
                   p1, score1, p2, score2);
        }
    }

    line();
    printf("🏁 FINAL RESULTS\n");
    line();

    printf("%s: %d\n", p1, score1);
    printf("%s: %d\n", p2, score2);

    if (score1 > score2)
        printf("🏆 Winner: %s\n", p1);
    else if (score2 > score1)
        printf("🏆 Winner: %s\n", p2);
    else
        printf("🤝 DRAW\n");

    line();

    return 0;
}