/**
*
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // ensure proper usage
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover card.raw");
        return 1;
    }
    
    // === OPEN MEMORY CARD FILE ===
    char *infile = argv[1];
    
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    
    // === FIND BEGINNING OF JPEG ===
    // fread(data, size, number, inptr);
    // fread(buffer, 512, 1, inptr);
    // 0xff 0xd8 0xff
    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {
            
    }
    
    // === OPEN A NEW JPEG ===
    // sprintf(filename, "%031.jpg", 2);
    // FILE *img = fopen(filename, "w");
    
    // === WRITE 512 BYTES UNTIL NEW JPEG IS FOUND
    // fwrite(data, size, number, outptr);
    
    
    // === DETECT END OF FILE ===


    // close infile
    fclose(inptr);

    // success
    return 0;   
}