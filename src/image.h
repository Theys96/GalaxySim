typedef struct Image {
	int width;
	int height;
	int** img;
} Image;

Image newImage(int width, int height);
void saveImage(Image img, char* filename);
void freeImage(Image img);
