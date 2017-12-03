//
//  keyboard.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/3.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

#include "keyboard.hpp"

float x = 0.0f, z = 5.0f;
float lx = 0.0f, lz = -1.0f;
float angle = 0.0f;

extern float deltaAngle,deltaMove;

void processNormalKeys(unsigned char key, int xx, int yy){
    if(key == 27)
        exit(0);
}

void pressKey(int key,int xx,int yy){
    switch(key){
        case GLUT_KEY_LEFT:deltaAngle = -0.01f;break;
        case GLUT_KEY_RIGHT:deltaAngle = 0.01f;break;
        case GLUT_KEY_UP:deltaMove = 0.5f;break;
        case GLUT_KEY_DOWN:deltaMove = -0.5f;break;
    }
}
void releaseKey(int key,int xx,int yy){
    switch(key){
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:deltaAngle = 0.0f;break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:deltaMove = 0.0f;break;
    }
}
