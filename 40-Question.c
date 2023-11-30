#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculate_letter_frequencies(const char *text, double *frequencies) {
    int total_letters = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char uppercase_char = toupper(text[i]);
            frequencies[uppercase_char - 'A']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (frequencies[i] / total_letters) * 100.0;
    }
}

void monoalphabetic_substitution_attack(const char *ciphertext, int top_results) {
    double frequencies[ALPHABET_SIZE] = {0.0};
    calculate_letter_frequencies(ciphertext, frequencies);

    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequencies[sorted_indices[j]] > frequencies[sorted_indices[i]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    printf("Top %d possible plaintexts:\n", top_results);
    for (int k = 0; k < top_results; k++) {
        printf("%d. Key: ", k + 1);

        char key[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            key[sorted_indices[i]] = 'A' + i;
            printf("%c", key[sorted_indices[i]]);
        }

        printf("\nDecrypted Text: ");

        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (isalpha(ciphertext[i])) {
                char uppercase_char = toupper(ciphertext[i]);
                printf("%c", isupper(ciphertext[i]) ? key[uppercase_char - 'A'] : tolower(key[uppercase_char - 'A']));
            } else {
                printf("%c", ciphertext[i]);
            }
        }

        printf("\n\n");
    }
}

int main() {
    const char *ciphertext = "Lwklv lv d whvw phvvdjh.";

    int top_results = 3;
    monoalphabetic_substitution_attack(ciphertext, top_results);

    return 0;
}
