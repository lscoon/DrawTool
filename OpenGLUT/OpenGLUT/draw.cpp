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

extern int width1, height1, border;
extern void *font;

float red = 1.0f, green = 0.5f, blue = 0.5f;
float scale = 1.0f;

int frame;
long time, timebase = 0;
char s[50];

void drawDisplay(){
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f( -2.0f, -2.0f, 0.0f);
        glVertex3f( 2.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 2.0f, 0.0f);
    glEnd();
    
    /*
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawSnowMan();
    glPopMatrix();*/
    
    drawFPS();
}

void drawControl(){
    Button b1 = {-2.0f, 5.0f, 3.0f, 1.5f};
    drawButton(&b1);
    Button b2 = {-2.0f, 2.0f, 3.0f, 1.5f};
    drawButton(&b2);
    Button b3 = {-2.0f, -1.0f, 3.0f, 1.5f};
    drawButton(&b3);
}

void drawButton(Button *b){
    if(b){
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(b->x, b->y, 0.0f);
            glVertex3f(b->x + b->w, b->y, 0.0f);
            glVertex3f(b->x + b->w, b->y + b->h, 0.0f);
            glVertex3f(b->x, b->y + b->h, 0.0f);
        glEnd();
    }
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
