#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void generate_subkeys(const unsigned char *key, unsigned char *subkey1, unsigned char *subkey2) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    int block_size = AES_BLOCK_SIZE * 8;
    const unsigned char const_Rb_64 = 0x1B;
    const unsigned char const_Rb_128 = 0x87;

    AES_encrypt(subkey1, subkey1, &aesKey);
    if ((subkey1[0] & 0x80) == 0) {
        left_shift_by_one(subkey1);
    } else {
        left_shift_by_one(subkey1);
        xor_with_constant(subkey1, (block_size == 64) ? const_Rb_64 : const_Rb_128);
    }

    AES_encrypt(subkey2, subkey2, &aesKey);
    if ((subkey2[0] & 0x80) == 0) {
        left_shift_by_one(subkey2);
    } else {
        left_shift_by_one(subkey2);
        xor_with_constant(subkey2, (block_size == 64) ? const_Rb_64 : const_Rb_128);
    }
}

void left_shift_by_one(unsigned char *data) {
    int i;
    int carry = 0;
    for (i = AES_BLOCK_SIZE - 1; i >= 0; i--) {
        int new_carry = data[i] & 0x80;
        data[i] = (data[i] << 1) | (carry >> 7);
        carry = new_carry;
    }
}

void xor_with_constant(unsigned char *data, unsigned char constant) {
    data[AES_BLOCK_SIZE - 1] ^= constant;
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "1234567890123456";
    unsigned char subkey1[AES_BLOCK_SIZE];
    unsigned char subkey2[AES_BLOCK_SIZE];

    generate_subkeys(key, subkey1, subkey2);

    printf("Subkey 1: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", subkey2[i]);
    }
    printf("\n");

    return 0;
}
