/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Return an error code if args provided is not 2 or 3
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // creates an interger n from the first arg (string) provided
    int n = atoi(argv[1]);

    // if a seed is provided, runs srand48 with the seed,
    // otherwise runs srand48 with time(), time() returns the time since
    // the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds. 
    // this greatly improves the chance of running the program with a random seed
    // srand48 is used to initialize the internal buffer r(n) of drand48.
    // where r(n) is called the seed of the random number generator.
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // return the output of drand48 * the LIMIT constant n times
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
