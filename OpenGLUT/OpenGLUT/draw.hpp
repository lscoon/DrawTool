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

void drawDisplay();
void drawControl();

void drawButton(Button *b);
void DrawBitmap(long width, long height, unsigned char* bitmapImage);

void drawFPS();
void setOrthographicProjection();
void restorePerspectiveProjection();

#endif /* draw_hpp */
