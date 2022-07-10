#include <iostream>

struct BMP_header
{
    char name[2];
    unsigned int size;
    unsigned short int reserved_1;
    unsigned short int reserved_2;
    unsigned int offset;
}h_bmp;

struct DIB_header{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short int planes;
    unsigned short int bitPerPixel;
    unsigned int compresion;
    unsigned int imageSize;
    unsigned int xPelsPerMeter;
    unsigned int yPelsPerMeter;
    unsigned int colorUsed;
    unsigned int colorImportant;

}h_dib;

void negative() {
    FILE* sourceFile = fopen("test.bmp", "rb");
    FILE* negativeFile = fopen("negative.bmp", "wb");

    fwrite(&h_bmp.name[0], 1, 1, negativeFile);
    fwrite(&h_bmp.name[1], 1, 1, negativeFile);
    fwrite(&h_bmp.size, sizeof(h_bmp.size), 1, negativeFile);
    fwrite(&h_bmp.reserved_1, sizeof(h_bmp.reserved_1), 1, negativeFile);
    fwrite(&h_bmp.reserved_2, sizeof(h_bmp.reserved_2), 1, negativeFile);
    fwrite(&h_bmp.offset, sizeof(h_bmp.offset), 1, negativeFile);
    fwrite(&h_dib, sizeof(struct DIB_header), 1, negativeFile);

    int img;
    for (int i = h_bmp.offset; i < h_bmp.size; i++)
    {
        fseek(sourceFile, i, SEEK_SET);
        fseek(negativeFile, i, SEEK_SET);
        fread(&img, 3, 1, sourceFile);
        img = INT_MAX - img;
        fwrite(&img, 3, 1, negativeFile);
    }

    fclose(sourceFile);
    fclose(negativeFile);
}

int main() {
    negative();
    return 0;
}