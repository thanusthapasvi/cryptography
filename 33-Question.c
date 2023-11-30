#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext) {
    DES_key_schedule des_key;
    DES_set_key((DES_cblock *)key, &des_key);
    DES_encrypt1((DES_cblock *)plaintext, &des_key, ciphertext);
}

void des_decrypt(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext) {
    DES_key_schedule des_key;
    DES_set_key((DES_cblock *)key, &des_key);
    DES_decrypt1((DES_cblock *)ciphertext, &des_key, plaintext);
}

int main() {
    unsigned char key[8] = "12345678";
    unsigned char plaintext[8] = "ABCDEFGH";
    unsigned char ciphertext[8];
    unsigned char decrypted[8];

    des_encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    des_decrypt(ciphertext, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
