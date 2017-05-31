/**
 * Rsizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[]) {
    // ensure proper usage
    if (argc != 4) {
        fprintf(stderr, "Usage: ./resize n infile outfile, where:\n"
                        "  n = positive integer <= 100\n"
                        "  infile = BMP to be resized\n"
                        "  outfile = name of resized BMP\n");
        return 1;
    }

    // remember filenames
    int n = strtol(argv[1], NULL, 10);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inBF;
    fread(&inBF, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inBI;
    fread(&inBI, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inBF.bfType != 0x4d42 || inBF.bfOffBits != 54 || inBI.biSize != 40 || 
        inBI.biBitCount != 24 || inBI.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // create structures for out file
    BITMAPFILEHEADER outBF = inBF;
    BITMAPINFOHEADER outBI = inBI;
    
    // determine new width & height
    outBI.biWidth = inBI.biWidth * n;
    outBI.biHeight = inBI.biHeight * n;

    // determine padding for scanlines
    int inPadding = (4 - (inBI.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (outBI.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // deterimine out image size
    outBI.biSizeImage = (outBI.biWidth * sizeof(RGBTRIPLE) + outPadding) * abs(outBI.biHeight);
    outBF.bfSize = inBF.bfSize - inBI.biSizeImage + outBI.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outBF, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outBI, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inBI.biHeight); i < biHeight; i++) {
        
        // reach each scanline n times
        for (int j = 0; j < n; j++) {
        
            // iterate over pixels in scanline
            for (int k = 0; k < inBI.biWidth; k++) {
                
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile n times
                for (int l = 0; l < n; l++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                }
            }
            
            // add new padding if any
            for (int h = 0; h < outPadding; h++) {
                fputc(0x00, outptr);
            }
            
            // reset position in scanline for next iteration
            if (j < n - 1) {
                long offset = inBI.biWidth * sizeof(RGBTRIPLE);
                fseek(inptr, -offset, SEEK_CUR);
            }
            
        }


        // skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
