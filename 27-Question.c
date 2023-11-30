#include <stdio.h>
#include <stdint.h>

uint32_t encryptRSA(uint32_t plaintext, uint32_t e, uint32_t n) {
    return (plaintext * plaintext) % n;
}

int main() {
    uint32_t e = 65537;
    uint32_t n = 179951;

    char message[] = "HELLO";
    uint32_t ciphertext[sizeof(message) - 1];

    for (size_t i = 0; i < sizeof(message) - 1; ++i) {
        ciphertext[i] = encryptRSA(message[i] - 'A', e, n);
        printf("%u ", ciphertext[i]);
    }

    return 0;
}
