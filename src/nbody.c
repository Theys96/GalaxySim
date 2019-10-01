/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * Code file for nbody.h
 */

#include <stdio.h>
#include "nbody.h"
#include "image.h"

void renderUniverse(Universe u, char* filename, int width, int height, int cx, int cy, double scale) {
	cx += width/2;
	cy += height/2;

	Image img = newImage(width, height);

	Body a;
	int ax, ay;
	for (int i = 0; i < u.n; i++) {
		a = u.bodies[i];
		ax = (int)((a.x/scale+cx));
		ay = (int)((a.y/scale+cy));
		if ( ax >= 0 && ax < width && ay >= 0 && ay < height) {
			setPixel(img, ax, ay, 255);
		}
	}

	saveImage(img, filename);
	freeImage(img);
}

