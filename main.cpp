#include <iostream>

struct FileH {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
};

struct PictureH {
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

void describe() {
    FileH F;
    PictureH P;
    FILE* sourceFile = fopen("test.bmp", "rb");

    fread(&F.bfType, sizeof(F.bfType), 1, sourceFile);
    printf("F.bfType: %x \n", F.bfType);
    fread(&F.bfSize, sizeof(F.bfSize), 1, sourceFile);
    printf("F.bfSize \n", F.bfSize);
    fread(&F.bfReserved1, sizeof(F.bfReserved1), 1, sourceFile);
    printf("F.bfReserved2: %d \n", F.bfReserved1);
    fread(&F.bfReserved2, sizeof(F.bfReserved2), 1, sourceFile);
    printf("F.bfReserved2: %d \n", F.bfReserved2);
    fread(&F.bfOffBits, sizeof(F.bfOffBits), 1, sourceFile);
    printf("F.bfOffBits: %d \n", F.bfOffBits);

    fseek(sourceFile, 14, SEEK_SET);
    fread(&P.biSize, sizeof(P.biSize), 1, sourceFile);
    printf("P.biSize: %d \n", P.biSize);
    fread(&P.biWidth, sizeof(P.biWidth), 1, sourceFile);
    printf("P.biWidt: %d \n", P.biWidth);
    fread(&P.biHeight, sizeof(P.biHeight), 1, sourceFile);
    printf("P.biHeight: %d \n", P.biHeight);
    fread(&P.biPlanes, sizeof(P.biPlanes), 1, sourceFile);
    printf("P.biPlanes: %d \n", P.biPlanes);
    fread(&P.biBitCount, sizeof(P.biBitCount), 1, sourceFile);
    printf("P.biBitCount: %d \n", P.biBitCount);
    fread(&P.biCompression, sizeof(P.biCompression), 1, sourceFile);
    printf("P.biCompression): %d \n", P.biCompression);
    fread(&P.biSizeImage, sizeof(P.biSizeImage), 1, sourceFile);
    printf("P.biSizeImage: %d \n", P.biSizeImage);
    fread(&P.biXPelsPerMeter, sizeof(P.biXPelsPerMeter), 1, sourceFile);
    printf("P.biXPelsPerMeter: %d \n", P.biXPelsPerMeter);
    fread(&P.biYPelsPerMeter, sizeof(P.biYPelsPerMeter), 1, sourceFile);
    printf("P.biYPelsPerMeter: %d \n", P.biYPelsPerMeter);
    fread(&P.biClrUsed, sizeof(P.biClrUsed), 1, sourceFile);
    printf("P.biClrUsed: %d \n", P.biClrUsed);
    fread(&P.biClrImportant, sizeof(P.biClrImportant), 1, sourceFile);
    printf("P.biClrImportant: %d \n", P.biClrImportant);

    fclose(sourceFile);
}

void negative() {
    FileH F;
    PictureH P;

    FILE* sourceFile = fopen("test.bmp", "rb");
    FILE* negativeFile = fopen("negative.bmp", "wb");

    fseek(negativeFile, 0, SEEK_SET);
    fwrite(&F.bfType, sizeof(F.bfType), 1, negativeFile);
    fwrite(&F.bfSize, sizeof(F.bfSize), 1, negativeFile);
    fwrite(&F.bfReserved1, sizeof(F.bfReserved1), 1, negativeFile);
    fwrite(&F.bfReserved2, sizeof(F.bfReserved2), 1, negativeFile);
    fwrite(&F.bfOffBits, sizeof(F.bfOffBits), 1, negativeFile);

    fseek(negativeFile, 14, SEEK_SET);
    fwrite(&P.biSize, sizeof(P.biSize), 1, negativeFile);
    fwrite(&P.biWidth, sizeof(P.biWidth), 1, negativeFile);
    fwrite(&P.biHeight, sizeof(P.biHeight), 1, negativeFile);
    fwrite(&P.biPlanes, sizeof(P.biPlanes), 1, negativeFile);
    fwrite(&P.biBitCount, sizeof(P.biBitCount), 1, negativeFile);
    fwrite(&P.biCompression, sizeof(P.biCompression), 1, negativeFile);
    fwrite(&P.biSizeImage, sizeof(P.biSizeImage), 1, negativeFile);
    fwrite(&P.biXPelsPerMeter, sizeof(P.biXPelsPerMeter), 1, negativeFile);
    fwrite(&P.biYPelsPerMeter, sizeof(P.biYPelsPerMeter), 1, negativeFile);
    fwrite(&P.biClrUsed, sizeof(P.biClrUsed), 1, negativeFile);
    fwrite(&P.biClrImportant, sizeof(P.biClrImportant), 1, negativeFile);

    fseek(negativeFile, sizeof(F.bfOffBits), SEEK_SET);

    int img;
    for (int i = F.bfOffBits; i < F.bfSize; i++)
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
    describe();
    negative();
    return 0;
}