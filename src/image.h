
typedef char byte;

typedef struct Image {
	int width;
	int height;
	int bytewidth;
	byte** img;
} Image;

Image newImage(int width, int height);
void setPixel(Image img, int x, int y, int val);
void saveImage(Image img, char* filename);
void freeImage(Image img);
