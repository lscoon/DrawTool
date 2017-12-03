//
//  mouse.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>

#include "mouse.hpp"

extern float lx, lz, angle, deltaAngle;

int xOrigin = -1;

void mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP){
            angle += deltaAngle;
            xOrigin = -1;
        }
        else xOrigin = x;
    }
}

void mouseMove(int x, int y){
    if(xOrigin >= 0){
        deltaAngle = (x-xOrigin) * 0.0001f;
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
        
    }
}
