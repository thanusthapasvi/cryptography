#include <stdio.h>
#include <string.h>

void vigenere_one_time_pad_encrypt(const char *plaintext, const int *key, char *ciphertext) {
    int plaintext_len = strlen(plaintext);
    
    for (int i = 0; i < plaintext_len; i++) {
        int shifted_key = key[i] % 26;

        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + shifted_key) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + shifted_key) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[plaintext_len] = '\0';
}

int main() {
    const char *plaintext = "HelloWorld";
    const int key[] = {3, 19, 5, 10, 7, 15, 2, 8, 20, 1, 6, 12};
    char ciphertext[strlen(plaintext) + 1];

    vigenere_one_time_pad_encrypt(plaintext, key, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
