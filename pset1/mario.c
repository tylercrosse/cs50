#include <cs50.h>
#include <stdio.h>

void build(int height);
void block(int blocks);
void space(int spaces);

int main(void) {
    int height;
    printf("Enter a pyramid height between 0 and 23\n");
    do {
        printf("Height: ");
        height = get_int();
    } while (height < 0 || height > 23);
    build(height);
    return 0;
}
void build(int height) {
    for (int i = 1; i < height + 1; i++) {
        space(height - i);
        block(i);
        printf("#\n");
    }
}
void block(int blocks) {
    for (int i = 0; i < blocks; i++) { printf("#"); }
}
void space(int spaces) {
    for (int i = 0; i < spaces; i++) { printf(" "); }
}