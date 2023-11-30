#include <stdio.h>
#include <stdint.h>

uint32_t gcd(uint32_t a, uint32_t b);
uint32_t extendedGCD(uint32_t a, uint32_t b, int32_t *x, int32_t *y);
uint32_t modInverse(uint32_t a, uint32_t m);
uint32_t modExp(uint32_t base, uint32_t exp, uint32_t mod);

int main() {
    uint32_t e = 31;
    uint32_t n = 3599;
    uint32_t p = 59;
    uint32_t q = 61;
    uint32_t phiN = (p - 1) * (q - 1);
    uint32_t d = modInverse(e, phiN);

    printf("Public key (e, n): (%u, %u)\n", e, n);
    printf("Private key (d): %u\n", d);

    uint32_t plaintext = 123;
    uint32_t ciphertext = modExp(plaintext, e, n);
    uint32_t decryptedText = modExp(ciphertext, d, n);

    printf("Plaintext: %u\n", plaintext);
    printf("Ciphertext: %u\n", ciphertext);
    printf("Decrypted Text: %u\n", decryptedText);

    return 0;
}

uint32_t gcd(uint32_t a, uint32_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

uint32_t extendedGCD(uint32_t a, uint32_t b, int32_t *x, int32_t *y) {
    // Extended GCD logic goes here
}

uint32_t modInverse(uint32_t a, uint32_t m) {
    int32_t x, y;
    extendedGCD(a, m, &x, &y);

    // Ensure that the result is positive
    return (x % m + m) % m;
}

uint32_t modExp(uint32_t base, uint32_t exp, uint32_t mod) {
    uint32_t result = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        exp /= 2;
        base = (base * base) % mod;
    }

    return result;
}
