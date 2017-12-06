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

void draw(){
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f( 1.0f, 0.0f, -1.0f);
        glVertex3f( -1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f, 0.0f, 1.0f);
    glEnd();
    
    /*
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawSnowMan();
    glPopMatrix();*/
    
    drawFPS();
}

void drawSnowMan(){
    glScalef(scale, scale, scale);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);
    
    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();
    
    // Draw Nose
    glColor3f(red, green, blue);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
    
    glColor3f(1.0f, 1.0f, 1.0f);
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
