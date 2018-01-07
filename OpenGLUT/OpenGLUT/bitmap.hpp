//
//  bitmap.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/11.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef bitmap_hpp
#define bitmap_hpp

#define BITMAP_ID 0x4D42
#define BI_RGB 0x0000

typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;

typedef struct BitmapFileHeader{
    WORD type;
    DWORD size;
    WORD reserved1;
    WORD reserved2;
    DWORD offbits;
}BITMAPFILEHEADER;

typedef struct BitmapInfoHeader{
    DWORD size;
    LONG width;
    LONG height;
    WORD planes;
    WORD bitCount;
    DWORD compression;
    DWORD sizeImage;
    LONG xPelsPerMeter;
    LONG yPelsPerMeter;
    DWORD clrUsed;
    DWORD clrImportant;
}BITMAPINFOHEADER;

unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
bool WriteBitmapFile(char *filename, int width, int height, unsigned char * bitmapData);

#endif /* bitmap_hpp */
