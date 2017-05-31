/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

int rec_search(int value, int values[], int l, int r) {
    // sanity check
    if (r >= l) {
        int middle = l + (r - l)/2;
        // look at middle of array
        // if element you're looking for
        //     return true
        if (values[middle] == value) return value;
        // else if element is to left
        //     search left half of array
        else if (value < values[middle]) return rec_search(value, values, l, middle -1);
        // else if element is to right
        //     search right half of array
        else if (values[middle] < value) return rec_search(value, values, middle + 1, r);
    }
    // else
    //     return false
    return -1;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {
    int l = 0; 
    int r = n - 1;
    if (rec_search(value, values, l, r) > 0) return true;
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {
    // repeat until no swaps
    for (int i = 0; i < n - 1; i++) {
        // for i from 0 to n-2
        for (int j = 0; j < n - i - 1; j++) {
            // if i'th and i+1'th elements out of order
            if (values[j] > values[j+1]) {
                // swap them
                int tmp = values[j];
                values[j] = values[j+1];
                values[j+1] = tmp;    
            }
        }
    }
    for (int k = 0; k < n; k++) {
        printf("%i, ", values[k]);
    }
    return;
}
