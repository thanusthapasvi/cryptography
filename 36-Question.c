#include <stdio.h>

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

void affine_caesar_encrypt(const char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current_char = plaintext[i];

        if (current_char >= 'A' && current_char <= 'Z') {
            ciphertext[i] = ((a * (current_char - 'A') + b) % 26) + 'A';
        } else if (current_char >= 'a' && current_char <= 'z') {
            ciphertext[i] = ((a * (current_char - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = current_char;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    const char *plaintext = "HelloWorld";
    int a = 7;
    int b = 10;
    char ciphertext[strlen(plaintext) + 1];

    int inverse_a = mod_inverse(a, 26);
    if (inverse_a == -1) {
        printf("The given 'a' does not have a modular inverse in Z26.\n");
        return 1;
    }

    affine_caesar_encrypt(plaintext, a, b, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
