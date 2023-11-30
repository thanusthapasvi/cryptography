#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/des.h>

void encryptECB(const uint8_t* key, const uint8_t* plaintext, size_t length, uint8_t* ciphertext);
void decryptECB(const uint8_t* key, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText);
void encryptCBC(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext);
void decryptCBC(const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText);
void encryptCFB(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext);
void decryptCFB(const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText);
void printHex(const char* label, const uint8_t* data, size_t length);

int main() {
    uint8_t key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t iv[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    const char* plaintext = "Hello, ECB/CBC/CFB modes!";
    size_t plaintextLength = strlen(plaintext);
    size_t blockSize = 8;
    size_t paddingBlocks = (blockSize - (plaintextLength % blockSize)) % blockSize;
    size_t totalLength = plaintextLength + paddingBlocks + blockSize;
    uint8_t* paddedPlaintext = (uint8_t*)malloc(totalLength);
    uint8_t* ciphertextECB = (uint8_t*)malloc(totalLength);
    uint8_t* ciphertextCBC = (uint8_t*)malloc(totalLength);
    uint8_t* ciphertextCFB = (uint8_t*)malloc(totalLength);
    uint8_t* decryptedTextECB = (uint8_t*)malloc(totalLength);
    uint8_t* decryptedTextCBC = (uint8_t*)malloc(totalLength);
    uint8_t* decryptedTextCFB = (uint8_t*)malloc(totalLength);

    memcpy(paddedPlaintext, plaintext, plaintextLength);
    memset(paddedPlaintext + plaintextLength, 0, paddingBlocks);
    memset(paddedPlaintext + totalLength - blockSize, 0, blockSize);

    encryptECB(key, paddedPlaintext, totalLength, ciphertextECB);
    encryptCBC(key, iv, paddedPlaintext, totalLength, ciphertextCBC);
    encryptCFB(key, iv, paddedPlaintext, totalLength, ciphertextCFB);

    decryptECB(key, ciphertextECB, totalLength, decryptedTextECB);
    decryptCBC(key, iv, ciphertextCBC, totalLength, decryptedTextCBC);
    decryptCFB(key, iv, ciphertextCFB, totalLength, decryptedTextCFB);

    printHex("Plaintext: ", paddedPlaintext, totalLength);
    printHex("ECB Ciphertext:", ciphertextECB, totalLength);
    printHex("CBC Ciphertext:", ciphertextCBC, totalLength);
    printHex("CFB Ciphertext:", ciphertextCFB, totalLength);
    printHex("Decrypted ECB:", decryptedTextECB, totalLength);
    printHex("Decrypted CBC:", decryptedTextCBC, totalLength);
    printHex("Decrypted CFB:", decryptedTextCFB, totalLength);

    free(paddedPlaintext);
    free(ciphertextECB);
    free(ciphertextCBC);
    free(ciphertextCFB);
    free(decryptedTextECB);
    free(decryptedTextCBC);
    free(decryptedTextCFB);

    return 0;
}

void encryptECB(const uint8_t* key, const uint8_t* plaintext, size_t length, uint8_t* ciphertext) {
    DES_cblock desKey;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, plaintext + i, 8);

        DES_ecb_encrypt(&inputBlock, &outputBlock, &keySchedule, DES_ENCRYPT);

        memcpy(ciphertext + i, outputBlock, 8);
    }
}

void decryptECB(const uint8_t* key, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText) {
    DES_cblock desKey;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, ciphertext + i, 8);

        DES_ecb_encrypt(&inputBlock, &outputBlock, &keySchedule, DES_DECRYPT);

        memcpy(decryptedText + i, outputBlock, 8);
    }
}

void encryptCBC(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext) {
    DES_cblock desKey, desIV;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    memcpy(desIV, iv, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, plaintext + i, 8);

        for (int j = 0; j < 8; ++j) {
            inputBlock[j] ^= desIV[j];
        }

        DES_ecb_encrypt(&inputBlock, &outputBlock, &keySchedule, DES_ENCRYPT);

        memcpy(ciphertext + i, outputBlock, 8);
        memcpy(desIV, outputBlock, 8);
    }
}

void decryptCBC(const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText) {
    DES_cblock desKey, desIV;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    memcpy(desIV, iv, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, ciphertext + i, 8);

        DES_ecb_encrypt(&inputBlock, &outputBlock, &keySchedule, DES_DECRYPT);

        for (int j = 0; j < 8; ++j) {
            outputBlock[j] ^= desIV[j];
        }

        memcpy(decryptedText + i, outputBlock, 8);
        memcpy(desIV, inputBlock, 8);
    }
}

void encryptCFB(const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t length, uint8_t* ciphertext) {
    DES_cblock desKey, desIV, feedback;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    memcpy(desIV, iv, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, plaintext + i, 8);

        DES_ecb_encrypt(&desIV, &outputBlock, &keySchedule, DES_ENCRYPT);

        for (int j = 0; j < 8; ++j) {
            outputBlock[j] ^= inputBlock[j];
        }

        memcpy(ciphertext + i, outputBlock, 8);
        memcpy(desIV, outputBlock, 8);
    }
}

void decryptCFB(const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t length, uint8_t* decryptedText) {
    DES_cblock desKey, desIV, feedback;
    DES_key_schedule keySchedule;

    memcpy(desKey, key, 8);
    memcpy(desIV, iv, 8);
    DES_set_key_unchecked(&desKey, &keySchedule);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock inputBlock, outputBlock;
        memcpy(inputBlock, ciphertext + i, 8);

        DES_ecb_encrypt(&desIV, &outputBlock, &keySchedule, DES_ENCRYPT);

        for (int j = 0; j < 8; ++j) {
            outputBlock[j] ^= inputBlock[j];
        }

        memcpy(decryptedText + i, outputBlock, 8);
        memcpy(desIV, inputBlock, 8);
    }
}

void printHex(const char* label, const uint8_t* data, size_t length) {
    printf("%s", label);
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
