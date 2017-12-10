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

extern int mainWindow, displayWindow, controlWindow;
extern int width, height, border;
extern int position1x, position1y, width1, height1;
extern int position2x, position2y, width2, height2;
extern int xMove, yMove, zMove;

float x = 0.0f,y = 0.0f, z = 20.0f;
float lx = 0.0f,ly = 0.0f, lz = -20.0f;

void renderScene(){
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void renderDisplay(){
    glutSetWindow(displayWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt( x, y, z,
              x+lx, y+ly, z+lz,
              0.0f, 1000.0f, 0.0f);
    drawDisplay();
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

void renderSceneAll(){
    if(xMove | yMove | zMove)
        computePos(xMove, yMove, zMove);
    
    renderDisplay();
    renderControl();
}

void changeSize(int w,int h){
    if(h == 0)
        h = 1;
    width = w;
    height = h;
    position1x = border;
    position1y = border;
    width1 = (width * 3/4) - border * 3/2;
    height1 = height - 2*border;
    position2x =(width * 3/4) + border * 1/2;
    position2y = border;
    width2 = (width  * 1/4) - border * 3/2;
    height2 = height - 2*border;
    
    glutSetWindow(displayWindow);
    glutPositionWindow(position1x, position1y);
    glutReshapeWindow(width1, height1);
    float ratio = 1.0 * width1/height1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width1, height1);
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glutSetWindow(controlWindow);
    glutPositionWindow(position2x, position2y);
    glutReshapeWindow(width2, height2);
    ratio = 1.0 * width2/height2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width2, height2);
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void computePos(float xMove, float yMove, float zMove){
    lx += xMove * 0.02f;
    ly += yMove * 0.02f;
    lz += zMove * 0.02f;
}
