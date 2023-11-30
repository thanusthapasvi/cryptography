#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>

void encryptCBC3DES(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext);
void printHex(const char* label, const uint8_t* data, size_t length);

int main() {
    uint8_t key[24] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98,
                       0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    uint8_t iv[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

    const char* plaintext = "Hello, CBC mode!";

    size_t plaintextLength = strlen(plaintext);

    uint8_t ciphertext[plaintextLength];

    encryptCBC3DES(key, iv, (const uint8_t*)plaintext, plaintextLength, ciphertext);

    printHex("Plaintext: ", (const uint8_t*)plaintext, plaintextLength);
    printHex("Ciphertext:", ciphertext, plaintextLength);

    return 0;
}

void encryptCBC3DES(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext) {
    DES_cblock desKey1, desKey2, desKey3;
    DES_key_schedule keySchedule1, keySchedule2, keySchedule3;

    memcpy(desKey1, key, 8);
    memcpy(desKey2, key + 8, 8);
    memcpy(desKey3, key + 16, 8);

    DES_set_key_unchecked(&desKey1, &keySchedule1);
    DES_set_key_unchecked(&desKey2, &keySchedule2);
    DES_set_key_unchecked(&desKey3, &keySchedule3);

    DES_cblock ivec;
    memcpy(ivec, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, plaintext + i, 8);

        for (int j = 0; j < 8; ++j) {
            inputBlock[j] ^= ivec[j];
        }

        DES_ecb3_encrypt(&inputBlock, &outputBlock, &keySchedule1, &keySchedule2, &keySchedule3, DES_ENCRYPT);

        memcpy(ciphertext + i, outputBlock, 8);
        memcpy(ivec, outputBlock, 8);
    }
}

void printHex(const char* label, const uint8_t* data, size_t length) {
    printf("%s", label);
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
