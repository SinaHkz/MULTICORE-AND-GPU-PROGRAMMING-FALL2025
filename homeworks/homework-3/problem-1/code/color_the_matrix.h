#ifndef COLOR_THE_MATRIX_H
#define COLOR_THE_MATRIX_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/*
 * Writes an N×N image using the RGB data in matrix
 * Output format: PPM (P6)
 */
void color(Pixel* matrix, int N);

#endif
