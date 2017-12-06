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
extern float x, z, lx, lz, angle;

float deltaAngle = 0.0f;
float deltaMove = 0.0f;

void renderScene(){
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    
    //char number[3];
    //sprintf(number, "%d", 33);
    //renderStrokeFontString(0.0f, 0.5f, 0.0f,GLUT_STROKE_ROMAN, number);
}

void renderDisplay(){
    glutSetWindow(displayWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt( x, 1.0f, z,
              x+lx, 1.0f, z+lz,
              0.0f, 1.0f, 0.0f);
    draw();
    
    glutSwapBuffers();
}

void renderControl(){
    glutSetWindow(controlWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void renderSceneAll(){
    if(deltaMove)
        computePos(deltaMove);
    //if(deltaAngle)
    //    computeDir(deltaAngle);
    
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
    setProjection(width1, height1);
    
    glutSetWindow(controlWindow);
    glutPositionWindow(position2x, position2y);
    glutReshapeWindow(width2, height2);
    setProjection(width2, height2);
}

void computePos(float deltaMove){
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle){
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void setProjection(int w, int h){
    float ratio = 1.0 * w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
}
