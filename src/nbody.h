/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * TODO: Library description to be written here.
 */

#include "bodies.h"

/* Renders a Universe onto an Image and saves it to a file.
 * This render is a straightforward projection of the first two dimensions and completely disregards the third (orthogonal projection)
 * Inputs:
 *  - u              : Universe struct to render.
 *  - filename       : string denoting the file to save the image to.
 *  - width, height  : desired width and height of the output image, in pixels.
 *  - cx, cy         : central coordinates of the render, where an object at location (cx,cy) will be rendered at approximatly (width/2, height/2).
 *  - scale          : scaling factor. Defaults to 1 which means a distance of 1 between objects will mean they are rendered at adjacent pixels.
 */
void renderUniverse(Universe u, char* filename, int width, int height, int cx, int cy, double scale);
