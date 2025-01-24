#include <stdio.h>

// Function to calculate (B^N) % M using modular exponentiation
long modular_exponentiation(long base, long exponent, long modulus) {
    if (modulus == 1) {
        return 0;
    }
    long result = 1;
    base = base % modulus;
    // Perform exponentiation by squaring
    while (exponent > 0) {
        // If the current power is odd, multiply the result by the base
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}
int main() {
    long B, N, M;
    // Get the base value from the user
    printf("Enter the base B: ");
    if (scanf("%ld", &B) != 1 || B < 0) {
        printf("Base must be a positive number.\n");
        return 1;
    }
    // Get the exponent value
    printf("Enter the exponent N: ");
    if (scanf("%ld", &N) != 1 || N < 0) {
        printf("Exponent must be a positive number.\n");
        return 1;
    }
    // Get the modulus value
    printf("Enter the modulus M: ");
    if (scanf("%ld", &M) != 1 || M <= 1) {
        printf("Modulus must be greater than 1.\n");
        return 1;
    }
    // Calculate and print the result
    long result = modular_exponentiation(B, N, M);
    printf("\nResult of (%ld^%ld) %% %ld = %ld\n", B, N, M, result);
    return 0;
}
