#include <cs50.h>
#include <stdio.h>

void make_change(float change_owed);

int main(void) {
    float change_owed;
    
    printf("O hai! ");
    do {
        printf("How much change is owed?\n");
        change_owed = get_float();
    } while (change_owed < 0);
    make_change(change_owed);
}

void make_change(float change_owed) {
    int coins = 0;
    while (change_owed > 0.001) {
        if (change_owed - 0.25 >= -0.001) {
            change_owed -= 0.25;
            coins++;
        } else if (change_owed - 0.10 >= -0.001) {
            change_owed -= 0.10;
            coins++;
        } else if (change_owed - 0.05 >= -0.001) {
            change_owed -= 0.05;
            coins++;
        } else {
            change_owed -= 0.01;
            coins++;
        }
    }
    printf("%i\n", coins);
}