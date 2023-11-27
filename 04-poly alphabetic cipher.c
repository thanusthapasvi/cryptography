#include <stdio.h>
#include <string.h>

int main() {
    char key[30], text[100], cipher[100];
    char k = 0;

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the text: ");
    scanf("%s", text);

    for (k; k < strlen(text); ++k)
        if (isalpha(text[k])) {
            char shift = key[k % strlen(key)];
            char base = isupper(text[k]) ? 'A' : 'a';
            cipher[k] = base + (text[k] - base + (shift - base + 26) % 26) % 26;
        } else {
            cipher[k] = text[k];
        }
    cipher[k] = '\0';
    printf("Cipher: %s\n", cipher);
    return 0;
}
