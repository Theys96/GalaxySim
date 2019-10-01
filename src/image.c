#include "image.h"
#include <stdlib.h>
#include <stdio.h>

Image newImage(int width, int height) {
	Image img;
	img.width = width;
	img.height = height;

	img.img = (int**)calloc(height, sizeof(int*));
	for (int y = 0; y < height; y++) {
		img.img[y] = calloc(width, sizeof(int));
	}
	return img;
}

void saveImage(Image img, char* filename) {
	FILE* pgmimg; 
    pgmimg = fopen(filename, "wb"); 

    fprintf(pgmimg, "P2\n");								// Magic bytes
    fprintf(pgmimg, "%d %d\n", img.width, img.height);		// Dimensions
    fprintf(pgmimg, "255\n");								// Upper value
    for (int i = 0; i < img.height; i++) { 
        for (int j = 0; j < img.width; j++) {
            fprintf(pgmimg, "%d ", img.img[i][j]); 
        } 
        fprintf(pgmimg, "\n"); 
    }
    fclose(pgmimg); 
}

void freeImage(Image img) {
	for (int i = 0; i < img.height; i++) { 
        free(img.img[i]);
    }
    free(img.img);
}
