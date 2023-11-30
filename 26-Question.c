#include <stdio.h>
#include <stdint.h>

uint32_t gcd(uint32_t a, uint32_t b);
uint32_t modInverse(uint32_t a, uint32_t m);

int main() {
   
    uint32_t leakedPrivateD = 123;

    uint32_t originalPublicE = 65537;
    uint32_t originalModulusN = 3233; 

    uint32_t originalPrivateD = modInverse(originalPublicE, originalModulusN);

    uint32_t factor1 = modInverse(leakedPrivateD, originalModulusN);

    if (factor1 == 0) {
        printf("Leaked private key does not help factorize the modulus.\n");
    } else {
        uint32_t factor2 = originalModulusN / factor1;
        printf("Factorization of modulus: %u * %u\n", factor1, factor2);
        printf("Security compromised!\n");
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

uint32_t modInverse(uint32_t a, uint32_t m) {

    int32_t x, y;
    int32_t g = extendedGCD(a, m, &x, &y);

    if (g != 1) {
        return 0;
    } else {
        return (x % m + m) % m;
    }
}

uint32_t extendedGCD(uint32_t a, uint32_t b, int32_t *x, int32_t *y) {

}
