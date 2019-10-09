#include "image.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Image newImage(int width, int height) {
  Image img;
  img.width = width;
  img.bytewidth = width % 8 == 0 ? width/8 : width/8 + 1;
  img.height = height;

  img.img = (byte**)calloc(height, sizeof(byte*));
  for (int y = 0; y < height; y++) {
    img.img[y] = calloc(img.bytewidth, sizeof(byte));
    memset(img.img[y], 255, img.bytewidth);
  }
  return img;
}

void setPixel(Image img, int x, int y, int val) {
  if (val) {
    img.img[y][x/8] &= ~(1UL << (7-x%8));
  } else {
    img.img[y][x/8] |= 1UL << (7-x%8);
  }
}

void saveImage(Image img, char* filename) {
  FILE* pgmimg = fopen(filename, "wb"); 

    fprintf(pgmimg, "P4\n");                              // Magic bytes
    fprintf(pgmimg, "%d %d\n", img.width, img.height);    // Dimensions
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.bytewidth ; j++) {
            fprintf(pgmimg, "%c", img.img[i][j]); 
        }
    }
    fprintf(pgmimg, "\n");
    fclose(pgmimg); 
}

void freeImage(Image img) {
  for (int i = 0; i < img.height; i++) { 
        free(img.img[i]);
    }
    free(img.img);
}
