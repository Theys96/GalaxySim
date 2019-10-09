/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * Simple library to create and save binary images
 * in an efficient format.
 */

typedef char byte;

typedef struct Image {
  int width;
  int height;
  int bytewidth;
  byte** img;
} Image;

/* Creates a new Image struct with a given width and height,
 * allocating the required memory for the pixels.
 * Inputs:
 *  - width   : Width of the image.
 *  - height   : Height of the image.
 */
Image newImage(int width, int height);

/* Sets a single pixel in a given image to black or white.
 * The parameter `val` denotes black (0) or white (>0).
 * Inputs:
 *  - img      : Image struct representing the image to draw on.
 *  - x, y     : Coordinates of the pixel to draw
 *  - val      : Color of the pixel (0 = black, >0 = white)
 */
void setPixel(Image img, int x, int y, int val);

/* Saves the image represented in the Image struct to a file.
 * Inputs:
 *  - img       : Image struct representing the image to save.
 *  - filename  : string denoting the file to save the image to.
 */
void saveImage(Image img, char* filename);

/* Frees an image struct and the associated memory.
 * Inputs:
 *  - img       : Image struct representing the image to free.
 */
void freeImage(Image img);
