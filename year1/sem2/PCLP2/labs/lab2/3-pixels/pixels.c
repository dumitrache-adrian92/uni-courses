#include "pixel.h"

void reversePic(Picture *pic) {
    int i, j;
    Pixel aux;
    for (i = 0; i < pic->height >> 1; i++) {
        for (j = 0; j < pic->width; j++) {
            aux = (*(*(pic->pix_array + i) + j));
			(*(*(pic->pix_array + i) + j)) = (*(*(pic->pix_array + pic->height - i - 1) + j));
			(*(*(pic->pix_array + pic->height - i - 1) + j)) = aux;
        }
    }
}

void colorToGray(Picture *pic) {
    for (int i = 0; i < pic->height; i++)
        for (int j = 0; j < pic->width; j++) {
            (*(*(pic->pix_array + i) + j)).R *= 0.3;
            (*(*(pic->pix_array + i) + j)).G *= 0.59;
            (*(*(pic->pix_array + i) + j)).B *= 0.11;
        }
}

int main() {
    int height, width;
    scanf("%d%d", &height, &width);
    Pixel **pix_array = generatePixelArray(height, width);
    Picture *pic = generatePicture(height, width, pix_array);

    printPicture(pic);

    reversePic(pic);
    printf("\n");
    printPicture(pic);

    freePicture(&pic);
    freePixelArray(&pix_array, height, width);

    return 0;
}
