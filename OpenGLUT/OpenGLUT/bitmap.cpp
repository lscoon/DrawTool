//
//  bitmap.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/11.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include "bitmap.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader){
    FILE *filePtr;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *bitmapImage;
    
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL)
        return NULL;
    
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    
    if(bitmapFileHeader.type != 'BM'){
        fclose(filePtr);
        return NULL;
    }
    
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    fseek(filePtr, bitmapFileHeader.offbits, SEEK_SET);
    
    bitmapImage = (unsigned char*) malloc(bitmapInfoHeader->sizeImage);
    if(bitmapImage == NULL){
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
    
    fread(bitmapImage, 1, bitmapInfoHeader->sizeImage, filePtr);
    if(bitmapImage ==NULL){
        fclose(filePtr);
        return NULL;
    }
    
    unsigned char tempRGB;
    for(int imageIdx = 0; imageIdx < bitmapInfoHeader->sizeImage; imageIdx += 3){
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx +2] = tempRGB;
    }
    
    fclose(filePtr);
    return bitmapImage;
}

bool WriteBitmapFile(char *filename, int width, int height, unsigned char * bitmapData){
    BITMAPFILEHEADER bitmapFileHeader;
    memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
    bitmapFileHeader.size = sizeof(BITMAPFILEHEADER);
    bitmapFileHeader.type = BITMAP_ID;
    bitmapFileHeader.offbits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    BITMAPINFOHEADER bitmapInfoHeader;
    memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.size = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.width = width;
    bitmapInfoHeader.height = height;
    bitmapInfoHeader.planes = 1;
    bitmapInfoHeader.bitCount = 24;
    bitmapInfoHeader.compression = BI_RGB;
    bitmapInfoHeader.sizeImage = width * abs(height) *3;
    
    unsigned char tempRGB;
    for(int imageIdx = 0; imageIdx < bitmapInfoHeader.sizeImage; imageIdx += 3){
        tempRGB = bitmapData[imageIdx];
        bitmapData[imageIdx] = bitmapData[imageIdx + 2];
        bitmapData[imageIdx +2] = tempRGB;
    }
    
    FILE *filePtr;
    filePtr = fopen(filename, "wb");
    if(filePtr == NULL)
        return false;
    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    fwrite(bitmapData, bitmapInfoHeader.size, 1, filePtr);
    fclose(filePtr);
    return true;
}

