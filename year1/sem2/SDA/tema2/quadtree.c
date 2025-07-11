#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QuadtreeNode {
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

/* structura unui pixel, folosita pentru a reprezenta imagini intregi
   (prin format de matrice spre exemplu) */
typedef struct pixel {
    unsigned char red, green, blue;
} pixel;

/* structura de arbore cuaternar, contine aceleasi informatii ca si QuadtreeNode
   dar are legaturi directe catre celelalte noduri din arbore*/
typedef struct Quadtree {
    unsigned char blue, green, red;
    uint32_t area;
    struct Quadtree *top_left, *top_right;
    struct Quadtree *bottom_left, *bottom_right;
} Quadtree;

// calculeaza numarul de cifre ale unui numar dat x
int digits(int x) {
    int count = 0;
    do {
        count++;
        x /= 10;
    } while (x != 0);
    return count;
}

// converteste un sir de caractere in valoarea sa numerica (doar pentru numere naturale)
int charToInt(char *a) {
    int x;
    x = 0;
    for (int i = 0; a[i] != '\0'; i++)
        x = x * 10 + (a[i] - '0');
    return x;
}

// creeaza matricea de pixeli a imaginii date in sirul de caractere name
void readImage(pixel **image, char *name, int offset, int size) {
    FILE *f = fopen(name, "rb");
    int i, j;
    fseek(f, offset, SEEK_SET); // sarim peste antet
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++) {
            fread(&image[i][j].red, sizeof(unsigned char), 1, f);
            fread(&image[i][j].green, sizeof(unsigned char), 1, f);
            fread(&image[i][j].blue, sizeof(unsigned char), 1, f);
        }
    fclose(f);
}

// creeaza arborele cuaternar din matricea de pixeli intr-un mod recursiv
void createQuadtree(Quadtree **quad, pixel **image, int x, int y, uint32_t size, int prag) {
    int64_t sum = 0, div = 3.0 * size * size, mean;
    int64_t rSum, gSum, bSum;
    unsigned char r, g, b;
    rSum = gSum = bSum = 0;
    int i, j;
    *quad = malloc(sizeof(Quadtree));
    (*quad)->area = size * size;
    (*quad)->bottom_left = (*quad)->bottom_right = (*quad)->top_left = (*quad)->top_right = NULL;

    // determinare valori medii rgb pentru blocul reprezentat de nodul quad
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++) {
            rSum += (int)image[i][j].red;
            gSum += (int)image[i][j].green;
            bSum += (int)image[i][j].blue;
        }
    r = rSum / (size * size);
    g = gSum / (size * size);
    b = bSum / (size * size);
    (*quad)->red = r;
    (*quad)->green = g;
    (*quad)->blue = b;

    // calculare mean
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++) {
            sum += (r - (int)image[i][j].red) * (r - (int)image[i][j].red) + (g - (int)image[i][j].green) * (g - image[i][j].green) + (b - image[i][j].blue) * (b - image[i][j].blue);
        }
    mean = sum / div;

    // daca mean trece de prag, continuam sa creeam noduri
    if (mean <= prag)
        return;

    createQuadtree(&((*quad)->top_left), image, x, y, size / 2, prag);
    createQuadtree(&((*quad)->top_right), image, x, y + size / 2, size / 2, prag);
    createQuadtree(&((*quad)->bottom_right), image, x + size / 2, y + size / 2, size / 2, prag);
    createQuadtree(&((*quad)->bottom_left), image, x + size / 2, y, size / 2, prag);
}

// numara cate noduri si cate culori avem in arbore
void quadtreeCount(Quadtree *quad, uint32_t *numar_culori, uint32_t *numar_noduri) {
    *numar_noduri += 1;
    if (quad->bottom_left != NULL) {
        quadtreeCount(quad->top_left, numar_culori, numar_noduri);
        quadtreeCount(quad->top_right, numar_culori, numar_noduri);
        quadtreeCount(quad->bottom_right, numar_culori, numar_noduri);
        quadtreeCount(quad->bottom_left, numar_culori, numar_noduri);
        return;
    }
    *numar_culori += 1;
}

// transforma recursiv arborele cuaternar intr-un vector conform cerintei
void createVector(Quadtree *quad, QuadtreeNode *vector, int *i) {
    int i2;
    vector[*i].blue = quad->blue;
    vector[*i].green = quad->green;
    vector[*i].red = quad->red;
    vector[*i].area = quad->area;
    if (quad->bottom_left != NULL) {
        i2 = *i;
        *i += 1;
        vector[i2].top_left = *i;
        createVector(quad->top_left, vector, i);

        *i += 1;
        vector[i2].top_right = *i;
        createVector(quad->top_right, vector, i);

        *i += 1;
        vector[i2].bottom_right = *i;
        createVector(quad->bottom_right, vector, i);

        *i += 1;
        vector[i2].bottom_left = *i;
        createVector(quad->bottom_left, vector, i);
    } else {
        vector[*i].top_left = -1;
        vector[*i].top_right = -1;
        vector[*i].bottom_left = -1;
        vector[*i].bottom_right = -1;
    }
}

// elibereaza memoria alocata arborelui recursiv
void freeQuadtree(Quadtree *quad) {
    if (quad == NULL)
        return;
    freeQuadtree(quad->top_left);
    freeQuadtree(quad->top_right);
    freeQuadtree(quad->bottom_right);
    freeQuadtree(quad->bottom_left);
    free(quad);
}

// transforma vectorul de noduri in arbore recursiv
void vectorToQuadtree(QuadtreeNode *vector, Quadtree **quad, int i) {
    *quad = malloc(sizeof(Quadtree));
    (*quad)->area = vector[i].area;
    (*quad)->blue = vector[i].blue;
    (*quad)->green = vector[i].green;
    (*quad)->red = vector[i].red;
    if (vector[i].top_left == -1)
        (*quad)->bottom_left = (*quad)->bottom_right = (*quad)->top_left = (*quad)->top_right = NULL;
    else {
        vectorToQuadtree(vector, &(*quad)->bottom_left, vector[i].bottom_left);
        vectorToQuadtree(vector, &(*quad)->bottom_right, vector[i].bottom_right);
        vectorToQuadtree(vector, &(*quad)->top_left, vector[i].top_left);
        vectorToQuadtree(vector, &(*quad)->top_right, vector[i].top_right);
    }
}

// transforma arborele cuaternar intr-o matrice de pixeli recursiv
void quadtreeToImage(Quadtree *quad, pixel **image, int size, int x, int y) {
    int i, j;
    if (quad->bottom_left == NULL) {
        for (i = x; i < x + size; i++)
            for (j = y; j < y + size; j++) {
                image[i][j].blue = quad->blue;
                image[i][j].green = quad->green;
                image[i][j].red = quad->red;
            }
        return;
    }
    quadtreeToImage(quad->top_left, image, size / 2, x, y);
    quadtreeToImage(quad->top_right, image, size / 2, x, y + size / 2);
    quadtreeToImage(quad->bottom_left, image, size / 2, x + size / 2, y);
    quadtreeToImage(quad->bottom_right, image, size / 2, x + size / 2, y + size / 2);
}

// scrie pixelii imaginii intr-un fisier binar conform formatului ppm P6
void writeImageToFile(pixel **image, char *name, int size) {
    FILE *output;
    int i;
    output = fopen(name, "wb");
    fprintf(output, "P6\n");
    fprintf(output, "%d %d\n", size, size);
    fprintf(output, "%d\n", 255);
    fclose(output);
    output = fopen(name, "ab");
    for (i = 0; i < size; i++)
        fwrite(image[i], sizeof(pixel), size, output);
    fclose(output);
}

// oglindire orizontala
void hMirror(Quadtree *quad) {
    Quadtree *p;
    p = quad->bottom_left;
    quad->bottom_left = quad->bottom_right;
    quad->bottom_right = p;
    p = quad->top_left;
    quad->top_left = quad->top_right;
    quad->top_right = p;
    if (quad->bottom_left != NULL) {
        hMirror(quad->bottom_left);
        hMirror(quad->bottom_right);
        hMirror(quad->top_left);
        hMirror(quad->top_right);
    }
}

// oglindire verticala
void vMirror(Quadtree *quad) {
    Quadtree *p;
    p = quad->bottom_left;
    quad->bottom_left = quad->top_left;
    quad->top_left = p;
    p = quad->top_right;
    quad->top_right = quad->bottom_right;
    quad->bottom_right = p;
    if (quad->bottom_left != NULL) {
        vMirror(quad->bottom_left);
        vMirror(quad->bottom_right);
        vMirror(quad->top_left);
        vMirror(quad->top_right);
    }
}

int main(int argc, char **argv) {
    FILE *f, *output;
    pixel **image;
    uint32_t numar_culori = 0, numar_noduri = 0;
    uint32_t width, height, maxColor;
    Quadtree *quad = NULL;
    QuadtreeNode *vector = NULL;
    char type[20];
    int i, j;
    int prag, offset;
    if (!strcmp(argv[1], "-c")) {
        prag = charToInt(argv[2]);
        f = fopen(argv[3], "r");
        output = fopen(argv[4], "wb");
        // citire header
        fscanf(f, "%s", type);
        fscanf(f, "%u%u%u", &width, &height, &maxColor);
        image = malloc(height * sizeof(pixel *));

        // citire pixeli
        for (i = 0; i < height; i++)
            image[i] = malloc(width * sizeof(pixel));
        fclose(f);
        // punctul unde incepe partea binara a fisierului PPM
        offset = 4 + digits(width) + digits(height) + digits(maxColor) + strlen(type);
        readImage(image, argv[3], offset, width);

        // compresie
        createQuadtree(&quad, image, 0, 0, width, prag);
        quadtreeCount(quad, &numar_culori, &numar_noduri);

        // scriere fisier output
        vector = malloc(numar_noduri * sizeof(QuadtreeNode));
        j = 0;
        createVector(quad, vector, &j);
        fwrite(&numar_culori, sizeof(uint32_t), 1, output);
        fwrite(&numar_noduri, sizeof(uint32_t), 1, output);
        for (i = 0; i < numar_noduri; i++)
            fwrite(&vector[i], sizeof(QuadtreeNode), 1, output);

        // eliberare memorie
        free(vector);
        fclose(output);
        for (i = 0; i < height; i++)
            free(image[i]);
        free(image);
        freeQuadtree(quad);
    } else if (!strcmp(argv[1], "-d")) {
        f = fopen(argv[2], "rb");

        // citire fisier output
        fread(&numar_culori, sizeof(uint32_t), 1, f);
        fread(&numar_noduri, sizeof(uint32_t), 1, f);
        vector = malloc(numar_noduri * sizeof(QuadtreeNode));
        fread(vector, sizeof(QuadtreeNode), numar_noduri, f);
        width = height = sqrt(vector[0].area);

        // creeare imagine
        image = malloc(height * sizeof(pixel *));
        for (i = 0; i < height; i++)
            image[i] = malloc(width * sizeof(pixel));
        vectorToQuadtree(vector, &quad, 0);
        quadtreeToImage(quad, image, width, 0, 0);
        writeImageToFile(image, argv[3], width);

        // eliberare memorie
        for (i = 0; i < height; i++)
            free(image[i]);
        free(image);
        freeQuadtree(quad);
        free(vector);
        fclose(f);
    } else if (!strcmp(argv[1], "-m")) {
        f = fopen(argv[4], "r");
        prag = charToInt(argv[3]);

        // citire header
        fscanf(f, "%s", type);
        fscanf(f, "%u%u%u", &width, &height, &maxColor);

        // citire imagine
        image = malloc(height * sizeof(pixel *));
        for (i = 0; i < height; i++)
            image[i] = malloc(width * sizeof(pixel));
        fclose(f);
        offset = 4 + digits(width) + digits(height) + digits(maxColor) + strlen(type);
        readImage(image, argv[4], offset, width);

        // quadtree
        createQuadtree(&quad, image, 0, 0, width, prag);

        // mirror
        if (!strcmp(argv[2], "h"))
            hMirror(quad);
        else if (!strcmp(argv[2], "v"))
            vMirror(quad);

        // scriere quadtree in ppm
        quadtreeToImage(quad, image, width, 0, 0);
        writeImageToFile(image, argv[5], width);
        for (i = 0; i < height; i++)
            free(image[i]);
        free(image);
        freeQuadtree(quad);
    }
}