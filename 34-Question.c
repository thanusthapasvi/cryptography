#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void aes_ecb_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, int size) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    for (int i = 0; i < size; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &aesKey);
    }
}

void aes_cbc_encrypt(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int size) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char previous_block[AES_BLOCK_SIZE];
    memcpy(previous_block, iv, AES_BLOCK_SIZE);

    for (int i = 0; i < size; i += AES_BLOCK_SIZE) {
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ previous_block[j];
        }

        AES_encrypt(ciphertext + i, ciphertext + i, &aesKey);

        memcpy(previous_block, ciphertext + i, AES_BLOCK_SIZE);
    }
}

void aes_cfb_encrypt(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int size, int segment_size) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char feedback[AES_BLOCK_SIZE];
    memcpy(feedback, iv, AES_BLOCK_SIZE);

    for (int i = 0; i < size; i += segment_size) {
        AES_encrypt(feedback, feedback, &aesKey);

        for (int j = 0; j < segment_size && i + j < size; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ feedback[j];
        }

        memcpy(feedback, ciphertext + i, segment_size);
    }
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "1234567890123456";
    unsigned char iv[AES_BLOCK_SIZE] = "abcdefgh12345678";
    unsigned char plaintext[] = "This is a message.";
    int plaintext_size = strlen((char *)plaintext);

    int padded_size = (plaintext_size / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    unsigned char padded_plaintext[padded_size];
    memcpy(padded_plaintext, plaintext, plaintext_size);
    memset(padded_plaintext + plaintext_size, 0, padded_size - plaintext_size);

    unsigned char ciphertext_ecb[padded_size];
    aes_ecb_encrypt(padded_plaintext, key, ciphertext_ecb, padded_size);

    unsigned char ciphertext_cbc[padded_size];
    aes_cbc_encrypt(padded_plaintext, key, iv, ciphertext_cbc, padded_size);

    unsigned char ciphertext_cfb[padded_size];
    aes_cfb_encrypt(padded_plaintext, key, iv, ciphertext_cfb, padded_size, AES_BLOCK_SIZE);

    printf("Original Text: %s\n", plaintext);

    printf("\nECB Mode:\n");
    for (int i = 0; i < padded_size; i++) {
        printf("%02X", ciphertext_ecb[i]);
    }
    printf("\n");

    printf("\nCBC Mode:\n");
    for (int i = 0; i < padded_size; i++) {
        printf("%02X", ciphertext_cbc[i]);
    }
    printf("\n");

    printf("\nCFB Mode:\n");
    for (int i = 0; i < padded_size; i++) {
        printf("%02X", ciphertext_cfb[i]);
    }
    printf("\n");

    return 0;
}
