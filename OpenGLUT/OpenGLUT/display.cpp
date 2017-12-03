//
//  display.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/3.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>

#include "display.hpp"

extern float x,z,lx,lz,angle;

float deltaAngle = 0.0f;
float deltaMove = 0.0f;

float red = 1.0f, green = 0.5f, blue = 0.5f;
float scale = 1.0f;

void display(){
    if(deltaMove)
        computePos(deltaMove);
    //if(deltaAngle)
    //    computeDir(deltaAngle);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt( x, 1.0f, z,
              x+lx, 1.0f, z+lz,
              0.0f, 1.0f, 0.0f);
    
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f( -100.0f, 0.0f, -100.0f);
    glVertex3f( -100.0f, 0.0f, 100.0f);
    glVertex3f( 100.0f, 0.0f, 100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawSnowMan();
    glPopMatrix();
    
    //angle += 0.05f;
    glutSwapBuffers();
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

void reshape(int w,int h){
    if(h == 0)
        h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
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



