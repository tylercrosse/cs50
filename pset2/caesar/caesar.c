#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cipher(int k) {
    printf("plaintext:  ");
    string s = get_string();
    if (s != NULL) {
        printf("ciphertext: ");
        for (int i = 0, n = strlen(s); i < n; i++) {
            char c;
            // uppercase letters
            if (s[i] >= 65 && s[i] <= 90) {
                c = ((s[i] - 65 + k) % 26) + 65;
            // lowercase letters
            } else if (s[i] >= 97 && s[i] <= 122) {
                c = ((s[i] - 97 + k) % 26) + 97;
            // nonletter chars
            } else {
                c = s[i];
            }
            printf("%c", c);
        }
        printf("\n");
    }
}

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("error: missing command-line argument\n");
        return 1;
    }
    int k = atoi(argv[1]);
    cipher(k);
    return 0;
}

