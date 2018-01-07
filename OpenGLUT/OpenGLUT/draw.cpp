//
//  draw.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "draw.hpp"
#include "mouse.hpp"
#include "font.hpp"
#include "bitmap.hpp"

#include "graph.hpp"

using namespace std;
extern vector<graph> allgraph;
extern graph nowgraph;

extern int lineFlag;
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
    for(auto g = allgraph.begin();g != allgraph.end(); g++){
        switch(g->type){
            case LINE:g->drawLine();break;
            default:break;
        }
    }
    
    
    switch (nowgraph.type){
        case NOTHING:break;
        case LINE:{
            nowgraph.drawLine();
            if(lineFlag == 2){
                graph *temp = new graph(Point(myMouse.xpress,height - myMouse.ypress), Point(myMouse.x,height - myMouse.y));
                temp->drawLine();
                delete(temp);
            }
        }break;
        default:break;
    }
    //drawBezier(0, 0, 10, 100, 100, 130, 300, 100);
    //drawDDA(myMouse.xpress, height - myMouse.ypress, myMouse.x, height - myMouse.y);
    //drawOval(myMouse.x, height - myMouse.y, 30,20);
    //const char *fileName = "/Users/apple/Documents/Photos/bear.bmp";
    //bitmapData = LoadBitmapFile(fileName, &bitmapInfoHeader);
    //if(bitmapData == NULL)
        //std::cout<<"kkk"<<std::endl;
    drawFPS();
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
        sprintf(s, "x:%d,y:%d,%d,%d", nowgraph.dx , nowgraph.dy,nowgraph.angle,nowgraph.scale);
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


