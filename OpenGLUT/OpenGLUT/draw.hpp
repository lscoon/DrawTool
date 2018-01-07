//
//  draw.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef draw_hpp
#define draw_hpp

typedef struct Button{
    float x;
    float y;
    float w;
    float h;
}Button;

void draw();
void drawDDA(int startx, int starty, int endx, int endy);
void drawBresenham(int startx, int starty, int endx, int endy);
void drawCircle(int x0, int y0, int r);
void drawOval(int x0, int y0, int a, int b);

void drawButton(Button *b);
void drawBitmap(long width, long height, unsigned char* bitmapImage);

void drawFPS();
void setOrthographicProjection();
void restorePerspectiveProjection();

#endif /* draw_hpp */
