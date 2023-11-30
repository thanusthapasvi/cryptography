#include <stdio.h>
#include <openssl/dsa.h>

void generate_dsa_keypair(DSA **dsa_key) {
    *dsa_key = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(*dsa_key);
}

void dsa_sign_and_verify(DSA *dsa_key, const unsigned char *message, int message_len) {
    DSA_SIG *signature = DSA_do_sign(message, message_len, dsa_key);
    if (signature == NULL) {
        fprintf(stderr, "DSA signing failed.\n");
        return;
    }

    int verify_result = DSA_do_verify(message, message_len, signature, dsa_key);
    if (verify_result == 1) {
        printf("DSA Signature verified successfully.\n");
    } else if (verify_result == 0) {
        printf("DSA Signature verification failed.\n");
    } else {
        fprintf(stderr, "Error in signature verification.\n");
    }

    DSA_SIG_free(signature);
}

int main() {
    DSA *dsa_key;
    generate_dsa_keypair(&dsa_key);

    unsigned char message[] = "Hello, DSA!";

    printf("Signing and verifying with DSA:\n");
    dsa_sign_and_verify(dsa_key, message, sizeof(message) - 1);

    RSA *rsa_key = RSA_generate_key(1024, RSA_F4, NULL, NULL);
    unsigned char rsa_signature[1024] = {0};
    unsigned int rsa_signature_len;

    RSA_sign(NID_sha256, message, sizeof(message) - 1, rsa_signature, &rsa_signature_len, rsa_key);

    int rsa_verify_result = RSA_verify(NID_sha256, message, sizeof(message) - 1, rsa_signature, rsa_signature_len, rsa_key);
    printf("\nSigning and verifying with RSA:\n");
    if (rsa_verify_result == 1) {
        printf("RSA Signature verified successfully.\n");
    } else if (rsa_verify_result == 0) {
        printf("RSA Signature verification failed.\n");
    } else {
        fprintf(stderr, "Error in RSA signature verification.\n");
    }

    DSA_free(dsa_key);
    RSA_free(rsa_key);

    return 0;
}
