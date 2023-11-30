#include <stdio.h>
#include <stdint.h>
#include <math.h>

uint64_t modExp(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 1;
    a = a % m;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }

        b = b >> 1;
        a = (a * a) % m;
    }

    return result;
}

uint64_t diffieHellman(uint64_t privateKey, uint64_t publicKey, uint64_t prime) {
    return modExp(publicKey, privateKey, prime);
}

int main() {
    // Public parameters
    uint64_t prime = 23;     // Example prime number
    uint64_t primitiveRoot = 5;  // Example primitive root

    uint64_t alicePrivateKey = 6;
    uint64_t bobPrivateKey = 15;

    // Calculate public keys for Alice and Bob
    uint64_t alicePublicKey = modExp(primitiveRoot, alicePrivateKey, prime);
    uint64_t bobPublicKey = modExp(primitiveRoot, bobPrivateKey, prime);

    uint64_t sharedSecretAlice = diffieHellman(alicePrivateKey, bobPublicKey, prime);
    uint64_t sharedSecretBob = diffieHellman(bobPrivateKey, alicePublicKey, prime);

    printf("Alice's private key: %lu\n", alicePrivateKey);
    printf("Bob's private key: %lu\n", bobPrivateKey);
    printf("Public prime (q): %lu\n", prime);
    printf("Primitive root (a): %lu\n", primitiveRoot);
    printf("Alice's public key (ya): %lu\n", alicePublicKey);
    printf("Bob's public key (yb): %lu\n", bobPublicKey);
    printf("Shared secret key (Alice): %lu\n", sharedSecretAlice);
    printf("Shared secret key (Bob): %lu\n", sharedSecretBob);

    return 0;
}
