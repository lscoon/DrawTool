//
//  draw.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "draw.hpp"
#include "font.hpp"
#include "bitmap.hpp"

extern int width1, height1, border;
extern void *font;

float red = 1.0f, green = 0.5f, blue = 0.5f;
float scale = 1.0f;

int frame;
long time, timebase = 0;
char s[50];

BITMAPINFOHEADER bitmapInfoHeader;
unsigned char *bitmapData;


void drawDisplay(){
    drawFPS();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f( -2.0f, -2.0f, 0.0f);
        glVertex3f( 2.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 2.0f, 0.0f);
    glEnd();
    bitmapData = LoadBitmapFile("test.bmp",&bitmapInfoHeader);
}

void drawControl(){
    glColor3f(0.0f, 0.6f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex3f(-2.5f, 9.0f, 0.0f);
        glVertex3f(-2.5f, -9.0f, 0.0f);
    glEnd();
    glLineWidth(1);
    
    Button b1 = {-1.5f, 5.0f, 3.0f, 1.5f};
    drawButton(&b1);
    Button b2 = {-1.5f, 2.0f, 3.0f, 1.5f};
    drawButton(&b2);
    Button b3 = {-1.5f, -1.0f, 3.0f, 1.5f};
    drawButton(&b3);
}

void drawButton(Button *b){
    if(b){
        glColor3f(0.0f, 0.0f, 0.8f);
        glBegin(GL_QUADS);
            glVertex3f(b->x, b->y, 0.0f);
            glVertex3f(b->x + b->w, b->y, 0.0f);
            glVertex3f(b->x + b->w, b->y + b->h, 0.0f);
            glVertex3f(b->x, b->y + b->h, 0.0f);
        glEnd();
    }
}

void drawBitmap(long width, long height, unsigned char* bitmapImage){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glRasterPos2i(0,0);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, bitmapImage);
}

void drawFPS(){
    glColor3f(1.0f, 1.0f, 1.0f);
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if(time - timebase >1000){
        sprintf(s, "FPS:%4.2f", frame * 1000.0 /(time - timebase));
        timebase = time;
        frame = 0;
    }
    
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(border, border * 5, 0, font, s);
    glPopMatrix();
    restorePerspectiveProjection();
}

void setOrthographicProjection(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width1, height1, 0);
    glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection(){
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
