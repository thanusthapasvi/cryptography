#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void cbc_mac(const unsigned char *key, const unsigned char *message, unsigned char *mac) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE);

    AES_cbc_encrypt(message, mac, AES_BLOCK_SIZE, &aesKey, iv, AES_ENCRYPT);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "1234567890123456";
    unsigned char message[AES_BLOCK_SIZE] = "HelloWorld123456";

    unsigned char mac[AES_BLOCK_SIZE];
    cbc_mac(key, message, mac);

    printf("MAC for one-block message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    unsigned char two_block_message[2 * AES_BLOCK_SIZE];
    memcpy(two_block_message, message, AES_BLOCK_SIZE);
    memcpy(two_block_message + AES_BLOCK_SIZE, mac, AES_BLOCK_SIZE);

    cbc_mac(key, two_block_message, mac);

    printf("MAC for two-block message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}
