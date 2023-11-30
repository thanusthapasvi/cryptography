#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

void matrix_multiply(int a[MAX_SIZE][MAX_SIZE], int b[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int size, int mod) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
}

int determinant_2x2(int a, int b, int c, int d, int mod) {
    return (a * d - b * c + mod) % mod;
}

int determinant_3x3(int matrix[3][3], int mod) {
    int det = 0;
    det += matrix[0][0] * determinant_2x2(matrix[1][1], matrix[1][2], matrix[2][1], matrix[2][2], mod);
    det -= matrix[0][1] * determinant_2x2(matrix[1][0], matrix[1][2], matrix[2][0], matrix[2][2], mod);
    det += matrix[0][2] * determinant_2x2(matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1], mod);
    return det % mod;
}

void adjugate_matrix(int matrix[3][3], int mod, int adjugate[3][3]) {
    adjugate[0][0] = determinant_2x2(matrix[1][1], matrix[1][2], matrix[2][1], matrix[2][2], mod);
    adjugate[0][1] = -determinant_2x2(matrix[1][0], matrix[1][2], matrix[2][0], matrix[2][2], mod);
    adjugate[0][2] = determinant_2x2(matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1], mod);

    adjugate[1][0] = -determinant_2x2(matrix[0][1], matrix[0][2], matrix[2][1], matrix[2][2], mod);
    adjugate[1][1] = determinant_2x2(matrix[0][0], matrix[0][2], matrix[2][0], matrix[2][2], mod);
    adjugate[1][2] = -determinant_2x2(matrix[0][0], matrix[0][1], matrix[2][0], matrix[2][1], mod);

    adjugate[2][0] = determinant_2x2(matrix[0][1], matrix[0][2], matrix[1][1], matrix[1][2], mod);
    adjugate[2][1] = -determinant_2x2(matrix[0][0], matrix[0][2], matrix[1][0], matrix[1][2], mod);
    adjugate[2][2] = determinant_2x2(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], mod);
}

void inverse_matrix(int matrix[3][3], int mod, int inverse[3][3]) {
    int det = determinant_3x3(matrix, mod);
    int det_inv = mod_inverse(det, mod);

    if (det_inv == -1) {
        printf("Inverse does not exist.\n");
        exit(EXIT_FAILURE);
    }

    int adjugate[3][3];
    adjugate_matrix(matrix, mod, adjugate);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = (adjugate[i][j] * det_inv) % mod;
            if (inverse[i][j] < 0) {
                inverse[i][j] += mod;
            }
        }
    }
}

void hill_chosen_plaintext_attack(const char *chosen_plaintext, const char *chosen_ciphertext, int key_size, int mod) {
    int plaintext_matrix[MAX_SIZE][MAX_SIZE];
    int ciphertext_matrix[MAX_SIZE][MAX_SIZE];
    int inverse_key[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < key_size; i++) {
