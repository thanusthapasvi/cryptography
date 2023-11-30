#include <stdio.h>
#include <stdint.h>

#define ROUNDS 16
#define BLOCK_SIZE 64

int initialPermutation[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int finalPermutation[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

int keyPermutationChoice1[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2,
                               59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39,
                               31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37,
                               29, 21, 13, 5, 28, 20, 12, 4};

int keyPermutationChoice2[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
                               26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
                               51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

int keyRotationSchedule[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void generateKeys(uint64_t key, uint64_t keys[]);
uint64_t permute(uint64_t input, const int* permutation, int size);
void des(uint64_t* data, uint64_t* keys);

int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t keys[ROUNDS];

    generateKeys(key, keys);
    des(&plaintext, keys);

    printf("Decrypted Text: 0x%llx\n", plaintext);

    return 0;
}

void generateKeys(uint64_t key, uint64_t keys[]) {
    key = permute(key, keyPermutationChoice1, 56);

    for (int i = 0; i < ROUNDS; ++i) {
        int shift = keyRotationSchedule[i];
        uint64_t leftPart = key >> 28;
        uint64_t rightPart = key & 0x000000000fffffff;

        leftPart = ((leftPart << shift) | (leftPart >> (28 - shift))) & 0x0fffffff;
        rightPart = ((rightPart << shift) | (rightPart >> (28 - shift))) & 0x0fffffff;

        keys[i] = permute((leftPart << 28) | rightPart, keyPermutationChoice2, 48);
    }
}

void des(uint64_t* data, uint64_t* keys) {
    *data = permute(*data, initialPermutation, BLOCK_SIZE);

    uint32_t left = *data >> 32;
    uint32_t right = *data & 0xffffffff;

    for (int i = ROUNDS - 1; i >= 0; --i) {
        uint32_t temp = right;
        right = left ^ permute(right, keys[i], 32);
        left = temp;
    }

    *data = ((uint64_t)right << 32) | left;
    *data = permute(*data, finalPermutation, BLOCK_SIZE);
}

uint64_t permute(uint64_t input, const int* permutation, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; ++i) {
        output |= ((input >> (size - permutation[i])) & 0x01) << (size - 1 - i);
    }
    return output;
}
