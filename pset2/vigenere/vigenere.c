#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cipher(string key) {
    printf("plaintext:  ");
    string p = get_string();
    int j = 0;
    int keylen = strlen(key);
    if (p != NULL) {
        printf("ciphertext: ");
        for (int i = 0, n = strlen(p); i < n; i++) {
            char k = toupper(key[j]) - 65;
            char c;
            // uppercase letters
            if (p[i] >= 65 && p[i] <= 90) {
                c = ((p[i] - 65 + k) % 26) + 65;
                j = (j + 1) % keylen;
            // lowercase letters
            } else if (p[i] >= 97 && p[i] <= 122) {
                c = ((p[i] - 97 + k) % 26) + 97;
                j = (j + 1) % keylen;
            // nonletter chars
            } else {
                c = p[i];
            }
            printf("%c", c);
        }
        printf("\n");
    }
}

int main(int argc, string argv[]) {
    // check arg count
    if (argc != 2) {
        printf("error: missing command-line argument\n");
        return 1;
    } 
    
    // check arg is alphabetical
    string key = argv[1];
    for (int i = 0, n = strlen(key); i < n; i++) {
        if (isalpha(key[i]) == 0) {
            printf("error: argument must ccontian only alphabetical characters\n");
            return 1;
        }
    }
    cipher(key);
    return 0;
}

