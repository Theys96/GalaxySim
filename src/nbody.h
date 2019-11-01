/* 
 * Part of the GalaxySim project
 * by M.J. Havinga
 * 
 * Set of useful functions to set up and save universe states.
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
 *  - blackHoleMass  : maximum mass of a body to be rendered. For some simulations, it's desired to make heavy bodies invisible to simulate black holes.
 */
void renderUniverse(Universe u, char* filename, int cx, int cy, double scale, int width, int height, float blackHoleMass);

/* Saves the universe state to a CSV data file for later analysis.
 * Saves for every body the location in both Cartesian and polar coordinates.
 * Inputs:
 *  - u              : Universe struct to save.
 *  - filename       : string denoting the file to save the data to.
 */
void universeToCsv(Universe u, char* filename);


/* Sets up a Universe struct filled with a random set of bodies
 * distributed in a circle.
 * Inputs:
 *  - n              : Number of bodies to generate.
 *  - size           : Radius of the circle.
 *  - gapSize        : Radius of the empty circle in the center
 *                     around the center of mass.
 */
Universe newCircularUniverse(int n, int size, int gapSize);

/* Sets up a Universe struct filled with a random set of bodies
 * distributed in a spiral by placing the bodies in ellipses at
 * different angles.
 * Inputs:
 *  - n              : Number of bodies to generate.
 *  - size           : Radius of the spiral.
 *  - gapSize        : Radius of the empty circle in the center
 *                     around the center of mass.
 */
Universe newSpiralUniverse(int n, int size, int gapSize);

/* Takes two systems of bodies ("universes") and combines them into one, creating a new universe.
 * The universes may be given a new center position (0,0,0)->(x,y,z) and velocity.
 * These transformations are given as "Body" objects.
 * Inputs:
 *  - a, b         : The universes to combine.
 *  - a_transform  : The transformation vector for universe a.
 *  - b_transform  : The transformation vector for universe b.
 */
Universe combineUniverses(Universe a, Body a_transform, Universe b, Body b_transform);
