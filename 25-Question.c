#include <stdio.h>
#include <stdint.h>

uint32_t gcd(uint32_t a, uint32_t b);
uint32_t factorizeN(uint32_t n, uint32_t plaintext);

int main() {

    uint32_t n = 3599;
    uint32_t e = 31;

    uint32_t knownPlaintextBlock = 123;

    uint32_t factor1 = factorizeN(n, knownPlaintextBlock);

    if (factor1 == 0) {
        printf("Could not factorize n using the known plaintext block.\n");
    } else {
        uint32_t factor2 = n / factor1;
        printf("Factorization of n: %u * %u\n", factor1, factor2);
    }

    return 0;
}

uint32_t gcd(uint32_t a, uint32_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

uint32_t factorizeN(uint32_t n, uint32_t plaintext) {
    uint32_t factor = gcd(n, plaintext);

    if (factor > 1 && factor < n) {
        return factor;
    } else {
        return 0;
    }
}
