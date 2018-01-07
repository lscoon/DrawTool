//
//  display.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/3.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>
#include <stdio.h>

#include "display.hpp"
#include "draw.hpp"

extern int width, height;
extern int xMove, yMove, zMove;

float x = 0.0f,y = 0.0f, z = 20.0f;
float lx = 0.0f,ly = 0.0f, lz = -20.0f;

void renderScene(){
    if(xMove | yMove | zMove)
        computePos(xMove, yMove, zMove);
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    glutSwapBuffers();
}
/*
void renderDisplay(){
    glutSetWindow(displayWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawDisplay();
 
    glLoadIdentity();
    gluLookAt( x, y, z,
              x+lx, y+ly, z+lz,
              0.0f, 1000.0f, 0.0f);
 
    glutSwapBuffers();
}

void renderControl(){
    glutSetWindow(controlWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,20.0f,0.0f,0.0f,-20.0f,0.0f,1000.0f,0.0f);
    drawControl();
    glutSwapBuffers();
}
*/

void changeSize(int w,int h){
    if(h == 0)
        h = 1;
    width = w;
    height = h;
    glutReshapeWindow(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    
    /*
    glutSetWindow(controlWindow);
    glutPositionWindow(position2x, position2y);
    float ratio = 1.0 * width1/height1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width1, height1);
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);*/
}

void computePos(float xMove, float yMove, float zMove){
    lx += xMove * 0.02f;
    ly += yMove * 0.02f;
    lz += zMove * 0.02f;
}
