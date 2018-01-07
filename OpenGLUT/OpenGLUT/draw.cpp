//
//  draw.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>

#include "draw.hpp"
#include "mouse.hpp"
#include "font.hpp"
#include "bitmap.hpp"

extern int width, height;
extern Mouse myMouse;
extern void *font;

float red = 1.0f, green = 0.5f, blue = 0.5f;
float scale = 1.0f;

int frame;
long timenow, timebase = 0;
char s[50];

BITMAPINFOHEADER bitmapInfoHeader;
unsigned char *bitmapData;

void draw(){
    glColor3f(1.0f, 0.0f, 0.0f);
    //drawDDA(myMouse.xpress, height - myMouse.ypress, myMouse.x, height - myMouse.y);
    drawOval(myMouse.x, height - myMouse.y, 30,20);
    //const char *fileName = "/Users/apple/Documents/Photos/bear.bmp";
    //bitmapData = LoadBitmapFile(fileName, &bitmapInfoHeader);
    //if(bitmapData == NULL)
        //std::cout<<"kkk"<<std::endl;
    drawFPS();
}

void drawDDA(int startx, int starty, int endx, int endy){
    glBegin(GL_POINTS);
    float dx,dy,k;
    dx = endx - startx;
    dy = endy - starty;
    k = dy/dx;
    if(k <= 1){
        float y = starty;
        for(int x = startx; x <= endx; x++){
            glVertex2i(x, int(y + 0.5));
            y = y+k;
        }
    }
    else{
        k = dx/dy;
        float x = startx;
        for(int y = starty; y <= endy; y++){
            glVertex2i(int(x + 0.5), y);
            x = x + k;
        }
    }
    glEnd();
}

void drawBresenham(int startx, int starty, int endx, int endy){
    glBegin(GL_POINTS);
    int x,y,dx,dy,s1,s2,p,interchange;
    x = startx;
    y = starty;
    dx = endx - startx;
    dy = endy - starty;
    
    if(endx > startx)
        s1 = 1;
    else s1 = -1;
    if(endy > starty)
        s2 = 1;
    else s2 = -1;
    
    if(dy > dx){
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else interchange = 0;
    
    p = 2*dy - dx;
    for(int i = 1;i <= dx; i++){
        glVertex2i(x, y);
        if( p >= 0){
            if( interchange == 0)
                y = y + s2;
            else x = x + s1;
            p = p - 2*dx;
        }
        else{
            if(interchange == 0)
                x = x + s1;
            else y = y +s2;
            p = p + 2*dy;
        }
    }
    glEnd();
}

void drawCircle(int x0, int y0, int r){
    glBegin(GL_POINTS);
    int x = 0;
    int y = r;
    int d = 1 - r;
    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 + y, y0 + x);
    glVertex2i(x0 + y, y0 - x);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
    glVertex2i(x0 - y, y0 - x);
    glVertex2i(x0 - y, y0 + x);
    glVertex2i(x0 - x, y0 + y);
    while(x < y){
        if(d < 0)
            d += 2*x + 3;
        else{
            d += 2*(x - y) + 5;
            y--;
        }
        x++;
        glVertex2i(x0 + x, y0 + y);
        glVertex2i(x0 + y, y0 + x);
        glVertex2i(x0 + y, y0 - x);
        glVertex2i(x0 + x, y0 - y);
        glVertex2i(x0 - x, y0 - y);
        glVertex2i(x0 - y, y0 - x);
        glVertex2i(x0 - y, y0 + x);
        glVertex2i(x0 - x, y0 + y);
    };
    glEnd();
}

void drawOval(int x0, int y0, int a, int b){
    glBegin(GL_POINTS);
    int aa = a*a;
    int bb = b*b;
    int twoaa = 2*aa;
    int twobb = 2*bb;
    int p;
    int x = 0;
    int y = b;
    int px = 0;
    int py = twoaa * y;
    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
    
    p = (bb-(aa * b)+(0.25 * aa)) + 0.5;
    while(px < py){
        x++;
        px += twobb;
        if(p < 0)
            p += bb + px;
        else{
            y--;
            py -= twoaa;
            p += bb + px - py;
        }
        glVertex2i(x0 + x, y0 + y);
        glVertex2i(x0 - x, y0 + y);
        glVertex2i(x0 + x, y0 - y);
        glVertex2i(x0 - x, y0 - y);
    }
    
    p = (bb*(x + 0.5)*(x + 0.5) + aa*(y -1)*(y - 1)- aa*bb) + 0.5;
    while(y > 0){
        y--;
        py -= twoaa;
        if(p > 0)
            p += aa - py;
        else{
            x++;
            px += twobb;
            p += aa - py + px;
        }
        glVertex2i(x0 + x, y0 + y);
        glVertex2i(x0 - x, y0 + y);
        glVertex2i(x0 + x, y0 - y);
        glVertex2i(x0 - x, y0 - y);
    }
    
    glEnd();
}
/*
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
*/
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
    glColor3f(0.0f, 0.0f, 1.0f);
    frame++;
    timenow = glutGet(GLUT_ELAPSED_TIME);
    if(timenow - timebase >1000){
        //sprintf(s, "FPS:%4.2f", frame * 1000.0 /(timenow - timebase));
        sprintf(s, "x:%d,y:%d", myMouse.x, myMouse.y);
        timebase = timenow;
        frame = 0;
    }
    
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(0, 20, 0, font, s);
    glPopMatrix();
    restorePerspectiveProjection();
}

void setOrthographicProjection(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection(){
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
