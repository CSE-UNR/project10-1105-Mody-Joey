//Joseph Mody
//5-6-25
//Project 10 Final

#include <stdio.h>
#include <stdbool.h>

void loadWord(char word[]) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Could not open word.txt\n");
        return;
    }
    fscanf(file, "%s", word);
    fclose(file);
}

void convertToLower(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        }
    }
}

bool isFiveLetters(char guess[]) {
    int count = 0;
    while (guess[count] != '\0') {
        count++;
    }
    return count == 5;
}

bool hasOnlyLetters(char guess[]) {
    for (int i = 0; guess[i] != '\0'; i++) {
        if (guess[i] < 'a' || guess[i] > 'z') {
            return false;
        }
    }
    return true;
}


bool checkGuess(char word[], char guess[]) {
    for (int i = 0; i < 5; i++) {
        if (word[i] != guess[i]) {
            return false;
        }
    }
    return true;
}


void showGuesses(char word[], char guesses[][6], int attempts) {
    printf("==============================\n");
    for (int i = 0; i < attempts; i++) {
        char hint[6] = "     ";
        for (int j = 0; j < 5; j++) {
            if (guesses[i][j] == word[j]) {
                guesses[i][j] -= ('a' - 'A');
            } else {
                for (int k = 0; k < 5; k++) {
                    if (guesses[i][j] == word[k]) {
                        hint[j] = '^';
                    }
                }
            }
        }
        printf("%s\n", guesses[i]);
        printf("%s\n", hint);
    }
}


void getGuess(char guess[], int guessNum) {
    do {
        printf("GUESS %d! Enter your guess: ", guessNum);
        scanf("%s", guess);
        convertToLower(guess);

        if (!isFiveLetters(guess) || !hasOnlyLetters(guess)) {
            printf("Guess must be exactly 5 letters (a-z only)!\n");
        }
    } while (!isFiveLetters(guess) || !hasOnlyLetters(guess));
}

int main() {
    char word[6];
    char guesses[6][6];
    int attempts = 0;
    bool correct = false;

    loadWord(word);

    while (attempts < 6 && !correct) {
        getGuess(guesses[attempts], attempts + 1);
        correct = checkGuess(word, guesses[attempts]);
        showGuesses(word, guesses, attempts + 1);
        attempts++;
    }

    if (correct) {
        printf("%s\n", guesses[attempts - 1]);
        printf("  You won in %d guesses!\n", attempts);
        printf("         Nice!\n");
    } else {
        printf("Sorry, you're out of guesses. The word was '%s'.\n", word);
    }

    return 0;
}

