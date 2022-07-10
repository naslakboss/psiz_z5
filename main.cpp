#include <iostream>

struct FileHeader {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
};

struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
};

void negative() {
    FileHeader File;
    PictureHeader Picture;

    FILE* sourceFile = fopen("test.bmp", "rb");
    FILE* negativeFile = fopen("negative.bmp", "wb");

    fseek(negativeFile, 0, SEEK_SET);
    fwrite(&File.bfType, sizeof(File.bfType), 1, negativeFile);
    fwrite(&File.bfSize, sizeof(File.bfSize), 1, negativeFile);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, negativeFile);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, negativeFile);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, negativeFile);

    fseek(negativeFile, 14, SEEK_SET);
    fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, negativeFile);
    fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, negativeFile);
    fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, negativeFile);
    fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, negativeFile);
    fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, negativeFile);
    fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, negativeFile);
    fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, negativeFile);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, negativeFile);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, negativeFile);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, negativeFile);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, negativeFile);

    fseek(negativeFile, sizeof(File.bfOffBits), SEEK_SET);

    int img;
    for (int i = File.bfOffBits; i < File.bfSize; i++)
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

void describe() {
    FileHeader File;
    PictureHeader Picture;
    FILE* sourceFile = fopen("test.bmp", "rb");

    fread(&File.bfType, sizeof(File.bfType), 1, sourceFile);
    printf("File.bfType: %x \n", File.bfType);
    fread(&File.bfSize, sizeof(File.bfSize), 1, sourceFile);
    printf("File.bfSize \n", File.bfSize);
    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, sourceFile);
    printf("File.bfReserved2: %d \n", File.bfReserved1);
    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, sourceFile);
    printf("File.bfReserved2: %d \n", File.bfReserved2);
    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, sourceFile);
    printf("File.bfOffBits: %d \n", File.bfOffBits);

    fseek(sourceFile, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, sourceFile);
    printf("Picture.biSize: %d \n", Picture.biSize);
    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, sourceFile);
    printf("Picture.biWidt: %d \n", Picture.biWidth);
    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, sourceFile);
    printf("Picture.biHeight: %d \n", Picture.biHeight);
    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, sourceFile);
    printf("Picture.biPlanes: %d \n", Picture.biPlanes);
    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, sourceFile);
    printf("Picture.biBitCount: %d \n", Picture.biBitCount);
    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, sourceFile);
    printf("Picture.biCompression): %d \n", Picture.biCompression);
    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, sourceFile);
    printf("Picture.biSizeImage: %d \n", Picture.biSizeImage);
    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, sourceFile);
    printf("Picture.biXPelsPerMeter: %d \n", Picture.biXPelsPerMeter);
    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, sourceFile);
    printf("Picture.biYPelsPerMeter: %d \n", Picture.biYPelsPerMeter);
    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, sourceFile);
    printf("Picture.biClrUsed: %d \n", Picture.biClrUsed);
    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, sourceFile);
    printf("Picture.biClrImportant: %d \n", Picture.biClrImportant);

    fclose(sourceFile);
}

int main() {
    describe();
    negative();
    return 0;
}