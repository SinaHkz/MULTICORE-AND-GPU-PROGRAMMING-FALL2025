#include <stdio.h>
#include "color_the_matrix.h"

void color(Pixel* matrix, int N)
{
    FILE* fp = fopen("output.bmp", "wb");
    if (!fp) {
        perror("Failed to open output file");
        return;
    }

    // PPM header
    fprintf(fp, "P6\n%d %d\n255\n", N, N);

    // Write pixel data
    fwrite(matrix, sizeof(Pixel), N * N, fp);

    fclose(fp);
}
