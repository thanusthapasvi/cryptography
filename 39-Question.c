#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculate_letter_frequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char uppercase_char = toupper(text[i]);
            frequencies[uppercase_char - 'A']++;
        }
    }
}

void additive_cipher_letter_frequency_attack(const char *ciphertext, int top_results) {
    int frequencies[ALPHABET_SIZE] = {0};
    calculate_letter_frequencies(ciphertext, frequencies);

    char most_frequent_letter = 'E';
    int shift = (most_frequent_letter - 'A' - (int)most_frequent_letter + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("Top %d possible plaintexts:\n", top_results);
    for (int k = 0; k < top_results; k++) {
        printf("%d. Shift: %d\n", k + 1, shift);

        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (isalpha(ciphertext[i])) {
                char uppercase_char = toupper(ciphertext[i]);
                char decrypted_char = 'A' + (uppercase_char - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
                printf("%c", isupper(ciphertext[i]) ? decrypted_char : tolower(decrypted_char));
            } else {
                printf("%c", ciphertext[i]);
            }
        }
        printf("\n\n");

        shift = (shift - 1 + ALPHABET_SIZE) % ALPHABET_SIZE;
    }
}

int main() {
    const char *ciphertext = "Lwklv lv d whvw phvvdjh.";
    int top_results = 3;
    additive_cipher_letter_frequency_attack(ciphertext, top_results);

    return 0;
}
